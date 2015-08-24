#ifndef BUTTON_H
#define BUTTON_H

#include "global.h"

class Button
{
  public:
         
    SDL_Rect box;
    SDL_Surface* button;
    SDL_Surface* button_normal;
    SDL_Surface* button_over;
    
    int DEF_STATE;
    
    Button( int x, int y,SDL_Surface *a,SDL_Surface *b,int st );
    Button(){}

    void proces_events();
    void show();
    
}game,multyplayer,exitg,lvleditor,back1,back2,back3,singleplayer,back4,back5;


Button::Button( int x, int y,SDL_Surface *a,SDL_Surface *b, int st )
{
    box.x = x;
    box.y = y;
    box.w = a->w;
    box.h = a->h;
    DEF_STATE=st;
    button_normal=a;
    button_over=b; 
    button=button_normal;
}
    
void Button::proces_events()//svako dugme ima svoju proveru dogadjaja tako se menja slika
{
    int x = 0, y = 0;
   
    if( event.type == SDL_MOUSEMOTION )
    {  
        x = event.motion.x;
        y = event.motion.y;
            
        if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
        {    
            button=button_over; 
        }
    
        else
        {
            button=button_normal; 
        }    
    }

    if( event.type == SDL_MOUSEBUTTONDOWN )
    {
        if( event.button.button == SDL_BUTTON_LEFT )
        {       
            x = event.button.x;
            y = event.button.y;

            if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
            {
                Mix_PlayChannel( -1, button_sound, 0 );///ukoliko je kliknuto dugme tada menjamo fazu
                set_next_state( DEF_STATE );
            }
        }
    }
}
    
void Button::show()
{
    apply_surface( box.x, box.y, button, screen);
}


#endif
