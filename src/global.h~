#ifndef GLOBAL_H
#define GLOBAL_H


#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include "game_state.h"



enum GameStates
{
    STATE_NULL,
    STATE_MAIN_MENU,
    STATE_CREDITS,
    STATE_LEVEL_EDITOR,
    STATE_MULTI_PLAYER,
    STATE_SINGLE_PLAYER,
    STATE_EXIT,
};

unsigned int framestart;
typedef const int freez;

freez SCREEN_WIDTH=1000;
freez SCREEN_HEIGHT=748;
freez SCREEN_BPP=32;
freez WAITTIME=50;		
freez GRAVITATION=1;
freez MAPWIDTH=30;		
freez MAPHEIGHT=90;		
freez TILESIZE=50;
freez PLAYERHEIGHT=55;		
freez PLAYERWIDTH=13;


SDL_Surface *load_image( std::string filename );
int hj=0;

bool check_collision( SDL_Rect A, SDL_Rect B );

bool init();

bool load_files();

void clean_up();

void set_next_state( int newState );

void change_state();

SDL_Surface *dot = NULL;
SDL_Surface *screen = NULL;

SDL_Surface *next1 = NULL;
SDL_Surface *next2 = NULL;
SDL_Surface *m=NULL;
SDL_Surface *m2=NULL;
SDL_Surface *ex=NULL;
SDL_Surface *ex2=NULL;
SDL_Surface *cr=NULL;
SDL_Surface *cr2=NULL;
SDL_Surface *le=NULL;
SDL_Surface *le2=NULL;
  
  
SDL_Surface *backg=NULL;
SDL_Surface *b_background=NULL;

SDL_Event event;
int LEVEL_WIDTH=MAPWIDTH*TILESIZE;
int LEVEL_HEIGHT=MAPHEIGHT*TILESIZE;

SDL_Rect camera = { 0, 0, LEVEL_WIDTH, LEVEL_HEIGHT };

Uint8*       keystates;

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip=NULL )
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    SDL_BlitSurface( source, clip, destination, &offset );
}

int stateID = STATE_NULL;
int nextState = STATE_NULL;



GameState *currentState = NULL;
#endif
