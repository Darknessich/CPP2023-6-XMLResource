#include "XMLParser.h"

//TODO
struct State {

};

XMLParser::XMLParser()
  : _state(nullptr)
{}

//TODO
std::unique_ptr<XMLElement> XMLParser::parse(std::string const xmldocument) {
  auto root = std::make_unique<XMLElement>("", "");
  return root;
}