#ifndef SPLAYER_H
#define SPLAYER_H

#include "Sglobal.h"
#include "Smap.h"
#include "global.h"


class CPlayer
{
	public:
		void think();		
		void draw();
		void handle_events();

		CPlayer();
         
        SDL_Rect box;
				
		int h, w,x,y;	
        int count;	
		int velx, vely;		//brzina po osama
		
		bool faceright;		//grafika desno

		int switchInAirDir;

		bool lockjump;		
		bool jumping;
        int airx;
 
        bool ON_GROUND; 

        int friction;

		void collision_detection_map();	
        void set_camera();							

		bool collision_ver(int x, int y, int &tilecoordx);			//vertikalni sudar
		bool collision_hor_up(int x, int y, int &tilecoordy);		//horiszontaln
		int collision_hor_down(int x, int y, int &tilecoordy);		
		
	

		void unlockjump();										
}player;


CPlayer::CPlayer()
{
    box.x=100;
    box.y=4200;

	box.h	=h	= PLAYERHEIGHT;	
	box.w	=w	= PLAYERWIDTH;

	velx	= 0;		
	vely	= 0;
	switchInAirDir = 0;
	
	ON_GROUND=false;

    friction=1;
    count   = 0;
	lockjump = true;	
	faceright = true;		
	jumping = false;

}

void CPlayer::unlockjump()
{		
	
	switchInAirDir = 0;
	//ova funkcija je pozvana kada igra dotakne zemlju
	if(!jumping || !keystates[SDLK_RSHIFT]){
		lockjump = false;
		jumping = false;
	}
}
///////////////////////////////////////////////////////////////////////////////
//OVDE SE IGRAC ANIMIRA
///////////////////////////////////////////////////////////////////////////////
void CPlayer::draw()
{       

    
   if (living==true)
   {
      if (ON_GROUND==true) //ako je na zemlji onda ce se obradjivati hodanje
      {
         if (abs(velx)>0)
         {	
	        if(faceright)// ako je na podu i okrenut desno  onda ce se menjati trcuce slike za desno
	        {
                            
                if(friction>1)
                {
                spr_player=spr_player_skija[1];
                }
                else
                {           
                if (!(count>5))
                count+=1;
                else
                count=0;
                spr_player=spr_player_right[(int)count];
                }

            }
    
	       if(!faceright) // ako je na podu i okrenut levo onda ce se menjati trcuce slike za levo
	       {
                          
                if(friction>1)
                {
                spr_player=spr_player_skija[0];
                }
                else
                {
                    
              if (!(count>5))
              count+=1;
              else
              count=0;

              spr_player=spr_player_left[(int)count];
              }
           }
        }
        else //ako ne trci onda ce se prikazati stojece slike
        {
           if (faceright)// stojeca slika za desno
           {
                if(friction>1)
                {
                spr_player=spr_player_skija[1];
                }else
              spr_player=spr_player_right[0];
              }
           else 
           if (!faceright)//levo
           {
                if(friction>1)                                                                                 
                {
                spr_player=spr_player_skija[0];
                }else
              spr_player=spr_player_left[0];
           }
        }
	

     }
     else 
     if (ON_GROUND==false)//ako skace 
     {
        if (faceright==true)spr_player=spr_player_right[7];//skacuca slika za desno
        else 
        if (faceright==false) spr_player=spr_player_left[7];//skacuca slika za levo
     }
   }
   else
   spr_player=spr_dead;//ako je igrac mrtav onda ce slika biti slika igraca kako lezi na podu
   apply_surface( (box.x-8)-camera.x,box.y-camera.y,spr_player,screen);
   // konacno lepljenje igraca na ekran
}


void CPlayer::handle_events()
{
   if(living==true)
   {
      if( event.type == SDL_KEYDOWN) 
      {
         if( event.key.keysym.sym==SDLK_SPACE && !lockjump )
         {

			VELMOVING = abs(velx);

			if(VELMOVING<4)
				VELMOVING = 4;
			
            ON_GROUND==false;	
            vely = -VELJUMP;		
		    lockjump = true;
            jumping = true;  
         }
      }
   }                    
}

void CPlayer::collision_detection_map()
{

   friction=1;
         
   if (win==false)
   {
      
        
      if (box.y>4500)
      {
         ON_GROUND=true;
         living=false;
         if(playable_a==true)
         {
            Mix_PlayChannel( -1, a, 0 );
            playable_a=false;
         }
         vely=0;
         ON_GROUND=true;

      }
      else
      playable_a=true;
      
      int dead_count=0;

           if (living==false)  
      {   
          lockjump=true;
          velx*=0.9;
       
         if ( ON_GROUND==true)
         {
            if(allow==true)
            {
              GLOBAL_TIME=1;
              allow=false;
            }
              
              if (GLOBAL_TIME%30==0)
            {
               
               vely=1;
               box.x=100;
               box.y=4200;
               beam=true; 
               spr_dugme_pr=spr_dugme;
               spr_svetlost=spr_crveno;
               lives--;
               living=true;
               r==true;
            }
         }
      }
      else    
      {      
         player.box.h=PLAYERHEIGHT;
         player.box.w=PLAYERWIDTH;
      }

	int tilecoord;

	//prvo X osa
	if(velx > 0)
    {		//desno
		if(collision_ver(box.x+velx+w, box.y, tilecoord))
        {	
			box.x = tilecoord*TILESIZE -w-1;
			VELMOVING=5;
        }
		else
        {		
		   if(velx>20)
	       velx=20;
		box.x += velx;
        }
	
	}		 
	else if(velx < 0)
    {	//levo
		if(collision_ver(box.x+velx, box.y, tilecoord))	
        {	
			box.x = (tilecoord+1)*TILESIZE +1;	
				VELMOVING=5;
        }		//pomera se do ivice tajla
		else
        {
           if(velx<-20)
	           velx=-20;
	           
		   box.x += velx;
        }
	}    
	

	//Y osa
	if(vely < 0)
    {	//kretanje gore
		if(collision_hor_up(box.x, box.y+vely, tilecoord))
        {
			box.y		= (tilecoord+1)*TILESIZE +1;
			vely	= 0;
		}
		else
        {
			box.y += vely;
			vely	+=GRAVITATION;
		}
	}		 
	else{		//na podu
		
		if(collision_hor_down(box.x, box.y+vely+h, tilecoord)==t_solid || collision_hor_down(box.x, box.y+vely+h, tilecoord)==t_ice||
        (collision_hor_down(box.x, box.y+vely+h, tilecoord)==t_toponly &&    
         ((box.y+h) < (tilecoord*TILESIZE))))         
          {	//na podu
          if(collision_hor_down(box.x, box.y+vely+h, tilecoord)==t_ice)
             friction=5;
             else
             friction=1;
             
			 box.y		= tilecoord*TILESIZE -h-1;
			 vely	= 1;				
             ON_GROUND=true;
			 unlockjump();
		}		
        else if(collision_hor_down(box.x, box.y+vely+h, tilecoord)==t_jumpwall)
		{
             Mix_PlayChannel( -1, boink, 0 );
		     vely = -30;		
		     lockjump = true;
         }

        if(ON_GROUND==false) 
        {	
		    friction=1;
			box.y		+= vely;
			vely	+= GRAVITATION;
           
			if(vely >= TILESIZE)		//if the speed is higher than this we might fall through a tile
				vely = TILESIZE;

			lockjump = true;			//don't allow jumping after falling of an edge
		}	
	} 
}       
}

double sign(double x){
	return (x > 0) - (x < 0);
}

void CPlayer::think()
{

     float tempvelx;
     if (win==false && living==true)
     {



         if (abs(vely)>-1)
         {
            ON_GROUND=false;
         }
     
         if(box.x>LEVEL_WIDTH-20)
         {
            VELMOVING=5;
            box.x=LEVEL_WIDTH-20;
         }
     
         if(box.x<10)
         {
        	VELMOVING=5;
            box.x=10;
         }

	     xtime++;
	
         if(lockjump==true )//SIMULACIJA GRAVITACIJE U VAZDUHU
         {
            if(GLOBAL_TIME%200==0)
            {
                 velx*=0.9;
            }
         }
         else
         {
              if(GLOBAL_TIME%friction==0)
				  velx*=0.9;
         }





//////////////////////////////////////////////////////////////////////////////////
// ovde se obradjuju pritisci na dugmad koji kontrolisu igraca
//////////////////////////////////////////////////////////////////////////////////


	    if(keystates[SDLK_RIGHT])///desno
        {

			 if(!faceright && lockjump){
				 switchInAirDir = 1;
			 }

			if(!lockjump)
		   velx += 2.0;		
			else
		   velx += 1.0;		

		   faceright = true;	
           W_RIGHT=true;
	    } 
	    else W_RIGHT=false;
	
	    if(keystates[SDLK_LEFT])//levo
        {  

			 if(faceright && lockjump)
				 switchInAirDir = -1;

			// if(faceright && VELMOVING>5)
			// 	VELMOVING *= 0.5;


			if(!lockjump)
           velx -= 2.0;
			else
           velx -= 1.0;
		   faceright = false;	
           W_LEFT=true;
	    }
	    else W_LEFT=false;
	


	    if(keystates[SDLK_LCTRL] && !lockjump && (W_LEFT==true || W_RIGHT==true))//trcanje
        {                        

               if (VELMOVING<13)        // mora da se ogrannici brzina                
               {            
                   VELMOVING+=1;
               }

			   if (VELJUMP<25 )                       
			   {
				  if(GLOBAL_TIME%3==0)
					 VELJUMP+=1;
			   }
                                          	
		}
		else if(!lockjump)
	   {
			if (VELMOVING > 4)
			{VELMOVING-=1;}
			else 
				VELMOVING = 4;
	   
			if (VELJUMP>15)                       
			{VELJUMP-=1;}
		   
	   }

}
	collision_detection_map();

	int maxLatAirSpeed = 4;

	if(switchInAirDir && lockjump){
		if(switchInAirDir == 1 && velx > maxLatAirSpeed)
			velx = maxLatAirSpeed;
		else if (velx < -maxLatAirSpeed)
			velx = -maxLatAirSpeed;
	}

		 if(abs(velx)>VELMOVING)
			 velx = VELMOVING*sign(velx);
}

void CPlayer::set_camera()
{
   camera.x = ( box.x + PLAYERWIDTH / 2 ) - 1000 / 2;   /// ovde se kamera centrira na igraca
   camera.y = ( box.y + PLAYERHEIGHT / 2 ) - 768 / 2;  ///  tako da igrac bude na sredini erkrana
   
///////////////////////////////////////////////////////////////////////////////////////////////////////////
// pomeranje kamera se mora ograniciti da nebi pobegla iz nivoa
//////////////////////////////////////////////////////////////////////////////////////////////////////
    
   if( camera.x < 0 )// ukoliko ode previse nalevo
   {
      camera.x = 0;    
   }
   
   if( camera.y < 0 )//ukoliko ode previse nagore
   {
      camera.y = 0;    
   }
    
   if( camera.x > 1500 - 1000 )//ukoliko kamera malo ode nadesno napolje ona se vraca na mesto
   {
      camera.x = 1500 - 1000;    
   }
    
   if( camera.y > 4500 - 748 )// ukoliko ode previse nadole vraca se na mesto 
   {
      camera.y =4500- 748;    
   }    
}


int CPlayer::collision_hor_down(int x, int y, int &tilecoordy)
{
	int tilexpixels = x-(x%TILESIZE);	//izracunavanje pixela kod tajla koji proveravamo
	int testend = x + w;	

	tilecoordy = y/TILESIZE;			//Y pozicija tajla koji proveravamo

	int tilecoordx = tilexpixels/TILESIZE;

	while(tilexpixels <= testend)
    {
		return mapy.map(tilecoordx, tilecoordy);

		tilecoordx++;	
		tilexpixels+=TILESIZE;	
	}

	return false;
}



bool CPlayer::collision_hor_up(int x, int y, int &tilecoordy)
{
	int tilexpixels = x-(x%TILESIZE);
	int testend = x + w;

	tilecoordy = y/TILESIZE;

	int tilecoordx = tilexpixels/TILESIZE;

	while(tilexpixels <= testend)
    {
		if(mapy.map(tilecoordx, tilecoordy) != t_nonsolid && mapy.map(tilecoordx, tilecoordy) != t_toponly) //only this changed: when jumping (moving up) we don't want to go through slopes
			return true;	

		tilecoordx++;
		tilexpixels+=TILESIZE;
	}
	return false;
}





bool CPlayer::collision_ver(int x, int y, int &tilecoordx)
{
	int tileypixels = y-(y%TILESIZE);
	int testend = y + h;

	tilecoordx = x/TILESIZE;

	int tilecoordy = tileypixels/TILESIZE;
	
	while(tileypixels <= testend)
    {
		if(mapy.map(tilecoordx, tilecoordy) == t_solid || mapy.map(tilecoordx, tilecoordy) == t_jumpwall|| mapy.map(tilecoordx, tilecoordy) == t_ice)
			return true;

		tilecoordy++;
		tileypixels += TILESIZE;
	}
	return false;
}



#endif
