#pragma once
#include "XMLElement.h"

#include <string>
#include <memory>

class XMLParser {
public:

  XMLParser();
  std::unique_ptr<XMLElement> parse(std::string const xmldocument);

private:
  struct State* _state;
};