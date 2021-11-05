#include <random>
#include <functional>
#include <stdlib.h>
#include "atkui/framework.h"
#include "atk/toolkit.h"
#include "agl/renderer.h"
#include "devil.h"

using namespace atk;
using namespace glm;

class Thriller : public atkui::Framework
{
public:
   Thriller() : atkui::Framework(atkui::Perspective) {}
   virtual ~Thriller() {}

   virtual void setup() {
      BVHReader reader;
      reader.load("../motions/Warrok/WarrokThriller.bvh", _skeleton, _motion);
      int count=0;
      for(int x=-2;x<=1;x++){
         for(int y=-1;y<=1;y++){
              positions[count] = vec3(x*100, (y+1)*100, (y)*150);
                std::cout << positions[count] << std::endl;
              count++;
         }
      }

      for(int i=0;i<N;i++){
         vec3 pos =positions[i];
         vec3 color = agl::randomUnitVector();
         float size =0.5f+((float)((rand()%3-1)*0.1));
         devils[i] = Devil(pos, color, size);

      }
      /*
      vec3 position = vec3(0);
      vec3 color = vec3(1,0,0);
      float size = 1.0f;
      _devil = Devil(position, color, size);
      */
   }

   virtual void scene() {
      if (!_paused) _motion.update(_skeleton, elapsedTime());
      for(int i=0;i<N;i++){
         devils[i].draw(_skeleton, *this);
     // _devil.draw(_skeleton, *this);
      }
   }

   virtual void keyUp(int key, int mods) {
      if (key == 'P') _paused = !_paused;
   }

protected:
   Motion _motion;
   Skeleton _skeleton;
   bool _paused = false;
   Devil _devil;
   int N = 12;
   Devil devils[12] = {}; 
   vec3 positions [12] = {};
   
};

int main(int argc, char** argv) {
   Thriller viewer;
   viewer.run();
}

