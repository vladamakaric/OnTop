#ifndef CREDITS_H 
#define CREDITS_H

#include "SDL/SDL.h"
#include "global.h"

class Credits : public GameState///kredits ekran
{
    private:
    SDL_Surface *p_8background;

    SDL_Surface *message;
    
    public:
    Credits();

    ~Credits();

    void handle_events();
    void logic();
    void render();
};

Credits::Credits()
{

    p_8background = load_image( "grafika/menu/creditsscreen.bmp" ); 
    Button n (770,700,ex,ex2,STATE_MAIN_MENU);
    back5=n;
  
}

Credits::~Credits()
{
}

void Credits::handle_events()
{
    while( SDL_PollEvent( &event ) )
    {
         back5.proces_events();
    }
}

void Credits::logic()
{
}

void Credits::render()
{
    apply_surface( 0, 0, p_8background, screen );
    back5.show();
}


#endif
