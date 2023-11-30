#pragma once
#include "XMLElement.h"

#include <iterator>
#include <stack>

struct XMLElement::XMLIterator {
  XMLIterator();
  explicit XMLIterator(XMLElement*);

  XMLIterator(XMLIterator const&) = default;
  XMLIterator& operator=(XMLIterator const&) = default;
  
  XMLIterator(XMLIterator&&) = default;
  XMLIterator& operator=(XMLIterator&&) = default;
  
  XMLElement& operator*() const noexcept;
  XMLElement* operator->() const noexcept;

  XMLIterator& operator++();
  XMLIterator  operator++(int);

  bool operator==(XMLIterator const&) const;
  bool operator!=(XMLIterator const&) const;

  bool operator==(XMLElement*) const;
  bool operator!=(XMLElement*) const;
private:
  std::stack<XMLElement*> _fwd;
  XMLElement* _current;
};