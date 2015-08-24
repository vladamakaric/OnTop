#ifndef MULTI_PLAYER_H
#define MULTI_PLAYER_H


#include "MPglobal.h"
#include "MPMap.h"
#include "Mplayer.h"
#include "MPfunctions.h"
#include "moving_object.h"

class MultiPlayer : public GameState
{
    private:

    SDL_Surface *background;
 

    
    public:

    MultiPlayer();

    ~MultiPlayer();

    void handle_events();
    void logic();
    void render();
};

MultiPlayer::MultiPlayer()
{
                  
   hj=0;      
   for(int s=0; s<2000; s++)
   {
      player1.array[s].active=false;
      player2.array[s].active=false;
   }

  
   Button u (770,700,ex,ex2,STATE_MAIN_MENU);
  
   back3=u;
   m_spr_lift=load_image("grafika/lift/b200x20.bmp");
   MPload_files();
   map.loadMap("mape/map01.map");
   moving_object a(true,200,300,220,365,3,m_spr_lift);
   moving_object b(true,550,220,220,365,3,m_spr_lift);

   lift1=a;
   lift2=b;
   keystates = SDL_GetKeyState(0);
   player1.lives=5;
   player2.lives=5;

   player1.box.x=20; player1.box.y=200;
   player2.box.x=940; player2.box.y=200;
}

MultiPlayer::~MultiPlayer()
{
    SDL_FreeSurface( m_spr_background );
}
    
void MultiPlayer::handle_events()
{
    while( SDL_PollEvent( &event ) )
    {

        if(over==false)
        {
           player1.handle_events(SDLK_UP,SDLK_SPACE);
           player2.handle_events(SDLK_w,SDLK_LALT);	
        }    
              
        back3.proces_events();
        
        if( event.type == SDL_QUIT )
        {
            set_next_state( STATE_EXIT );
        }
    }
}


//ovde se obradjuje logika
void MultiPlayer::logic()
{
   apply_surface(0,0,m_spr_background,screen);
   player1.think(SDLK_LEFT,SDLK_RIGHT,SDLK_m,SDLK_UP);
   player2.think(SDLK_a,SDLK_d,SDLK_LCTRL,SDLK_w);
   lift1.think();
   lift2.think();
   check_cool_collision(player1.box,lift1.box,player1,lift1,SDLK_UP);
   check_cool_collision(player2.box,lift1.box,player2,lift1,SDLK_w);
     
   check_cool_collision(player1.box,lift2.box,player1,lift2,SDLK_UP);
   check_cool_collision(player2.box,lift2.box,player2,lift2,SDLK_w);
   
   for ( int t=0; t<2000; t++ )
       { 
          for ( int s=0; s<2000; s++ )
          {
              if(player1.array[t].active==true && player2.array[s].active==true)
              {
                 if(check_collision(player1.array[t].box,player2.array[s].box))
                 {
                     player1.array[t].active=false;
                     player2.array[s].active=false;
                 }
              }
          }
       }
       
          ///////////////////////////////////////////////////////////////////////////
          // obradjivanje podataka vezano za metkove
          //////////////////////////////////////////////////////////////////////////
        for(int s=0; s<2000; s++)
	    {
           if (player2.array[s].active==true)
           {
                                             
                                             
              player2.array[s].draw();
              player2.array[s].boolet_fire();
              for(int x=0; x<6; x++)
              {
                 if(check_collision(bounding[x],player2.array[s].box))
                 player2.array[s].active=false;
              }
              
                             if(check_collision(lift1.box,player2.array[s].box))
                 player2.array[s].active=false;
                                if(check_collision(lift2.box,player2.array[s].box))
                 player2.array[s].active=false;
              
              
              
              if(check_collision(player1.box,player2.array[s].box))
              {
                  player1.lives--;
                  player2.array[s].active=false;
              }
              
              
           }
           
           
           if (player1.array[s].active==true)
           {
              player1.array[s].draw();
              player1.array[s].boolet_fire();
              
              

              for(int x=0; x<6; x++)
              {
                 if(check_collision(bounding[x],player1.array[s].box))
                 player1.array[s].active=false;
              }
              
               if(check_collision(lift1.box,player1.array[s].box))
                 player1.array[s].active=false;
                                if(check_collision(lift2.box,player1.array[s].box))
                 player1.array[s].active=false;
                 
              if(check_collision(player2.box,player1.array[s].box))
              {
                  player2.lives--;
                  player1.array[s].active=false;
                 }
              

           }


        }
        
}

void MultiPlayer::render()
{
     ///////////////////////////////////////
     /// iscrtavanje igraca
     ////////////////////////////////
        map.draw();
        player1.draw(0);
        player2.draw(1);
        lift1.draw(false);
        lift2.draw(false);
        calculate_lives(player1,player2);
        back3.show();

}

#endif
