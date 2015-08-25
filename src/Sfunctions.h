#ifndef SFUNCTIONS_H
#define SFUNCTIONS_H

#include "Splayer.h"
#include "moving_object.h"
#include "SDL/SDL_rotozoom.h"

SDL_Surface *load_image_ck_black( std::string filename ) 
{
    
   SDL_Surface* loadedImage = NULL; // obicna slika
   SDL_Surface* optimizedImage = NULL;  // slika optimizovana za bolji render
   loadedImage = SDL_LoadBMP( filename.c_str() );
   
   if( loadedImage != NULL )
   { 
      optimizedImage = SDL_DisplayFormat( loadedImage );
     
      SDL_FreeSurface( loadedImage );// ovde odbacujemo obicnu sliku jel nam vise netreba
      if( optimizedImage != NULL )
      {//ovde se podesava transparencija i boja koja se nece videti u mom slucaju roza (255,0,255)
         SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0, 0 ) ); 
      }
   }
    return optimizedImage;
}



#include "moving_object.h"
void check_cool_collision( SDL_Rect &A, SDL_Rect &B ,CPlayer &player,moving_object mobject)
{
     
///////////////////////////////////////////////////////////////////////
// slozena provera sudara gde se meri rastojanje 
//  centara izmedju 2 pravougaonika
///////////////////////////////////////////////////////////////////////
  int cxa, cya;
   int cxb, cyb;
   
   cxa = A.x+A.w/2;
   cya = A.y+A.h/2;
   
   cxb = B.x+B.w/2;
   cyb = B.y+B.h/2; 
   
   int dx = cxb-cxa;
   int dy = cyb-cya;
   
   int sx = (dx>0 ? 1 : -1);
   int sy = (dy>0 ? 1 : -1);

   int nx = A.w/2+B.w/2 - abs(dx);
   int ny = A.h/2+B.h/2 - abs(dy);

   
   if (nx > 0 && ny > 0)//provera dali se desila kolizija
   {
      if (nx < ny)//ukoliko je po x osi
	  {
        VELMOVING=3;
	      
          A.x-=nx*sx;
      }
	  else// y osi
      {
	     A.y-=ny*sy;
	   
         if(ny*sy<0)//sudar od dole
         {
           if(player.vely<0)
             player.vely=1;
         }
         
	     if(ny*sy>0)/// sudar od gore
         {
            player.ON_GROUND=true;

            
            if(player.vely>1)
            player.vely=5;
            
            player.unlockjump();
            
            if (W_LEFT==false && W_RIGHT==false || (living==false))
            {
               player.box.x+=mobject.velx;
            }

          }
          else
          {
             player.ON_GROUND=false;
             player.lockjump=true;
          }     
       }  
   }
}


void check_cool_cutter_collision( SDL_Rect &A, SDL_Rect &B ,CPlayer &player,moving_object mobject)
{
   // ista rpvoera sudara samo za sekac
   int cxa, cya;
   int cxb, cyb;
   
   cxa = A.x+A.w/2;
   cya = A.y+A.h/2;
   
   cxb = B.x+B.w/2;
   cyb = B.y+B.h/2; 
   
   int dx = cxb-cxa; ///razdaljina centara po x osi
   int dy = cyb-cya; /// razdaljina cenatara po y osi
   
   int sx = (dx>0 ? 1 : -1);
   int sy = (dy>0 ? 1 : -1);

   int nx = A.w/2+B.w/2 - abs(dx);
   int ny = A.h/2+B.h/2 - abs(dy);

   

   
   if (nx > 0 && ny > 0)
   {
      if (nx < ny)
	  {
          if(GLOBAL_TIME%10==0)
	      VELMOVING*=0.9; 
	      
	      
          A.x-=nx*sx;
      }
	  else
      {
	     A.y-=ny*sy;
	   
         if(ny*sy<0)
         {
            //player.vely=5;
            player.lockjump=true;
            living=false;
         }
         
	     if(ny*sy>0)
         {
            player.ON_GROUND=true;
            player.vely=5;
            player.unlockjump();
            
            if (W_LEFT==false && W_RIGHT==false || (living==false))
            {
               player.box.x+=mobject.velx;
            }

          }
          else
          {
             player.ON_GROUND=false;
             player.lockjump=true;
          }     
       }  
   }
}

#include "Senemys.h"
void check_cool_push_collision( SDL_Rect &A, SDL_Rect &B ,CPlayer &player,pushing_enemy pobject)
{
   //provera sudara za gurajuce objekte
   int cxa, cya;
   int cxb, cyb;
   
   cxa = A.x+A.w/2;
   cya = A.y+A.h/2;
   
   cxb = B.x+B.w/2;
   cyb = B.y+B.h/2; 
   
   int dx = cxb-cxa;
   int dy = cyb-cya;
   
   int sx = (dx>0 ? 1 : -1);
   int sy = (dy>0 ? 1 : -1);

   int nx = A.w/2+B.w/2 - abs(dx);
   int ny = A.h/2+B.h/2  - abs(dy);

   
   if (nx > 0 && ny > 0)
   {
      if (nx < ny)
	  {
	      VELMOVING=5; 
          A.x-=nx*sx;  
      }
   }
}
  
SDL_Surface *create_transparent_image(SDL_Surface *image)//transparencija crne slike
{
   SDL_Surface *transparent;
  SDL_SetColorKey( image, SDL_SRCCOLORKEY, SDL_MapRGB( image->format, 0, 0, 0 ) );
   return image;
}


#include "SDL/SDL_rotozoom.h"
void load_roll()//ucitavanje lopte i rotiranje u memoriji
{     
   SDL_Surface *temp_ball=load_image_ck_black("grafika/enemy1.bmp");

   for(int q=1; q<361;q++ )
   {
      spr_ball[q]=rotozoomSurface(temp_ball,q,1,0);
      create_transparent_image(spr_ball[q]); 
   }

   spr_ball[0]=rotozoomSurface(spr_ball[180],180,1,0);
   create_transparent_image(spr_ball[0]);
}
  
//ucitavaje fajlova  
bool load_files()
{
     
     
     
   gun = Mix_LoadWAV( "gunshot2.wav" );
   boink = Mix_LoadWAV( "boink2.wav" );
   button_sound = Mix_LoadWAV( "beep3.wav" );
   beep = Mix_LoadWAV( "beep7.wav" );
   a = Mix_LoadWAV( "a.wav" );
   kraj = Mix_LoadWAV( "kraj.wav" );
   loser = Mix_LoadWAV( "loser.wav" );
   zap = Mix_LoadWAV( "zap.wav" );

   spr_lift_long_upright=load_image("grafika/uspravno.bmp");
   spr_pushing_enemy[0][1]=load_image("grafika/p22.bmp");
   spr_pushing_enemy[1][1]=load_image("grafika/p21.bmp");
     
   spr_pushing_enemy[0][2]=load_image("grafika/p31.bmp");
   spr_pushing_enemy[1][2]=load_image("grafika/p32.bmp");
     
   spr_short=load_image("grafika/object4.bmp");
     
     
   spr_sekac=load_image("grafika/sekac.bmp");
     
   spr_lift_fat =load_image("grafika/object3.bmp"); 
   spr_lift_medium =load_image("grafika/object2brown.bmp"); 
   spr_stefan =load_image("grafika/object.bmp"); 
     
   spr_bar =load_image("grafika/bar.bmp");   
    
   spr_thorns =load_image("grafika/siljnci2.bmp"); 
    
   spr_enemy1 =load_image("grafika/enemy1.bmp");   

   spr_enemy2 =load_image("grafika/enemy2.bmp");   
   spr_enemy3 =load_image("grafika/enemy3.bmp");  
        
   spr_enemy1_smart =load_image("grafika/enemy_smart_1.bmp");   
   spr_enemy2_smart =load_image("grafika/enemy_smart_2.bmp");   
   spr_enemy3_smart =load_image("grafika/enemy_smart_3.bmp"); 
     
   spr_boolet =load_image("grafika/enemy3.bmp"); 
    
   spr_dugme =load_image("grafika/dugme-1.bmp");
    
   spr_lift_long=load_image("grafika/object1brown.bmp");
     
   spr_dead =load_image("grafika/player/mrtav.bmp");
    
   spr_head1 =load_image("grafika/glava-1.bmp");
   spr_head2 =load_image("grafika/glava-2.bmp");
   spr_head3 =load_image("grafika/glava-3.bmp");
    
   spr_zeleno =load_image("grafika/zeleno.bmp"); 
   spr_crveno =load_image("grafika/crveno.bmp"); 
    
   spr_enemy1_smart_red =load_image("grafika/enemy_smart_red_1.bmp");   
   spr_enemy2_smart_red =load_image("grafika/enemy_smart_red_2.bmp");   
   spr_enemy3_smart_red =load_image("grafika/enemy_smart_red_3.bmp"); 
      
   spr_shit= load_image("grafika/mario.bmp"); 
   spr_boolet_right =load_image("grafika/metak_desno.bmp"); 
   spr_boolet_left =load_image("grafika/metak_levo.bmp"); 
          
   spr_t[0] =load_image("grafika/trava-levo.bmp");                           // 1
   spr_t[1] =load_image("grafika/trava-sredina.bmp");                        // 2
   spr_t[2] =load_image("grafika/trava-desno.bmp");                          // 3
   spr_t[3] =load_image("grafika/trava-duboko-levo.bmp");                    // 4
   spr_t[4] =load_image("grafika/trava-duboko-sredina.bmp");                 // 5
   spr_t[5] =load_image("grafika/trava-duboko-desno.bmp");                   // 6
   spr_t[6] =load_image("grafika/drvo-jednodelno.bmp");                      // 7 
   spr_t[7] =load_image("grafika/drvo-krosnja-levo.bmp");                    // 8
   spr_t[8] =load_image("grafika/drvo-krosnja-desno.bmp");                   // 9
   spr_t[9] =load_image("grafika/drvo-krosnja-sredina-puno.bmp");            // 10
   spr_t[10] =load_image("grafika/drvo-krosnja-sredina.bmp");                // 11
   spr_t[11] =load_image("grafika/zid-cvrst.bmp");                           // 12
   spr_t[12] =load_image("grafika/zid-cigla.bmp");                           // 13
   spr_t[13] =load_image("grafika/skakanje-1.bmp");    
   spr_t[14] =load_image("grafika/zid-leden.bmp");  
 
                  
   spr_player_right[0]=load_image("grafika/player/stoji.bmp");
   spr_player_right[1]=load_image("grafika/player/hoda-0.bmp");
   spr_player_right[2]=load_image("grafika/player/hoda-1.bmp");
   spr_player_right[3]=load_image("grafika/player/hoda-2.bmp");
   spr_player_right[4]=load_image("grafika/player/hoda-3.bmp");
   spr_player_right[5]=load_image("grafika/player/hoda-2.bmp");
   spr_player_right[6]=load_image("grafika/player/hoda-1.bmp");			
   spr_player_right[7]=load_image("grafika/player/skoci.bmp");
	
   spr_player_left[0]=load_image("grafika/player/stoji-levo.bmp");
   spr_player_left[1]=load_image("grafika/player/hoda-levo-0.bmp");
   spr_player_left[2]=load_image("grafika/player/hoda-levo-1.bmp");
   spr_player_left[3]=load_image("grafika/player/hoda-levo-2.bmp");
   spr_player_left[4]=load_image("grafika/player/hoda-levo-3.bmp");
   spr_player_left[5]=load_image("grafika/player/hoda-levo-2.bmp");
   spr_player_left[6]=load_image("grafika/player/hoda-levo-1.bmp");			
   spr_player_left[7]=load_image("grafika/player/skoci-levo.bmp");
	
   spr_player_skija[0]=load_image("grafika/player/skija-levo.bmp");			
   spr_player_skija[1]=load_image("grafika/player/skija-desno.bmp");
	
   spr_light[0]=load_image("grafika/svetlo-1.bmp");
   spr_light[1]=load_image("grafika/svetlo-2.bmp");
   spr_light[2]=load_image("grafika/svetlo-3.bmp");
   spr_light[3]=load_image("grafika/svetlo-4.bmp");
   spr_light[4]=load_image("grafika/svetlo-5.bmp");
   spr_light[5]=load_image("grafika/svetlo-6.bmp");
   spr_light[6]=load_image("grafika/svetlo-7.bmp");
   spr_light[7]=load_image("grafika/svetlo-8.bmp");
   spr_light[8]=load_image("grafika/svetlo-94.bmp");
   spr_light[9]=load_image("grafika/svetlo-10.bmp");
	spr_light[10]=load_image("grafika/svetlo-11.bmp");
	spr_light[11]=load_image("grafika/svetlo-10.bmp");
	spr_light[12]=load_image("grafika/svetlo-94.bmp");
	spr_light[13]=load_image("grafika/svetlo-8.bmp");
	spr_light[14]=load_image("grafika/svetlo-7.bmp");
    spr_light[15]=load_image("grafika/svetlo-6.bmp");
    spr_light[16]=load_image("grafika/svetlo-5.bmp");
    spr_light[17]=load_image("grafika/svetlo-4.bmp");
    spr_light[18]=load_image("grafika/svetlo-3.bmp");
    spr_light[19]=load_image("grafika/svetlo-2.bmp");
    spr_light[20]=load_image("grafika/svetlo-1.bmp");
    
    spr_height_max[0]=load_image("grafika/vi-1.bmp");
    spr_height_max[1]=load_image("grafika/vi-2.bmp");
    spr_height_max[2]=load_image("grafika/vi-3.bmp");
    spr_height_max[3]=load_image("grafika/vi-4.bmp");
    spr_height_max[4]=load_image("grafika/vi-5.bmp");
    spr_height_max[5]=load_image("grafika/vi-6.bmp");
    spr_height_max[6]=load_image("grafika/vi-7.bmp");
    spr_height_max[7]=load_image("grafika/vi-8.bmp");
    spr_height_max[8]=load_image("grafika/vi-9.bmp");
    spr_height_max[9]=load_image("grafika/vi-10.bmp");
    spr_height_max[10]=load_image("grafika/vi-11.bmp");
    spr_height_max[11]=load_image("grafika/vi-12.bmp");
    spr_height_max[12]=load_image("grafika/vi-13.bmp");
    spr_height_max[13]=load_image("grafika/vi-14.bmp");
    spr_height_max[14]=load_image("grafika/vi-15.bmp");
    spr_height_max[15]=load_image("grafika/vi-16.bmp");
    spr_height_max[16]=load_image("grafika/vi-17.bmp");
    spr_height_max[17]=load_image("grafika/vi-18.bmp");
    spr_height_max[18]=load_image("grafika/vi-19.bmp");
    spr_height_max[19]=load_image("grafika/vi-20.bmp");
    spr_height_max[20]=load_image("grafika/vi-21.bmp");
    spr_height_max[21]=load_image("grafika/vi-22.bmp");
    spr_height_max[22]=load_image("grafika/vi-23.bmp");
    spr_height_max[23]=load_image("grafika/vi-24.bmp");
    spr_height_max[24]=load_image("grafika/vi-25.bmp");
    spr_height_max[25]=load_image("grafika/vi-26.bmp");
    spr_height_max[26]=load_image("grafika/vi-27.bmp");
    spr_height_max[27]=load_image("grafika/vi-28.bmp");
    spr_height_max[28]=load_image("grafika/vi-29.bmp");
    spr_height_max[29]=load_image("grafika/vi-30.bmp");
    spr_height_max[30]=load_image("grafika/vi-31.bmp");
    spr_height_max[31]=load_image("grafika/vi-32.bmp");
    spr_height_max[32]=load_image("grafika/vi-33.bmp");
    spr_height_max[33]=load_image("grafika/vi-34.bmp");
    spr_height_max[34]=load_image("grafika/vi-35.bmp");
    spr_height_max[35]=load_image("grafika/vi-36.bmp");
    spr_height_max[36]=load_image("grafika/vi-37.bmp");
    spr_height_max[37]=load_image("grafika/vi-38.bmp");
    spr_height_max[38]=load_image("grafika/vi-39.bmp");
    spr_height_max[39]=load_image("grafika/vi-40.bmp");
    spr_height_max[40]=load_image("grafika/vi-41.bmp");
    spr_height_max[41]=load_image("grafika/vi-42.bmp");
    spr_height_max[42]=load_image("grafika/vi-43.bmp");
    spr_height_max[43]=load_image("grafika/vi-44.bmp");
    spr_height_max[44]=load_image("grafika/vi-45.bmp");
    spr_height_max[45]=load_image("grafika/vi-46.bmp");
    spr_height_max[46]=load_image("grafika/vi-47.bmp");
    spr_height_max[47]=load_image("grafika/vi-48.bmp");
    spr_height_max[48]=load_image("grafika/vi-49.bmp");
    spr_height_max[49]=load_image("grafika/vi-50.bmp");
    spr_height_max[50]=load_image("grafika/vi-51.bmp");
    spr_height_max[51]=load_image("grafika/vi-52.bmp");
    spr_height_max[52]=load_image("grafika/vi-53.bmp");
    spr_height_max[53]=load_image("grafika/vi-54.bmp");
    spr_height_max[54]=load_image("grafika/vi-55.bmp");
    spr_height_max[55]=load_image("grafika/vi-56.bmp");
    spr_height_max[56]=load_image("grafika/vi-57.bmp");
    spr_height_max[57]=load_image("grafika/vi-58.bmp");
    spr_height_max[58]=load_image("grafika/vi-59.bmp");
    spr_height_max[59]=load_image("grafika/vi-60.bmp");
    spr_height_max[60]=load_image("grafika/vi-61.bmp");
    spr_height_max[61]=load_image("grafika/vi-62.bmp");
    spr_height_max[62]=load_image("grafika/vi-63.bmp");
    spr_height_max[63]=load_image("grafika/vi-64.bmp");
    spr_height_max[64]=load_image("grafika/vi-65.bmp");
    spr_height_max[65]=load_image("grafika/vi-66.bmp");
    spr_height_max[66]=load_image("grafika/vi-67.bmp");
    spr_height_max[67]=load_image("grafika/vi-68.bmp");
    spr_height_max[68]=load_image("grafika/vi-69.bmp");
    spr_height_max[69]=load_image("grafika/vi-70.bmp");
    spr_height_max[70]=load_image("grafika/vi-71.bmp");
    spr_height_max[71]=load_image("grafika/vi-72.bmp");
    spr_height_max[72]=load_image("grafika/vi-73.bmp");
    spr_height_max[73]=load_image("grafika/vi-74.bmp");
    spr_height_max[74]=load_image("grafika/vi-75.bmp");
    spr_height_max[75]=load_image("grafika/vi-76.bmp");
    spr_height_max[76]=load_image("grafika/vi-77.bmp");
    spr_height_max[77]=load_image("grafika/vi-78.bmp");
    spr_height_max[78]=load_image("grafika/vi-79.bmp");
    spr_height_max[79]=load_image("grafika/vi-80.bmp");
    spr_height_max[80]=load_image("grafika/vi-81.bmp");
    spr_height_max[81]=load_image("grafika/vi-82.bmp");
    spr_height_max[82]=load_image("grafika/vi-83.bmp");
    spr_height_max[83]=load_image("grafika/vi-84.bmp");
    spr_height_max[84]=load_image("grafika/vi-85.bmp");
    spr_height_max[85]=load_image("grafika/vi-86.bmp");
    spr_height_max[86]=load_image("grafika/vi-87.bmp");
    spr_height_max[87]=load_image("grafika/vi-88.bmp");
    spr_height_max[88]=load_image("grafika/vi-89.bmp");
    spr_height_max[89]=load_image("grafika/vi-90.bmp");
    spr_height_max[90]=load_image("grafika/vi-91.bmp");
    spr_height_max[91]=load_image("grafika/vi-92.bmp");
    spr_height_max[92]=load_image("grafika/vi-93.bmp");
    spr_height_max[93]=load_image("grafika/vi-94.bmp");
    spr_height_max[94]=load_image("grafika/vi-95.bmp");
    spr_height_max[95]=load_image("grafika/vi-96.bmp");
    spr_height_max[96]=load_image("grafika/vi-97.bmp");
    spr_height_max[97]=load_image("grafika/vi-98.bmp");
    spr_height_max[98]=load_image("grafika/vi-99.bmp");
    spr_height_max[99]=load_image("grafika/vi-100.bmp");
    spr_height_max[100]=load_image("grafika/vi-101.bmp");
    spr_height_max[101]=load_image("grafika/vi-102.bmp");
    spr_height_max[102]=load_image("grafika/vi-103.bmp");
    spr_height_max[103]=load_image("grafika/vi-104.bmp");
    spr_height_max[104]=load_image("grafika/vi-105.bmp");
    spr_height_max[105]=load_image("grafika/vi-106.bmp");
    spr_height_max[106]=load_image("grafika/vi-107.bmp");

    spr_dugmad[0]=load_image("grafika/dugme-1");
    spr_dugmad[1]=load_image("grafika/dugme-2");
    spr_dugmad[2]=load_image("grafika/dugme-3");

    spr_emiter1=load_image("grafika/emiter1.bmp");
    spr_emiter2=load_image("grafika/emiter2.bmp");
	
	spr_background=load_image("grafika/bg.bmp");
	
	spr_game_over=load_image("grafika/kraj.bmp");
	spr_game_win=load_image("grafika/bravo.bmp");
	
	spr_finish_line=load_image("grafika/finish.bmp");
}



//////////////////////////////////
//iscrtavanje animacije lasera
//////////////////////////////////
void bar_draw()
{
     
   if (beam==true)
   {
      if (light_count>19)
         light_count=0;
      else
         light_count++;//ovde se vrti animacija

      spr_light_bar=spr_light[light_count];
   
      apply_surface(bar.x-camera.x,bar.y-camera.y,spr_light_bar,screen);//lepljenje laseraa na ekran
   }  

}


//////////////////////////////////////////////////
// dugme za prekid lasera
////////////////////////////////////////////////////
void button()
{
   SDL_Rect dugme;
     
   dugme.x=1450; 
   dugme.y=1120;
   dugme.h=34;
   dugme.w=50;
   
   if (beam==true)
   {
      spr_dugme_pr=spr_dugme;
      spr_svetlost=spr_crveno;
   }
     
   if (check_collision( player.box, dugme ))// kaad igrac stane na dugme tada prekine laser
   {
      if (beam==true)
         Mix_PlayChannel( -1, zap, 0 );// pusta se laser muzika
         
      beam=false; 
      
   }

   if (beam==false)
   {
      spr_dugme_pr=NULL;
      spr_svetlost=spr_zeleno;
   }
   
   apply_surface(dugme.x-camera.x,dugme.y-camera.y,spr_dugme_pr,screen);//dugme se iscrtava na ekran
   apply_surface(1450-camera.x,1150-camera.y,spr_svetlost,screen);
}

////////////////////////////////////////////////////////
//   izracunavanje zivota
///////////////////////////////////////////////////////
void calculate_life()
{
   if(lives==3)
   {
      apply_surface(3,707,spr_head1,screen);
      apply_surface(36,707,spr_head2,screen);
      apply_surface(67,707,spr_head3,screen);
   }
   
   if(lives==2)
   {
      apply_surface(3,707,spr_head1,screen);
      apply_surface(36,707,spr_head2,screen);
   }
   
   if(lives==1)
   {
      apply_surface(3,707,spr_head1,screen);
   }
   
   if(lives<1)
   {
      dead_count++;         
      apply_surface(0,0,spr_game_over,screen);
            if(playable_kraj==true)
      {
         Mix_PlayChannel( -1, loser, 0 );
         playable_kraj=false;
}
      
      if(dead_count>100)
      {
         set_next_state( STATE_MAIN_MENU );
         dead_count=0;
         playable_kraj=true;
      }
   }
   
   if(win==true)
   {
      if(playable_kraj==true)
      {
         Mix_PlayChannel( -1, kraj, 0 );            
         playable_kraj=false;
      }
      
      dead_count++;         
      apply_surface(0,0,spr_game_win,screen);
      
      if(dead_count>100)
      {set_next_state( STATE_MAIN_MENU );
          dead_count=0;
          playable_kraj=true;
          
      }
   }
}
/////////////////////////////////////////////////////////////////////////////////
//   izracunavanje me progress bara za visinu
/////////////////////////////////////////////////////////////////////////////////
void calculate_height()
{
   if (!(player.box.y>4500))//racuna se visina SVE DOK igrac nepadne u provaliju
   {
      int g= ((player.box.y+50)*107)/4500;//ovde se koristi proporcija da bi se dobila vrednost visine
      
      
      if ((g-107)>106) g=104;
      
      spr_height=spr_height_max[abs(g-107)];
   }
}

#endif
