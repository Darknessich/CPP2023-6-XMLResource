cmake_minimum_required (VERSION 3.8)

project ("XMLResource")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable (XMLResource 
  "main.cpp"
  "XMLDocument.cpp"
  "XMLDocument.h"
  "XMLElement.cpp"
  "XMLElement.h"
  "XMLIterator.cpp"
  "XMLIterator.h"
  "XMLResource.cpp"
  "XMLResource.h"
  "XMLParser.cpp"
  "XMLParser.h")