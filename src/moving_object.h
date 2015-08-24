#ifndef MOVING_OBJECT_H
#define MOVING_OBJECT_H

#include "functions.h"

class red_object
{
   public:
      SDL_Rect box;
      SDL_Surface * image;
      
      red_object(int s,int g,int h,int j,SDL_Surface *d)//deklaracija krecuceg objekta
      {
         box.x=s;
         box.y=g;
         box.w=h;
         box.h=j;
         image=d;
      }
      red_object(){}
      void draw()
      {
         apply_surface(box.x-camera.x,box.y-camera.y,image,screen);   
      }
}emiter1,emiter2;

class moving_object
{
   public:
      SDL_Rect box;
      SDL_Surface * image;
      int x,y;
      int velx,vely,speed;
      
      int right,left;
      
      bool v;
      
      bool top;//parametar koji odredjuje vrstu krecuceg neprijatelja
 
    moving_object()
    {
}

    
      moving_object(bool to,int x,int y,int lef,int righ,int sped,SDL_Surface *d)
      {
         top=to;
         left=lef;
         right=righ;
         speed=sped;
         if(top==true)
         vely=speed;
         else
         velx=speed;
         
         
         box.x=x;
         box.y=y;
         box.w=d->w;
         box.h=d->h;
         v=true;
         image=d;
         velx=1;
         
         x=box.x+(box.w/2);
         y=box.y+(box.h/2);
      }
      
      void think()//KRETANJE 
      {
      
         if (top==false)
         {box.x+=velx;
         vely=0;
            if(v==true)
               if (box.x < right)
                  velx=speed;
                    else v=false;
               else
               {
                  if (box.x > left)
                  velx=-speed;
                  else 
                  v=true;
               }
               
          }
          else
          {
              velx=0;
             box.y+=vely;
            if(v==true)
               if (box.y < right)
                  vely=speed;
                    else v=false;
               else
               {
                  if (box.y > left)
                    vely=-speed;
                  else 
                  v=true;
               }
          }
      }
      
      void draw(bool a)
      {
        if(a==true)
         apply_surface(box.x-camera.x,box.y-camera.y,image,screen); 
         else
          apply_surface(box.x,box.y,image,screen); 
      }
}lift2,lift1,mobj,mobj3,mobj4,mobj5,mobj6,mobj7,mobj8,mobj9,mobj10,mobj11,mobj12,mobj13,mobj14,mobj15;
#endif
