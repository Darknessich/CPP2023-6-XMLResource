#pragma once

#include "XMLDocument.h"

#include <memory>

class XMLResource {
public:
  using Iterator = XMLDocument::Iterator;
  
  static std::unique_ptr<XMLResource> create();

  XMLResource(XMLResource const&) = delete;
  XMLResource(XMLResource&&) = delete;

  XMLResource& operator=(XMLResource const&) = delete;
  XMLResource& operator=(XMLResource&&) = delete;

  bool load(std::string const& filename);
  void save(std::string const& filename) const;

  Iterator find(std::string const& name) const;
  Iterator find(std::string const& name, Iterator start) const;

  Iterator add(std::string const& name, std::string const& value, Iterator place);
  bool erase(Iterator& place);

private:
  XMLResource() = default;
  XMLDocument _document;
};