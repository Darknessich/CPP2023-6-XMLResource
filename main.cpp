#include "XMLResource.h"

#include <iostream>

int main() {
  std::string const filename = "test.xml";
  auto resource = XMLResource::create();

  std::string msg;
  if (!resource->load(filename, msg)) {
    std::cout << msg << std::endl;
    return 0;
  }

  resource->save("out.xml");
}