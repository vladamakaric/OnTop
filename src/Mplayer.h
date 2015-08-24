#ifndef MPLAYER_H
#define MPLAYER_H


#include "MPboolet.h"
#include "MPglobal.h"
#include "global.h"


class MPlayer
{
      
	public:
       SDL_Rect box;
		void think(int LEFT,int RIGHT,int VELMORE,int JUMP);	//uzimanje vrednosti koje su unikatne po svakog igraca
        void handle_events(int JUMP,int SHOOT);	
		void draw(int x);
        
        
		MPlayer(int x,int y); // inicijalizacija igraca

		int collision_ver(int x, int y, int &tilecoordx);	//provera sudara po y osi	
		int collision_hor(int x, int y, int &tilecoordy);	//provera sudara po x osi
        

        MPboolet array[2000];
			
		int h, w;	
        
        int brojac;		
        int count;
        
        int shit;
        int prev;
        
        int lives;
        
		int velx, vely;		
		
		float VELMOVING;		
        float VELJUMP;	
        
        bool W_RIGHT;
        bool W_LEFT;
        
        bool living;
        
        bool ON_GROUND;
		
		bool faceright;		

		bool lockjump;		
		
}player1(100,200),player2(500,200);

MPlayer::MPlayer(int x, int y)
{
	box.x=x;			
    box.y=y;

	box.h = h = PLAYERHEIGHT;	
    box.w=	w = PLAYERWIDTH;

	velx	= 0;			
    vely	= 0;
    
    shit=11;
    prev=5;
    
    VELMOVING=15;
    VELJUMP=14;
    
    brojac=3;
    lives=5;
    
    W_RIGHT =false;
    W_LEFT  =false;

	lockjump = false;		
	faceright = true;	
    living=true;	
}



void MPlayer::draw(int x)
{
   if (lives>0)
   {
      if (ON_GROUND==true) //ako je na zemlji onda ce se obradjivati hodanje
      {
         if (abs(velx)>0)
         {	
	        if(faceright)// ako je na podu i okrenut desno  onda ce se menjati trcuce slike za desno
	        {
                if (!(count>5))
                count+=1;
                else
                count=0;
                m_spr_player[x]=m_spr_player_right[x][(int)count];
            }
    
	       if(!faceright) // ako je na podu i okrenut levo onda ce se menjati trcuce slike za levo
	       {
              if (!(count>5))
              count+=1;
              else
              count=0;

              m_spr_player[x]=m_spr_player_left[x][(int)count];
           }
        }
        else //ako ne trci onda ce se prikazati stojece slike
        {
           if (faceright)// stojeca slika za desno
              m_spr_player[x]=m_spr_player_right[x][0];
           else 
           if (!faceright)//levo
              m_spr_player[x]=m_spr_player_left[x][0];
        }
	

     }
     else 
     if (ON_GROUND==false)//ako skace 
     {
                                
       
        if (faceright==true)m_spr_player[x]=m_spr_player_right[x][7];//skacuca slika za desno
        else 
        if (faceright==false) m_spr_player[x]=m_spr_player_left[x][7];//skacuca slika za levo
   
     }

   }
   else
   m_spr_player[x]=m_spr_dead[x];//ako je igrac mrtav onda ce slika biti slika igraca kako lezi na podu
   

         
   apply_surface( box.x-8,box.y,m_spr_player[x],screen);
}


int MPlayer::collision_hor(int x, int y, int &tilecoordy){
	int tilexpixels = x-(x%TILESIZE);	
	int testend = box.x + w;		

	tilecoordy = y/TILESIZE;			

	int tilecoordx = tilexpixels/TILESIZE;	



	while(tilexpixels <= testend){
		map.colmapxy(tilecoordx, tilecoordy);	
			return map.colmapxy(tilecoordx, tilecoordy);	

		tilecoordx++;		
		tilexpixels+=TILESIZE;	
	}

	return false;
}

int MPlayer::collision_ver(int x, int y, int &tilecoordx)
{
	int tileypixels = y-(y%TILESIZE);
	int testend = box.y + h;
	tilecoordx = x/TILESIZE;

	int tilecoordy = tileypixels/TILESIZE;

	while(tileypixels <= testend)
    {
		if ((map.colmapxy(tilecoordx, tilecoordy)==mSOLID || map.colmapxy(tilecoordx, tilecoordy)==mBRICK_WALL) && map.colmapxy(tilecoordx, tilecoordy)!=mTOP_ONLY)
		return true;

		tilecoordy++;
		tileypixels += TILESIZE;
	}

	return false;
}

void MPlayer::think(int LEFT,int RIGHT,int VELMORE,int JUMP)
{
     
     
     if (VELMOVING>23)
     VELMOVING=23;
     
     if (velx>23)
     velx=23;
     
     if (abs(vely)>0)
         {
            ON_GROUND=false;
         }
     if(box.x>1020-40)
     {
        box.x=box.x-velx;
     }
     
          if(box.x<10)
     {
        box.x=box.x-velx;
     }
     
          if(box.y<0)
     {
        vely=5;
     }
          

	xtime++;
	
if(lockjump==true )
{
       if(xtime%200==0)
       {
           velx*=9;
       }
}
else  
velx*=0.9;

sudar=false;

if(lives<1)
{

        int tilecoord;
		if(collision_hor(box.x, box.y+vely+h, tilecoord)==mSOLID || collision_hor(box.x, box.y+vely+h, tilecoord)==mBRICK_WALL ||  (collision_hor(box.x, box.y+vely+h, tilecoord)==mTOP_ONLY  && ((box.y+h) < (tilecoord*TILESIZE)  )))
        {	//na zemlji
			box.y		= tilecoord*TILESIZE -h-1;
			vely	= 1;			
            sudar=true;
            ON_GROUND=true;

		}
		else{	//padanje
		sudar=false;
			box.y += vely;
			vely += GRAVITATION;

			if(vely >= TILESIZE)		//ogranicavanje brzine
				vely = TILESIZE;
			//ako igrac pada sa ivice nesme da skoce
        }	
       	
}


if (lives>0)
{
	if(keystates[RIGHT])
    {
		velx = (int)VELMOVING;	
		faceright = true;	
        W_RIGHT=true;
	
	}
	else W_RIGHT=false;
	
	if(keystates[LEFT])
    {
		velx = (int)-VELMOVING;	
		faceright = false;	
        W_LEFT=true;
	}
	else W_LEFT=false;
	
	
if(keystates[VELMORE] && (W_LEFT==true || W_RIGHT==true))
{
   if (lockjump==false) // naravno igrac jedino moze da trci ako je na podu
   {
      if (VELMOVING<12)        // mora da se ogrannici brzina                
      {
         if(lockjump==false)
            VELMOVING+=0.5;
      }
      
      if (VELJUMP<23 )                       
      {
         if(xtime%3==0)
            VELJUMP+=1;
      }
   }                           	
}
else
{
   if (VELMOVING > 4)
   {VELMOVING-=1;}
       
   if (VELJUMP>10)                       
   {VELJUMP-=1;}
}

   int tilecoord;

	//prvo x osa
   if(velx > 0)
   {		//kretanje u desno
      if(collision_ver(box.x+velx+w, box.y, tilecoord))
      {	
	     box.x = tilecoord*TILESIZE -w-1;
	     if(abs(velx)>6)
	     {
			VELMOVING=5;
         }
      }					//pomeranje do ivice tajla
      else			//ukoliko nema sudara moze slobodno da se krece
        box.x += velx;
	}		 
	else if(velx < 0)
    {	//levo
	   if(collision_ver(box.x+velx, box.y, tilecoord))	
       {	
	      box.x = (tilecoord+1)*TILESIZE +1;
	      if(abs(velx)>6)
	      {
             VELMOVING=5;
          }

        }			
		else
		   box.x += velx;
	}

	if(vely < 0)
    {	
		if(collision_hor(box.x, box.y+vely, tilecoord)==mSOLID && collision_hor(box.x, box.y+vely, tilecoord)!=mTOP_ONLY)
        {
			box.y = (tilecoord+1)*TILESIZE +1;
			vely = 0;
		}else
        {
           sudar=false;
		   box.y += vely;
		   vely	+=GRAVITATION;
		}
    }		 
	else
    {		
		if(collision_hor(box.x, box.y+vely+h, tilecoord)==mSOLID || collision_hor(box.x, box.y+vely+h, tilecoord)==mBRICK_WALL ||  (collision_hor(box.x, box.y+vely+h, tilecoord)==mTOP_ONLY  && ((box.y+h) < (tilecoord*TILESIZE)  )))
        {	//na podu
			box.y		= tilecoord*TILESIZE -h-1;
			vely	= 1;			
            sudar=true;
            ON_GROUND=true;
			if(!keystates[JUMP])
				lockjump = false;
		}
		else
        {
		   sudar=false;
		   box.y += vely;
		   vely += GRAVITATION;
		   
           if(vely >= TILESIZE)		//ogranicavanje brzine
		      vely = TILESIZE;

           lockjump = true;		
		}
	 }	
  }
}

void MPlayer::handle_events(int JUMP,int SHOOT)
{
//provera eventa koji nisu ucestali
if(lives>0)
{                                                
   if(event.type==SDL_KEYDOWN)
   {                     
      if(event.key.keysym.sym==JUMP && !lockjump )
      { 
         vely = (int)-VELJUMP;		
		 lockjump = true;
      }
     
      if(event.key.keysym.sym==SHOOT &&  ((hj-2)>-3) )
      { 
         brojac++;
         
         Mix_PlayChannel( -1, gun, 0 );
         
         if(ON_GROUND==true)
         {
         if (faceright==true)
            array[brojac].boolet_init((box.x+21),(box.y+20),1);
      
         if (faceright==false)
            array[++brojac].boolet_init((box.x-15),(box.y+20),2);
         }
         else
         {
         if (faceright==true)
            array[brojac].boolet_init((box.x+21),(box.y+5),1);
      
         if (faceright==false)
            array[++brojac].boolet_init((box.x-15),(box.y+5),2);
         }
          
          hj=0;
       }
     } 
   }  
}	

#endif
