#ifndef MPFUNCTIONS_H
#define MPFUNCTIONS_H

#include "MPglobal.h"
void calculate_lives(MPlayer &a,MPlayer &b)
//ovde se izracunavaju energije 2 protivnicka igraca
{
if(a.lives>0)
{
   m_spr_left_bar=m_spr_red[a.lives-1];
}
       
if(b.lives>0)
{
   m_spr_right_bar=m_spr_blue[b.lives-1];
}
    
if(b.lives<1)
{
   m_spr_right_bar=m_spr_loser_right;
   m_spr_left_bar=m_spr_winner_left;
   
   if(GLOBAL_TIME%30==0)
      set_next_state( STATE_MAIN_MENU );
}
     
if(a.lives<1)
{
   m_spr_left_bar=m_spr_loser_left;
   m_spr_right_bar=m_spr_winner_right;
   if(GLOBAL_TIME%30==0)
      set_next_state( STATE_MAIN_MENU );
}
     
apply_surface(0,0,m_spr_left_bar,screen);
apply_surface(752,0,m_spr_right_bar,screen); 
}

#include "moving_object.h"
void check_cool_collision( SDL_Rect &A, SDL_Rect &B ,MPlayer &player,moving_object mobject,int JUMP)
{
 //slozena provera sudara tako sto se uporedjuje razdaljina centara 2 Rect-a  
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

   
   if (nx > 0 && ny > 0) //ukoliko je doslo do kolizije
   {
      if (nx < ny)//sudar sa strane
	  {
	       player.VELMOVING=3;	      
          A.x-=nx*sx;
      }
	  else// u suprotnom sudar po y osi
      {
	     A.y-=ny*sy;
            
         if(ny*sy<0)//sudar od dole
         {
           if(player.vely<0)
             player.vely=1;
         }
         
	     if(ny*sy>0)//sudar od gore
         {
            player.ON_GROUND=true;
            
            if(player.vely>1)
            player.vely=5;

            player.lockjump = false;
            
            if (player.W_LEFT==false && player.W_RIGHT==false || (player.lives<1))
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

bool check_ultra_collision( SDL_Rect &A, SDL_Rect &B)
{//provera slozene kolizije ali BEZ reakcije
   
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

   
   if (nx > 0 && ny > 0)
   {
     return true;
       
   }
   else return false;
}

bool MPload_files()
{
    m_spr_player_right[0][0]=load_image("grafika/player1/stoji.bmp");
	m_spr_player_right[0][1]=load_image("grafika/player1/hoda-0.bmp");
	m_spr_player_right[0][2]=load_image("grafika/player1/hoda-1.bmp");
	m_spr_player_right[0][3]=load_image("grafika/player1/hoda-2.bmp");
	m_spr_player_right[0][4]=load_image("grafika/player1/hoda-3.bmp");
	m_spr_player_right[0][5]=load_image("grafika/player1/hoda-2.bmp");
	m_spr_player_right[0][6]=load_image("grafika/player1/hoda-1.bmp");			
	m_spr_player_right[0][7]=load_image("grafika/player1/skoci.bmp");
	
	m_spr_player_left[0][0]=load_image("grafika/player1/stoji-levo.bmp");
	m_spr_player_left[0][1]=load_image("grafika/player1/hoda-levo-0.bmp");
	m_spr_player_left[0][2]=load_image("grafika/player1/hoda-levo-1.bmp");
	m_spr_player_left[0][3]=load_image("grafika/player1/hoda-levo-2.bmp");
	m_spr_player_left[0][4]=load_image("grafika/player1/hoda-levo-3.bmp");
	m_spr_player_left[0][5]=load_image("grafika/player1/hoda-levo-2.bmp");
	m_spr_player_left[0][6]=load_image("grafika/player1/hoda-levo-1.bmp");			
	m_spr_player_left[0][7]=load_image("grafika/player1/skoci-levo.bmp");
     
    m_spr_dead[0] =load_image("grafika/player1/mrtav.bmp");
     
    m_spr_player_right[1][0]=load_image("grafika/player2/stoji.bmp");
	m_spr_player_right[1][1]=load_image("grafika/player2/hoda-0.bmp");
	m_spr_player_right[1][2]=load_image("grafika/player2/hoda-1.bmp");
	m_spr_player_right[1][3]=load_image("grafika/player2/hoda-2.bmp");
	m_spr_player_right[1][4]=load_image("grafika/player2/hoda-3.bmp");
	m_spr_player_right[1][5]=load_image("grafika/player2/hoda-2.bmp");
	m_spr_player_right[1][6]=load_image("grafika/player2/hoda-1.bmp");			
	m_spr_player_right[1][7]=load_image("grafika/player2/skoci.bmp");
	
	m_spr_player_left[1][0]=load_image("grafika/player2/stoji-levo.bmp");
	m_spr_player_left[1][1]=load_image("grafika/player2/hoda-levo-0.bmp");
	m_spr_player_left[1][2]=load_image("grafika/player2/hoda-levo-1.bmp");
	m_spr_player_left[1][3]=load_image("grafika/player2/hoda-levo-2.bmp");
	m_spr_player_left[1][4]=load_image("grafika/player2/hoda-levo-3.bmp");
	m_spr_player_left[1][5]=load_image("grafika/player2/hoda-levo-2.bmp");
	m_spr_player_left[1][6]=load_image("grafika/player2/hoda-levo-1.bmp");			
	m_spr_player_left[1][7]=load_image("grafika/player2/skoci-levo.bmp");
     
    m_spr_dead[1] =load_image("grafika/player2/mrtav.bmp");

    m_spr_boolet =load_image("grafika/enemy3.bmp"); 
      
    m_spr_boolet_right =load_image("grafika/metak_desno2.bmp"); 
    m_spr_boolet_left =load_image("grafika/metak_levo2.bmp");

	m_spr_t[0] =load_image("grafika/trava-levo.bmp");                           // 1
	m_spr_t[1] =load_image("grafika/trava-sredina.bmp");                        // 2
	m_spr_t[2] =load_image("grafika/trava-desno.bmp");                          // 3
	m_spr_t[3] =load_image("grafika/trava-duboko-levo.bmp");                    // 4
	m_spr_t[4] =load_image("grafika/trava-duboko-sredina.bmp");                 // 5
	m_spr_t[5] =load_image("grafika/trava-duboko-desno.bmp");                   // 6
	m_spr_t[6] =load_image("grafika/drvo-jednodelno.bmp");                      // 7 
	m_spr_t[7] =load_image("grafika/drvo-krosnja-levo.bmp");                    // 8
    m_spr_t[8] =load_image("grafika/drvo-krosnja-desno.bmp");                   // 9
	m_spr_t[9] =load_image("grafika/drvo-krosnja-sredina-puno.bmp");            // 10
	m_spr_t[10] =load_image("grafika/drvo-krosnja-sredina.bmp");                // 11
	m_spr_t[11] =load_image("grafika/zid-cvrst.bmp");                           // 12
	m_spr_t[12] =load_image("grafika/zid-cigla.bmp");  
	
	m_spr_player[0]=load_image("grafika/left.bmp");
	m_spr_player[1]=load_image("grafika/right.bmp");
	
	m_spr_background=load_image("grafika/bg.bmp");
	
    m_spr_loser_left=load_image("grafika/red/loser.bmp");
    m_spr_winner_left=load_image("grafika/red/winner.bmp");
    m_spr_loser_right=load_image("grafika/blue/loser.bmp");
    m_spr_winner_right=load_image("grafika/blue/winner.bmp");

    m_spr_blue[0]=load_image("grafika/blue/1.bmp");  
    m_spr_blue[1]=load_image("grafika/blue/2.bmp");  
    m_spr_blue[2]=load_image("grafika/blue/3.bmp");  
    m_spr_blue[3]=load_image("grafika/blue/4.bmp");  
    m_spr_blue[4]=load_image("grafika/blue/5.bmp");  
    
    m_spr_red[0]=load_image("grafika/red/1.bmp");
    m_spr_red[1]=load_image("grafika/red/2.bmp");
    m_spr_red[2]=load_image("grafika/red/3.bmp");
    m_spr_red[3]=load_image("grafika/red/4.bmp");
    
    m_spr_red[4]=load_image("grafika/red/5.bmp");
}

#endif
