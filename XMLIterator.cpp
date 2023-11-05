#include "XMLIterator.h"

using Iter = XMLElement::XMLIterator;

Iter::XMLIterator()
  : _current(nullptr)
{}

Iter::XMLIterator(XMLElement* init) 
  : _current(init)
{}


XMLElement& Iter::operator*() noexcept {
  return *_current;
}

XMLElement* Iter::operator->() noexcept {
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

bool Iter::operator==(XMLIterator const& other) {
  return _current == other._current;
}

bool Iter::operator!=(XMLIterator const& other) {
  return _current != other._current;
}