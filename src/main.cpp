int GLOBAL_TIME=0;

#include "level_editor.h"
#include "functions.h"
#include "credits.h"
#include "multi_player.h"
#include "game_state.h"
#include "main_menu.h"
#include "single_player.h"

#include "door.h"
#include "button.h"


int main( int argc, char* args[] )
{ 
    if( init() == false )
    {
        return 1;
    }

    load_files();

    stateID = STATE_MAIN_MENU;

    currentState= new MainMenu;
    
    int fps=0;

    std::ifstream FPS( "fps.txt" );
    FPS >> fps;
    FPS.close();
    
    while( stateID != STATE_EXIT )
    {
        framestart=SDL_GetTicks();

        currentState->handle_events();

        currentState->logic();
        GLOBAL_TIME++;

        change_state();

        currentState->render();

        if( SDL_Flip( screen ) == -1 )
        {
            return 1;    
        }

        while((SDL_GetTicks()-framestart) < fps);
    }

    clean_up();
    
    return 0;    
}