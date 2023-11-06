#pragma once
#include "XMLElement.h"

#include <string>
#include <memory>

class XMLParser {
  struct State {
    enum class EState {
      S_BEGIN,
      S_OPEN,
      S_BODY,
      S_VALUE,
      S_CLOSE,
      S_END,
      S_ERROR
    };

    EState state = EState::S_BEGIN;
    std::string str = "";
    std::string err_msg = "";
    std::unique_ptr<XMLElement> root = nullptr;
    XMLElement* curr = nullptr;

    bool isError() const;
    bool isCorrect() const;

    void begin(char c);
    void open(char c);
    void body(char c);
    void value(char c);
    void close(char c);

    void next(char c);
  };
public:

  XMLParser();
  std::unique_ptr<XMLElement> parse(std::string const& xmldocument);
  std::unique_ptr<XMLElement> parse(std::string const& xmldocument, bool& ok, std::string& msg);

private:
  struct State _state;
};