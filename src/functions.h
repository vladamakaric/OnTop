#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "credits.h"
#include "single_player.h"
#include "multi_player.h"
#include "global.h"
#include "level_editor.h"
#include "main_menu.h"


SDL_Surface *load_image( std::string filename ) ////ucitavanje slike
{  
    SDL_Surface* loadedImage = NULL;   //sirova slika
    SDL_Surface* optimizedImage = NULL;      //optimizovana slika
    loadedImage = IMG_Load( filename.c_str() );
        
    if( loadedImage != NULL )
    {      
        optimizedImage = SDL_DisplayFormat( loadedImage );     
        SDL_FreeSurface( loadedImage );
        
        if( optimizedImage != NULL )
        {
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format,255, 0, 255 ) );// transparecnija
        }
    }
    return optimizedImage;
}



bool check_collision( SDL_Rect A, SDL_Rect B )//////standardna AABB provera 
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;
        
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;
            
    if( bottomA <= topB )
    {
        return false;
    }
    
    if( topA >= bottomB )
    {
        return false;
    }
    
    if( rightA <= leftB )
    {
        return false;
    }
    
    if( leftA >= rightB )
    {
        return false;
    }

    return true;
}

bool init()
{
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;    
    }


    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_FULLSCREEN );//ovde se startuje SDL program
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ); 

    if( screen == NULL )
    {
        return false;    
    }

    SDL_WM_SetCaption( "ON TOP", NULL );

    return true;
}

void clean_up()
{

    delete currentState;

    SDL_FreeSurface( dot );
    SDL_Quit();
}

void set_next_state( int newState )
{ 
    if( nextState != STATE_EXIT )
    {
        nextState = newState;
    }
}

void change_state()
{
    if( nextState != STATE_NULL )
    {

        if( nextState != STATE_EXIT )
        {
            delete currentState;
        }
        
        //promena stanja
        switch( nextState )
        {
            case STATE_CREDITS:
                currentState = new Credits();
                break;
                
                case STATE_MAIN_MENU:
                currentState = new MainMenu();
                break;
        
            case STATE_LEVEL_EDITOR:
                currentState = new LevelEditor();
                break;
                
            case STATE_MULTI_PLAYER:
                currentState = new MultiPlayer();
                break;
                
            case STATE_SINGLE_PLAYER:
                currentState = new SinglePlayer();
                break;
        }
        

        stateID = nextState;

        nextState = STATE_NULL;    
    }
}


#endif
