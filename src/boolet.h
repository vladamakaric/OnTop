#ifndef BOOLET_H
#define BOOLET_H
#include "global.h"

class boolet
{
   public:
      SDL_Rect box;
      int x;
      int direct;
      int y;
      bool active; // provera dali je metak aktivan
   
      void boolet_init(int r,int b, int v) // inicijalizacija metka
      {
         if (active==false)
         {
            box.x=r;
            box.y=b;
            box.h=8;
            box.w=15;
            direct=v;
            active=true;
         }
      }
   
      void boolet_fire()
      {
         if (direct==1)
         box.x+=10;
         else
         box.x-=10;
      }
    
     
      void draw()
      {
         if (direct==1)
         apply_surface(box.x-camera.x,box.y-camera.y,spr_boolet_right,screen);
         else
         apply_surface(box.x-camera.x,box.y-camera.y,spr_boolet_left,screen);
      }

      boolet () {active=false;}
   
};

#endif
