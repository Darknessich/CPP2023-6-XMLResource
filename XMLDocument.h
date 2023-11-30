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

  XMLDocument(XMLDocument const&);
  XMLDocument(XMLDocument&&) = default;

  XMLDocument& operator=(XMLDocument const&);
  XMLDocument& operator=(XMLDocument&&) = default;

  bool load(std::string const& filename);
  bool load(std::string const& filename, std::string& msg);
  void save(std::string const& filename) const;

  Iterator begin();
  Iterator end();

  Iterator find(std::string const& name);
  Iterator find(std::string const& name, Iterator start);

  Iterator add(std::string const& name, std::string const& value, Iterator place);
  Iterator addRoot(std::string const& name, std::string const& value);

  bool erase(Iterator place);

private:
  std::unique_ptr<XMLElement> _root;
  std::unique_ptr<XMLParser> _parser;
};

