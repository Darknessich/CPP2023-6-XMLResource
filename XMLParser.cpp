#include "XMLParser.h"

bool XMLParser::State::isError() const {
  return state == EState::S_ERROR;
}

bool XMLParser::State::isCorrect() const {
  return !isError() && state != EState::S_END;
}

void XMLParser::State::begin(char c) {
  if (std::isspace(c))
    return;

  if (c == '<') {
    state = EState::S_OPEN;
    str = "";
    return;
  }

  if (c == '\0') {
    state = EState::S_END;
    return;
  }

  state = EState::S_ERROR;
  err_msg = "Expected opening tag but found ";
  err_msg += c;
}

void XMLParser::State::open(char c) {
  if (isalnum(c)) {
    str += c;
    return;
  }

  if (str.empty() && c == '/') {
    state = EState::S_CLOSE;
    return;
  }

  if (c != '>') {
    state = EState::S_ERROR;
    err_msg = "Expected name [A-Za-z0-9] but found ";
    err_msg += c;
    return;
  }

  state = EState::S_BODY;

  if (root == nullptr) {
    root = std::make_unique<XMLElement>(str, "");
    curr = root.get();
    return;
  }

  curr = curr->emplace_back(str, "");
}

void XMLParser::State::body(char c) {
  if (isspace(c))
    return;

  if (c == '<') {
    state = EState::S_OPEN;
    str = "";
    return;
  }

  if (c == '\0') {
    state = EState::S_ERROR;
    err_msg = "Expected closing tag but found end of file";
    return;
  }

  state = EState::S_VALUE;
  str = "";
  str += c;
}

void XMLParser::State::value(char c) {
  if (isspace(c) || c == '<') {
    state = c == '<'? EState::S_OPEN : EState::S_BODY;
    if (!curr->value().empty())
      curr->value() += ' ';
    curr->value() += str;
    str = "";
    return;
  }

  if (c == '\0') {
    state = EState::S_ERROR;
    err_msg = "Expected closing tag but found end of file";
    return;
  }

  str += c;
}

void XMLParser::State::close(char c) {
  if (isalnum(c)) {
    str += c;
    return;
  }

  if (c != '>') {
    state = EState::S_ERROR;
    err_msg = "Expected name [A-Za-z0-9] but found ";
    err_msg += c;
    return;
  }

  if (curr == nullptr || curr->name() != str) {
    state = EState::S_ERROR;
    err_msg = "The opening and closing tag names do not match";
    return;
  }

  curr = curr->parent();
  state = curr ? EState::S_BODY : EState::S_END;
}

void XMLParser::State::next(char c) {
  switch (state) {
  case EState::S_BEGIN:
    begin(c);
    break;

  case EState::S_OPEN:
    open(c);
    break;

  case EState::S_BODY:
    body(c);
    break;

  case EState::S_VALUE:
    value(c);
    break;

  case EState::S_CLOSE:
    close(c);
    break;

  case EState::S_END:
  case EState::S_ERROR:
    break;

  default:
    state = EState::S_ERROR;
    err_msg = "Unknown error";
    break;
  }
}

XMLParser::XMLParser()
  : _state()
{}

std::unique_ptr<XMLElement> XMLParser::parse(std::string const& xmldocument) {
  bool ok;
  std::string msg;
  return parse(xmldocument, ok, msg);
}

std::unique_ptr<XMLElement> XMLParser::parse(std::string const& xmldocument, bool& ok, std::string& msg) {
  _state = State();
  
  size_t ptr = 0;
  while (_state.isCorrect())
    _state.next(xmldocument[ptr++]);

  if (_state.isError()) {
    ok = false;
    msg = _state.err_msg;
    return nullptr;
  }

  ok = true;
  return std::move(_state.root);
}