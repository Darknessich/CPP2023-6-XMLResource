#pragma once
#include <iterator>
#include <string>
#include <memory>
#include <vector>

class XMLElement
{
public:
  struct XMLIterator;

  using XMLChild = std::unique_ptr<XMLElement>;
  using XMLChildren = std::vector<XMLChild>;

  XMLElement(std::string const& name, std::string const& value);

  XMLElement(XMLElement const&) = default;
  XMLElement& operator=(XMLElement const&) = default;

  XMLElement(XMLElement&&) = default;
  XMLElement& operator=(XMLElement&&) = default;


  std::string name() const;
  std::string value() const;

  XMLIterator begin();
  XMLIterator end();

  void emplace_back(std::string const& name, std::string const& value);

private:
  std::string _name;
  std::string _value;

  XMLChildren _children;
};

#include "XMLIterator.h"