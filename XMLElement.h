#pragma once
#include <iterator>
#include <string>
#include <memory>
#include <list>

class XMLElement
{
public:
  struct XMLIterator;

  using XMLChild = std::unique_ptr<XMLElement>;
  using XMLChildren = std::list<XMLChild>;

  XMLElement(std::string const& name, std::string const& value, XMLElement* parent = nullptr);

  XMLElement(XMLElement const&);
  XMLElement& operator=(XMLElement const&);

  XMLElement(XMLElement&&) noexcept = default;
  XMLElement& operator=(XMLElement&&) noexcept = default;

  std::string name() const;
  std::string& name() noexcept;

  std::string value() const;
  std::string& value() noexcept;

  XMLElement* parent() noexcept;
  bool hasChild() noexcept;

  XMLIterator begin();
  XMLIterator end();

  XMLElement* emplace_back(std::string const& name, std::string const& value);

private:
  std::string _name;
  std::string _value;

  XMLElement* _parent;
  XMLChildren _children;
};

#include "XMLIterator.h"