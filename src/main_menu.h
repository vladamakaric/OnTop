#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "global.h"
#include "button.h"


class MainMenu : public GameState
{
    public:
    
    SDL_Surface *background;
    SDL_Surface *message;
    
    MainMenu();
    ~MainMenu();

    void handle_events();
    void logic();
    void render();
};


MainMenu::MainMenu()
{

    background = load_image( "grafika/menu/main.bmp" );

    next1 = load_image ("grafika/menu/sipl.bmp");
    next2 = load_image ("grafika/menu/sipl2.bmp");

    m=load_image("grafika/menu/multy.bmp");
    
    
    m2=load_image("grafika/menu/multy2.bmp");
    
    ex=load_image("grafika/menu/ex.bmp");
    
    
    ex2=load_image("grafika/menu/ex2.bmp");
    
    cr=load_image("grafika/menu/cr.bmp");
    
    
    cr2=load_image("grafika/menu/cr2.bmp");
    
   le=load_image("grafika/menu/leed.bmp");
    
    
    le2=load_image("grafika/menu/leed2.bmp");

     Button a (380,270,cr,cr2,STATE_CREDITS);
     Button b (380,340,next1,next2,STATE_SINGLE_PLAYER);
     
     Button c (380,410,le,le2,STATE_LEVEL_EDITOR);
     Button d (380,480,m,m2,STATE_MULTI_PLAYER);
     Button r (380,550,ex,ex2,STATE_EXIT);
     
      game =a;
      multyplayer =b;
      exitg=d;
      lvleditor=c;
      back4=r;
   
}

MainMenu::~MainMenu()
{

}

void MainMenu::handle_events()
{
    while( SDL_PollEvent( &event ) )
    {
         game.proces_events();
         multyplayer.proces_events();
         exitg.proces_events();
         lvleditor.proces_events();
         back4.proces_events();
    }
}

void MainMenu::logic()
{

}

void MainMenu::render()
{
    apply_surface( 0, 0, background, screen );

    game.show();
    multyplayer.show();
    exitg.show();
    lvleditor.show();
    back4.show();
}

#endif
