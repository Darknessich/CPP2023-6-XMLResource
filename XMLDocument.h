#pragma once
#include "XMLElement.h"
#include "XMLParser.h"

#include <memory>
#include <string>

class XMLDocument
{
public:
  using Iterator = XMLElement::XMLIterator;
  
  XMLDocument();

  bool load(std::string const& filename);
  void save(std::string const& filename) const;

  Iterator find(std::string const& name) const;
  Iterator find(std::string const& name, Iterator start) const;

  Iterator add(std::string const& name, std::string const& value, Iterator place);
  bool erase(Iterator& place);

private:
  std::unique_ptr<XMLElement> _root;
  std::unique_ptr<XMLParser> _parser;
};

