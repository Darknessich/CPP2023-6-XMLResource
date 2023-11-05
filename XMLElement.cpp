#include "XMLElement.h"

XMLElement::XMLElement(std::string const& name, std::string const& value)
  : _name(name), _value(value)
{}

std::string XMLElement::name() const {
  return _name;
}

std::string XMLElement::value() const {
  return _value;
}

XMLElement::XMLIterator XMLElement::begin() {
  return XMLIterator(this);
}

XMLElement::XMLIterator XMLElement::end() {
  return XMLIterator();
}

void XMLElement::emplace_back(std::string const& name, std::string const& value) {
  _children.emplace_back(std::make_unique<XMLElement>(name, value));
}