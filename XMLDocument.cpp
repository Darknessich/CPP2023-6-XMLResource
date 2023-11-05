#include "XMLDocument.h"

using Doc = XMLDocument;
using Iterator = Doc::Iterator;

Doc::XMLDocument()
  : _root(nullptr), _parser(new XMLParser)
{}

// TODO
bool Doc::load(std::string const& filename) {
  return false;
}

// TODO
void Doc::save(std::string const& filename) const {

}

// TODO
Iterator Doc::find(std::string const& name) const {
  return _root->end();
}

// TODO
Iterator Doc::find(std::string const& name, Iterator start) const {
  return _root->end();
}

// TODO
Iterator Doc::add(std::string const& name, std::string const& value, Iterator place) {
  return _root->end();
}

// TODO
bool Doc::erase(Iterator& place) {
  return false;
}