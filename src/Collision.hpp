#ifndef COLLISION_H
#define COLLISION_H
#include <irrlicht.h>
#include <ostream>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


class Collision
{

 public:
  static bool getBitAt(int buffer, int bitIndex);

  // ...lots of great stuff

 private:
  // Disallow creating an instance of this object
  Collision() {}
};
#endif
