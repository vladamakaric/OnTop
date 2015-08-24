#ifndef SENEMYS_H
#define SENEMYS_H


#include "functions.h"
#include "boolet.h"



///////////////////////////////////////////////////////////////////////
// gurajuci nepriajtelj
///////////////////////////////////////////////////////////////////////
class pushing_enemy 
{
   public:
      pushing_enemy(int xx, int yy,int clef,int crig,int d,int r);
      pushing_enemy(moving_object f,int xx, int yy,int d,int r);
      pushing_enemy(){};
      SDL_Rect box;
      moving_object obj;
      int Eheight;
      int brojac;
      int start_speed;
      int left,right;
      int speed;
      int cfg;         
   
      bool v;
      bool red;
      bool dir_left;
      
      bool allow_push;
   
      void think(moving_object b);
      void think_again(moving_object a);
      void draw();
}pue,pue2,pue3;

pushing_enemy::pushing_enemy(moving_object f,int xx, int yy,int d,int r)
{
   obj=f;
   red=false;
   allow_push=true;
   Eheight=d*50;
   v=true;
   cfg=d;
   box.x=xx;
   speed=r;
   start_speed=r;
   box.h=cfg*50;
   box.w=50;
   

}



pushing_enemy::pushing_enemy(int xx, int yy,int clef,int crig,int d,int r)
{
   red=false;
   Eheight=d*50;
   v=true;
   cfg=d;
   left=clef; 
   right=crig;
   box.x=xx;
   speed=r;
   start_speed=r;

   if (cfg==1)
   {
      box.y=yy-50;
      box.h=100;
      box.w=33;
   }   
   else
   
   if (cfg==2)
   {
      box.y=yy-100;
      box.w=33;
      box.h=150;
   }
   else
   
   if (cfg==3)
   {
      box.y=yy-200;
      box.h=250;
      box.w=33;
   }
}

void pushing_enemy::think_again(moving_object a)
{

        if (cfg==1)
   {
      box.h=100;
      box.w=33;
   }   
   else
   
   if (cfg==2)
   {
      box.w=33;
      box.h=100;
   }
   else
   
   if (cfg==3)
   {
      box.h=250;
      box.w=33;
   }
   if (living==true)
   {
      left=a.box.x;
      if (cfg==1)
      right=a.box.x+a.box.w-8;
      
      box.y=a.box.y-box.h;              
                    
      int playerx=player.box.x;
      int playery=player.box.y;
      
      if ( (((playerx+4)>left)&&(playerx<right)) &&   ((playery+PLAYERHEIGHT)  >(box.y)) &&  (playery<(box.y+box.h))  )
      { 
         speed=10;
         Mix_PlayChannel( -1, beep, 0 );
         red=true;
      }
      else
      {
         speed=start_speed;
         red=false;
      }
   }else red=false; 

}

void pushing_enemy::think(moving_object a)
{
   int playerx=player.box.x;
   int playery=player.box.y;
   
   left=a.box.x;
      
   right=a.box.x+a.box.w-box.w-4;
      
   if (red==false) // ovaj deo koda obradjuje normalno kretanje od leva na desno
   {    
      if(v==true)
         if (box.x < right)
         {
            box.x+=speed;
         }
         else v=false;
      else
      {
         if (box.x > left)
         {
            box.x-=speed;
         }
         else 
            v=true;
      }
   }  
   else // ovde se obradjuje kretanje pod crvenim svetlom
   {
      if (playerx>box.x+15)
      {
         dir_left==false; 
         box.x+=speed;
         v=true;
      }
   else 
        if (playerx<box.x)
      {
         dir_left==true; 
         box.x-=speed;
         v=false;
      }
   }
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// u zavisnosti od stanja neprijatelja i njegove velicine crta se odredjena slika
//////////////////////////////////////////////////////////////////////////////////////////////////
void pushing_enemy::draw()
{
   if (red==false)
      apply_surface((box.x+6)-camera.x,(box.y)-camera.y,spr_pushing_enemy[0][cfg-1],screen);
   else
      apply_surface((box.x+6)-camera.x,(box.y)-camera.y,spr_pushing_enemy[1][cfg-1],screen);
}

///////////////////////////////////////////////////////////////////////
// kotrljajuci neprijatelj
///////////////////////////////////////////////////////////////////////
class rolling_enemy
{
   public:
   int brojac;
   SDL_Rect box;
   int left,right;
   int speed;
   int r_speed;
   int cfg;         
   void think();
   bool v;
   bool roll;
  // int k;
   rolling_enemy(int xx, int yy,int clef,int crig);
   rolling_enemy(){}
   
   void draw(int r,int t,int d)
   {

      if(d>359)
      d=2;
      if(d<1)
      d=359;
      
      
      apply_surface(r-camera.x,t-camera.y,spr_ball[d],screen);//mala

   }
}si_en1;

rolling_enemy::rolling_enemy(int xx, int yy,int clef,int crig)
{
   r_speed=0;
   v=true;
   left=clef; 
   right=crig;
   roll=false;
   box.x=xx;
   box.h=50;
   box.w=50;

      box.y=yy;

}

//krketanje od leva ka desno i nazad
void rolling_enemy::think() 
{

   if (living==true)
   {
                           
                    
      int playerx=player.box.x;
      int playery=player.box.y;
      
      if ( ((playerx>left)&&(playerx<(right+50))) &&   (playery+PLAYERHEIGHT  >(box.y)) &&  (playery<(box.y+box.h))  )
      { 
         roll=true;
         if(playerx>(box.x+box.w))//desna strana
         {
            speed=1000/(playerx-box.x);//obrnuta proporcionalnost (vise o ovome u dokumentaciji)
            if (abs(k)<360)
            {
               k+= -speed;
               if(k<0)
                  k=359;
               if(k>359)
                  k=0;
             }
             else 
                k=0;
         }
         else
         if ((playerx+PLAYERWIDTH)<box.x)
         {
            speed=1000/(playerx-box.x);    
            k+= -speed;
            if(k<0)
               k=359;      
            if(k>359)
               k=0;
         }
         r_speed=speed;

       }
       else
       {
          speed=0;
          roll=false;   
       }
       box.x+=speed;
    }    
}

///////////////////////////////////////////////////////////////////////
// pucajuci nepriajtelj
///////////////////////////////////////////////////////////////////////
class shooting_enemy
{
   public:
      boolet array[10000];// niz metkova na raspolaganju 
      SDL_Rect box;
      shooting_enemy(int xx, int yy,int clef,int crig,int r); // inicijalizacija neprijatelja
      shooting_enemy(){}
      int Eheight;
      int brojac;
      int start_speed;
      int left,right;
      int speed;
      
      void think_again();
      void think();
      
      void draw() // iscrtavanje
      {
         apply_surface(box.x-camera.x,box.y-camera.y, spr_shit ,screen);
      };
      
      bool v;
}sh_en,sh_en1,sh_en2,sh_en3,sh_en4,sh_en5;


shooting_enemy::shooting_enemy(int xx, int yy,int clef,int crig,int r)
{
   Eheight=100;
   v=true;

   left=clef; 
   right=crig;
   box.h=100;
   box.w=80;
   box.x=xx;
   box.y=yy;
      
   speed=r;
   start_speed=r;
      
   brojac=3;
};

void shooting_enemy::think_again()
{
   int playerx=player.box.x;
   int playery=player.box.y;
            
   if ( ((playerx>(left-50))&&(playerx<(right+50))) &&   (playery+PLAYERHEIGHT  >=(box.y)) &&  (((playery+PLAYERHEIGHT)-box.y)<Eheight)  )
   {// prva grana provere dali je igrac u opsegu neprijatelja
      if (playerx>box.x)//desni deo ospega
      {
         if (playery>(box.y+30))// ako je igrac u skoku i ako proba da izbegne neprijatelja
         {//tada neprijatelj ispaljuje metke iz gornje cevi
            if(GLOBAL_TIME%20==0) //ovo je ogranicenje da meci nebi leteli svake milisekunde
            {
               brojac++;  
               Mix_PlayChannel( -1, gun, 0 ); // zvuk pucnja
            }  
               array[brojac].boolet_init((box.x),(box.y+73),1);//kreiranje metka
         }
         else
         {
            if(GLOBAL_TIME%20==0) 
            {
               brojac++;    
               Mix_PlayChannel( -1, gun, 0 );     
            }  
              
            array[brojac].boolet_init((box.x),(box.y+23),1);
         }
         
      }
////////////////////////////////////////////////////////////////////////////////
//sve isto sto i gore samo sto se obradjuje levi deo opsega
////////////////////////////////////////////////////////////////////////////////
        
      if (playerx<box.x)
      {
         if (playery>(box.y+30))
         {
            if(GLOBAL_TIME%20==0) 
            {
               brojac++;     
               Mix_PlayChannel( -1, gun, 0 );
            }  
               
            array[brojac].boolet_init((box.x),(box.y+73),2);
         }
         else
         {
            if(GLOBAL_TIME%20==0) 
            {
               brojac++;          
               Mix_PlayChannel( -1, gun, 0 );
            }
            
            array[brojac].boolet_init((box.x),(box.y+23),2);
         }
            
      }
   }
   else
   {
      speed=start_speed; 
   }
};
////////////////////////////////////////////////////////////////////////////////
//ovde se obradjuje kretanje od leve do desne tacke neprijateljeve teritorije
/////////////////////////////////////////////////////////////////////////////////
void shooting_enemy::think()
{
   if(v==true)
      if (box.x < right)
         box.x+=speed;
         else v=false;
            else
            {
               if (box.x > left)
               box.x-=speed;
               else 
               v=true;
            }
}


///////////////////////////////////////////////////////////////////////
// neprijatelj koji ide levo desno 
///////////////////////////////////////////////////////////////////////
class Simple_enemy
{
   public:
   int brojac;
   SDL_Rect box;
   int left,right;
   int speed;
   int cfg;         
   void think();
   bool v;
   
   Simple_enemy(int xx, int yy,int clef,int crig,int d,int r);
   Simple_enemy(){}
   
   void draw()
   {
    /////////////////////////////////////////////////////////////////////////
    // u zavisnosti od visine neprijatelja razlicita slika ce biti iscrtavana
    ////////////////////////////////////////////////////////////////////////
      if (cfg==1)
      apply_surface((box.x)-camera.x,(box.y)-camera.y,spr_enemy1,screen);//mala
      
      if (cfg==2)
      apply_surface((box.x)-camera.x,(box.y)-camera.y,spr_enemy2,screen);//srednja
      
      if (cfg==3)
      apply_surface((box.x)-camera.x,(box.y)-camera.y,spr_enemy3,screen);//velika
   }
   
}simp,simp1,simp2,simp3,simp4;

Simple_enemy::Simple_enemy(int xx, int yy,int clef,int crig,int d,int r)
{
   v=true;
   cfg=d;
   left=clef; 
   right=crig;
   box.x=xx;
   speed=r;
   box.h=cfg*50;
   box.w=50;
   
   if (cfg==1)
      box.y=yy;
   else
   
   if (cfg==2)
      box.y=yy-50;
   else
   
   if (cfg==3)
      box.y=yy-100;
}

//krketanje od leva ka desno i nazad
void Simple_enemy::think()
{
   if(v==true)
      if (box.x < right)
         box.x+=speed;
         else v=false;
            else
            {
               if (box.x > left)
                  box.x-=speed;
               else 
               v=true;
            }
}

///////////////////////////////////////////////////////////////////////
// inteligentni nepriajtelj
///////////////////////////////////////////////////////////////////////

class Smart_enemy 
{
   public:
      Smart_enemy(int xx, int yy,int clef,int crig,int d,int r);
      Smart_enemy(){}
     
      SDL_Rect box;
      
      int Eheight;
      int brojac;
      int start_speed;
      int left,right;
      int speed;
      int cfg;         
      
    
      bool v;
      bool red;
      bool dir_left;
   
      void think();
      void think_again();
      void draw();
}sm_en,sm_en1,sm_en2,sm_en3,sm_en4,sm_en5;

Smart_enemy::Smart_enemy(int xx, int yy,int clef,int crig,int d,int r)
{
   red=false;
   Eheight=d*50;
   v=true;
   cfg=d;
   left=clef; 
   right=crig;
   box.x=xx;
   speed=r;
   start_speed=r;
   box.h=cfg*50;
   box.w=50;
   
  
   
   if (cfg==1)
      box.y=yy;
   else
   
   if (cfg==2)
      box.y=yy-50;
   else
   
   if (cfg==3)
      box.y=yy-100;
      
   };
   
   

   
void Smart_enemy::think_again()
{
     

   if (living==true)
   {
      int playerx=player.box.x;
      int playery=player.box.y;
      
      if ( ((playerx>left)&&(playerx<right+40)) &&   (playery+PLAYERHEIGHT  >=(box.y)) &&  (((playery+PLAYERHEIGHT)-box.y)<Eheight)  )
      { // ova slozena provera proveruje dali je igrac usao u teritoriju neprijatelja
           
      // ukoliko je igrac usao upaljuje se alarm pali se 
      //crveno svetlo i neprijatelj krece punom brzinom da vija igraca
         speed=10;
         Mix_PlayChannel( -1, beep, 0 );
         red=true;
         
         if(playerx<box.x)
         {
            dir_left=false;
            v=true;
         }
         else
            dir_left=true;
      }
      else
      {
         speed=start_speed;
         red=false;
      }
   }else red=false; 
}

void Smart_enemy::think()
{
     

    
   int playerx=player.box.x;
   int playery=player.box.y;
   
   
   if (red==false) // ovaj deo koda obradjuje normalno kretanje od leva na desno
   {    
      if(v==true)
         if (box.x < right)
         {
            box.x+=speed;
         }
         else v=false;
      else
      {
         if (box.x > left)
         {
            box.x-=speed;
         }
         else 
            v=true;
      }
   }  
   else // ovde se obradjuje kretanje pod crvenim svetlom
   {
      if (playerx>box.x)
      {
         dir_left==false; 
         box.x+=speed;
         v=true;
      }
      else
      {
         dir_left==true; 
         box.x-=speed;
         v=false;
      }
   }
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// u zavisnosti od stanja neprijatelja i njegove velicine crta se odredjena slika
//////////////////////////////////////////////////////////////////////////////////////////////////
void Smart_enemy::draw()
{
   if ((cfg==1)&&(red==false))
      apply_surface((box.x)-camera.x,(box.y)-camera.y,spr_enemy1_smart,screen);
      
   else if ((cfg==1)&&(red==true))
      apply_surface((box.x)-camera.x,(box.y)-camera.y,spr_enemy1_smart_red,screen);
      
   if ((cfg==2)&&(red==false))
      apply_surface((box.x)-camera.x,(box.y)-camera.y,spr_enemy2_smart,screen);
      
   else if ((cfg==2)&&(red==true))
      apply_surface((box.x)-camera.x,(box.y)-camera.y,spr_enemy2_smart_red,screen);
      
   if ((cfg==3)&&(red==false))
      apply_surface((box.x)-camera.x,(box.y)-camera.y,spr_enemy3_smart,screen);
      
   else if ((cfg==3)&&(red==true))
      apply_surface((box.x)-camera.x,(box.y)-camera.y,spr_enemy3_smart_red,screen);
}

///////////////////////////////////////////////////////////////////////
// jos pametniji nepriajtelj koji se krece po podlozi koja je dinamicka
///////////////////////////////////////////////////////////////////////

class Smart_enemy2 
{
   public:
      Smart_enemy2(moving_object,int xx, int yy,int d,int r,int hjk);
      Smart_enemy2(){}
      SDL_Rect box;
      
      
      int room;
      int Eheight;
      int brojac;
      int start_speed;
      int left,right;
      int speed;
      int cfg;         
      moving_object j;
      bool moving;
      bool v;
      bool red;
      bool dir_left;
   
      void think(int y,moving_object o);
      void think_again(int y,moving_object o);
      void draw(int y);
}sm_en6,sm_en7;


   
Smart_enemy2::Smart_enemy2(moving_object mob,int xx, int yy,int d,int r,int hjk)
{
   red=false;
   Eheight=d*50;
   v=true;
   cfg=d;
   j=mob;
   left=j.box.x; 
   right=j.box.x+mob.box.w;
   box.x=xx;
   speed=r;
   start_speed=r;
   box.h=cfg*50;
   box.w=50;
   room=hjk;
   moving=true;
   
   if (cfg==1)
      box.y=yy;
   else
   
   if (cfg==2)
      box.y=yy-50;
   else
   
   if (cfg==3)
      box.y=yy-100;
      
   };
   
void Smart_enemy2::think_again(int y,moving_object o)
{
     
     
   if(room==1)
   {
      left=o.box.x;
      right=o.box.x+o.box.w-50;
      box.y=o.box.y;
   }

   if(room==2)
   {
      left=o.box.x-50;
      right=o.box.x+o.box.w-100;
      box.y=o.box.y;
      box.y=y;
   
      if (living==true)
      {
         int playerx=player.box.x;
         int playery=player.box.y;
      
         if ( (((playerx+4)>left+100)&&(playerx<right+70)) &&   ((playery+PLAYERHEIGHT)  >(box.y)) &&  (playery<(box.y+box.h))  )
         { // ova slozena provera proveruje dali je igrac usao u teritoriju neprijatelja
           
         // ukoliko je igrac usao upaljuje se alarm pali se 
         //crveno svetlo i neprijatelj krece punom brzinom da vija igraca
            speed=10;
            Mix_PlayChannel( -1, beep, 0 );
            red=true;
         
            if(playerx<box.x)
            {
               dir_left=false;
               v=true;
            }
            else
               dir_left=true;
         }
         else
         {
            speed=start_speed;
            red=false;
         }
      }else red=false; 
   }
   else if(room==1)
   {
      left=o.box.x;
      right=o.box.x+o.box.w-50;
      box.y=y;
      
      if (living==true)
      {
         int playerx=player.box.x;
         int playery=player.box.y;
      
         if ( (((playerx+4)>left)&&(playerx<right+15)) &&   ((playery+PLAYERHEIGHT)  >(box.y)) &&  (playery<(box.y+box.h))  )
         { // ova slozena provera proveruje dali je igrac usao u teritoriju neprijatelja
           
            // ukoliko je igrac usao upaljuje se alarm pali se 
            //crveno svetlo i neprijatelj krece punom brzinom da vija igraca
            speed=10;
            Mix_PlayChannel( -1, beep, 0 );
            red=true;
         
            if(playerx<box.x)
            {
               dir_left=false;
               v=true;
            }
            else
               dir_left=true;
         }
         else
         {
            speed=start_speed;
            red=false;
         }
      }else red=false; 
   }
}

void Smart_enemy2::think(int y,moving_object o)
{
     
   if(room==1)
   {
      left=o.box.x;
      right=o.box.x+o.box.w-50;
      box.y=o.box.y;
   }

   if(room==2)
   {
      left=o.box.x+50;
      right=o.box.x+o.box.w-100;
      box.y=o.box.y;
    
      int playerx=player.box.x;
      int playery=player.box.y;
   
   
      if (red==false) // ovaj deo koda obradjuje normalno kretanje od leva na desno
      {    
         if(v==true)
            if (box.x < right+15)
            {
               box.x+=speed;
            }
            else v=false;
         else
         {
            if (box.x > left)
            {
               box.x-=speed;
            }
            else 
               v=true;
         }
      }  
      else // ovde se obradjuje kretanje pod crvenim svetlom
      {
         if (playerx>box.x)
         {
            dir_left==false; 
            box.x+=speed;
            v=true;
         }
         else
         {
            dir_left==true; 
            box.x-=speed;
            v=false;
         }
      }
   }
   else if (room==1)
   {
      left=o.box.x;
      right=o.box.x+o.box.w-50;
      box.y=o.box.y;
        
      int playerx=player.box.x;
      int playery=player.box.y;

      if (red==false) // ovaj deo koda obradjuje normalno kretanje od leva na desno
      {    
         if(v==true)
            if (box.x < right)
            {
               box.x+=speed;
            }
            else v=false;
         else
         {
            if (box.x > left)
            {
               box.x-=speed;
            }
            else 
               v=true;
         }
      }  
      else // ovde se obradjuje kretanje pod crvenim svetlom
      {
         if (playerx>box.x)
         {
            dir_left==false; 
            box.x+=speed;
            v=true;
         }
         else
         {
            dir_left==true; 
            box.x-=speed;
            v=false;
         }
      }
   }
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// u zavisnosti od stanja neprijatelja i njegove velicine crta se odredjena slika
//////////////////////////////////////////////////////////////////////////////////////////////////
void Smart_enemy2::draw(int y)
{
   if ((cfg==1)&&(red==false))
      apply_surface((box.x)-camera.x,y-camera.y,spr_enemy1_smart,screen);
      
   else if ((cfg==1)&&(red==true))
      apply_surface((box.x)-camera.x,y-camera.y,spr_enemy1_smart_red,screen);
      
   if ((cfg==2)&&(red==false))
      apply_surface((box.x)-camera.x,y-camera.y,spr_enemy2_smart,screen);
      
   else if ((cfg==2)&&(red==true))
      apply_surface((box.x)-camera.x,y-camera.y,spr_enemy2_smart_red,screen);
      
   if ((cfg==3)&&(red==false))
      apply_surface((box.x)-camera.x,y-camera.y,spr_enemy3_smart,screen);
      
   else if ((cfg==3)&&(red==true))
      apply_surface((box.x)-camera.x,y-camera.y,spr_enemy3_smart_red,screen);
}



#endif
