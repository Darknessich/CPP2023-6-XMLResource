#include "XMLElement.h"

#include <queue>

XMLElement::XMLElement(std::string const& name, std::string const& value, XMLElement* parent)
  : _name(name), _value(value), _parent(parent)
{}

XMLElement::XMLElement(XMLElement const& other) {
  std::queue<std::pair<XMLElement*, XMLElement const*>> q;
  q.push({ this, &other });

  this->_name = other._name;
  this->_value = other._value;
  while (!q.empty()) {
    auto [copy, from] = q.front();
    q.pop();

    for (auto&& child : from->_children) {
      copy->emplace_back(child->_name, child->_value);
      q.push({copy->_children.back().get(), child.get()});
    }
  }
}

XMLElement& XMLElement::operator=(XMLElement const& other) {
  XMLElement copy(other);
  *this = std::move(copy);
  return *this;
}

std::string XMLElement::name() const {
  return _name;
}

std::string XMLElement::value() const {
  return _value;
}

std::string& XMLElement::name() noexcept {
  return _name;
}

std::string& XMLElement::value() noexcept {
  return _value;
}

XMLElement* XMLElement::parent() noexcept {
  return _parent;
}

bool XMLElement::hasChild() noexcept {
  return !_children.empty();
}


XMLElement::XMLIterator XMLElement::begin() {
  return XMLIterator(this);
}

XMLElement::XMLIterator XMLElement::end() {
  return XMLIterator();
}

XMLElement* XMLElement::emplace_back(std::string const& name, std::string const& value) {
  _children.emplace_back(std::make_unique<XMLElement>(name, value, this));
  return _children.back().get();
}