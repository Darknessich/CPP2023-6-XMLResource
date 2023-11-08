#include "XMLIterator.h"

using Iter = XMLElement::XMLIterator;

Iter::XMLIterator()
  : _current(nullptr)
{}

Iter::XMLIterator(XMLElement* init) 
  : _current(init)
{
  if (_current != nullptr) {
    std::stack<XMLElement*> parents;

    XMLElement* curr = _current;
    while (curr) {
      parents.push(curr);
      curr = curr->parent();
    }

    curr = parents.top();
    parents.pop();
    while (!parents.empty()) {
      auto& ch = curr->_children;
      for (auto&& it = ch.rbegin(); it->get() != parents.top() && it != ch.rend(); it++)
        _fwd.push(it->get());
      curr = parents.top();
      parents.pop();
    }
  }
}


XMLElement& Iter::operator*() const noexcept {
  return *_current;
}

XMLElement* Iter::operator->() const noexcept {
  return _current;
}

Iter& Iter::operator++() {
  if (!_current) return *this;

  auto& ch = _current->_children;

  if (ch.empty() && _fwd.empty()) {
    _current = nullptr;
    return *this;
  }

  std::stack<XMLElement*> copy(_fwd); // for SEG
  if (!ch.empty()) {
    for (auto&& rit = ch.rbegin(); rit != ch.rend(); rit++)
      copy.push(rit->get());
  }                               // except

  XMLElement* curr = copy.top();  // for SEG
  copy.pop();                     // except

  _fwd = std::move(copy);         // noexcept
  _current = curr;                // noexcept
  return *this;
}

Iter  Iter::operator++(int) {
  Iter prev(*this); // except
  ++(*this);        // SEG
  return prev;      // noexcept (&&)
}

bool Iter::operator==(XMLIterator const& other) const {
  return _current == other._current;
}

bool Iter::operator!=(XMLIterator const& other) const {
  return _current != other._current;
}

bool Iter::operator==(XMLElement* other) const {
  return _current == other;
}

bool Iter::operator!=(XMLElement* other) const {
  return _current != other;
}