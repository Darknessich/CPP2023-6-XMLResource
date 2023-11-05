cmake_minimum_required (VERSION 3.8)

project ("XMLResource")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable (XMLResource 
  "main.cpp"
  "XMLDocument.cpp"
  "XMLElement.cpp"
  "XMLIterator.cpp"
  "XMLResource.cpp"
  "XMLParser.cpp")