#include "data.h"
#include <iostream>
#include <quakelib/common/entity_parser.h>

using std::cout, std::endl;
using namespace quakelib;

class MyPoint : public PointEntity {};

int main() {

  EntityParser::ParseEntites(entbuff, [](ParsedEntity *pe) {
    Entity *ent = nullptr;
    if (pe->type == EntityType::POINT) {
      ent = new MyPoint();
    }
    if (pe->type == EntityType::SOLID) {
      ent = new SolidEntity();
    }
    if (pe->type == EntityType::WORLDSPAWN) {
      ent = new WorldSpawnEntity();
    }
    ent->FillFromParsed(pe);
    cout << ent->ClassName() << endl;
  });
  cout << "============" << endl << endl;
  EntityParser::ParseEntites(mapbuff, [](ParsedEntity *pe) {
    auto mp = MyPoint();
    mp.FillFromParsed(pe);
    cout << mp.ClassName() << mp.Origin()[0] << endl;
  });
}