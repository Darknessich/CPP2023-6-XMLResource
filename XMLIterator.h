#pragma once
#include "XMLElement.h"

#include <iterator>
#include <stack>

struct XMLElement::XMLIterator :
  std::iterator<std::forward_iterator_tag, XMLElement>
{
  XMLIterator();
  XMLIterator(XMLElement*);

  XMLIterator(XMLIterator const&) = default;
  XMLIterator& operator=(XMLIterator const&) = default;
  
  XMLIterator(XMLIterator&&) = default;
  XMLIterator& operator=(XMLIterator&&) = default;
  
  XMLElement& operator*() noexcept;
  XMLElement* operator->() noexcept;

  XMLIterator& operator++();
  XMLIterator  operator++(int);

  bool operator==(XMLIterator const&);
  bool operator!=(XMLIterator const&);

private:
  std::stack<XMLElement*> _fwd;
  XMLElement* _current;
};