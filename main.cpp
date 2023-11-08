#include "XMLResource.h"

#include <iostream>

int main() {
  std::string const filename = "../../../input.xml";
  auto resource = XMLResource::create();

  std::string msg;
  if (!resource->load(filename, msg)) {
    std::cout << msg << std::endl;
    return 0;
  }

  if (auto it = resource->find("surname"); it != resource->end())
    it->value() = "Ivanov";

  if (auto it = resource->find("name"); it != resource->end())
    it->value() = "Ivan";

  auto it = resource->find("fullname");
  if (!resource->erase(it))
    std::cout << "Ñannot be deleted (fullname)" << std::endl;

  it = resource->begin();
  resource->add("patronymic", "Ivanovich", it);

  it = resource->find("years");
  if (!resource->erase(it))
    std::cout << "Ñannot be deleted (years)" << std::endl;

  it = resource->add("info", "", resource->begin());
  resource->add("years", "30", it);
  resource->add("gender", "male", it);
  resource->add("status", "worker", it);

  resource->save("out.xml");
}