#include "XMLDocument.h"
#include <fstream>
#include <sstream>
#include <stack>

using Doc = XMLDocument;
using Iterator = Doc::Iterator;

Doc::XMLDocument()
  : _root(nullptr), _parser(new XMLParser)
{}

Doc::XMLDocument(XMLDocument const& other) {
  *(this->_root) = *(other._root);
}

XMLDocument& Doc::operator=(XMLDocument const& other) {
  *(this->_root) = *(other._root);
  return *this;
}

bool Doc::load(std::string const& filename) {
  std::string msg;
  return this->load(filename, msg);
}

bool Doc::load(std::string const& filename, std::string& msg) {
  std::ifstream file(filename);

  if (!file.is_open()) {
    msg = "file \"" + filename + "\" not found";
    return false;
  }

  std::ostringstream ss;
  ss << file.rdbuf();

  bool ok;
  auto new_root = _parser->parse(ss.str(), ok, msg);
  if (ok) 
    _root = std::move(new_root);
  return ok;
}

void Doc::save(std::string const& filename) const {
  std::ofstream file(filename, std::ios::ate | std::ios::out);

  int level = 0;
  std::stack<Iterator> closing;
  for (auto&& it = _root->begin(); it != _root->end(); it++) {
    if (!closing.empty() && closing.top() != it->parent()) {
      --level;
      file << std::string(2 * level, ' ') << "</" << closing.top()->name() << ">" << std::endl;
      closing.pop();
    }
   
    file << std::string(2 * level, ' ') << "<" << it->name() << ">" << it->value();
    
    if (it->hasChild()) {
      file << std::endl;
      ++level;
      closing.push(it);
    } 
    else 
      file << "</" << it->name() << ">" << std::endl;
  }

  if (!closing.empty()) {
    --level;
    file << std::string(2 * level, ' ') << "</" << closing.top()->name() << ">" << std::endl;
    closing.pop();
  }
}

Iterator Doc::begin() {
  return _root->begin();
}

Iterator Doc::end() {
  return _root->end();
}

Iterator Doc::find(std::string const& name) {
  return this->find(name, _root->begin());
}

Iterator Doc::find(std::string const& name, Iterator start) {
  for (auto&& it = start; it != _root->end(); it++)
    if (it->name() == name)
      return it;

  return end();
}

Iterator Doc::add(std::string const& name, std::string const& value, Iterator place) {
  place->emplace_front(name, value);
  return ++place;
}

bool Doc::erase(Iterator place) {
  if (place == begin() || place == end())
    return false;
  
  place->childrenToParent();
  place->parent()->erase(place);
  return true;
}