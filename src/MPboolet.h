#ifndef MPBOOLET_H
#define MPBOOLET_H

#include "MPglobal.h"

class MPboolet
{
   public:
      SDL_Rect box;
      int x;
      int direct;
      int y;
      bool active; // provera dali je metak aktivan
   
      void boolet_init(int r,int b, int v) // inicijalizacija metka
      {           
            
            
            
            
            
            box.h=5;
            box.w=12;
            
         if (active==false)
         {
            box.x=r;
            box.y=b;

            direct=v;
            active=true;
         }
      }
   
      void boolet_fire()
      {
         if (direct==1)
         box.x+=15;
         else
         box.x-=15;
      }
    
     
      void draw()
      {
         if (direct==1)
         apply_surface(box.x,box.y,m_spr_boolet_right,screen);
         else
         apply_surface(box.x,box.y,m_spr_boolet_left,screen);
      }

      MPboolet () {active=false;}
   
};

#endif
