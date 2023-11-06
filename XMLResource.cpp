#include "XMLResource.h"

using Res = XMLResource;
using Iter = Res::Iterator;

std::unique_ptr<Res> Res::create() {
  return std::unique_ptr<Res>(new XMLResource());
}

bool Res::load(std::string const& filename) {
  return _document.load(filename);
}

bool Res::load(std::string const& filename, std::string& msg) {
  return _document.load(filename, msg);
}

void Res::save(std::string const& filename) const {
  _document.save(filename);
}

Iter Res::begin() {
  return _document.begin();
}

Iter Res::end() {
  return _document.end();
}

Iter Res::find(std::string const& name) const {
  return _document.find(name);
}

Iter Res::find(std::string const& name, Iter start) const {
  return _document.find(name, start);
}

Iter Res::add(std::string const& name, std::string const& value, Iter place) {
  return _document.add(name, value, place);
}

bool Res::erase(Iter& place) {
  return _document.erase(place);
}