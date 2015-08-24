#ifndef LEVEL_EDITOR_H
#define LEVEL_EDITOR_H

#include "Sglobal.h"
#include "SDL/SDL.h"
#include "button.h"
#include <fstream>
////////////////GLOBAL ///////////////////////////////



const int TILE_WIDTH = 50;
const int TILE_HEIGHT = 50;
const int TOTAL_TILES = (1500/50)*(3000/50);
const int TILE_SPRITES = 20;

SDL_Surface *tileSheet = NULL;
SDL_Surface *triangle = NULL;

SDL_Rect clips[ TILE_SPRITES ];

SDL_Rect camera2 = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
////////////////////////////////////////

///////////////TILE CLASS///////////////////////////////
class Tile
{
    private:
    SDL_Rect box;
    int type;
    
    public:
    Tile( int x, int y, int tileType );
    void show();
    int get_type();
    SDL_Rect &get_box();
};



//////////////////////////////////////////////////

/////////////FUNCTIONS///////////////////////////
bool LEload_files()
{
    tileSheet = load_image( "ftile.png" );
    triangle = load_image ("kul.png");

    if( tileSheet == NULL )
    {
        return false;    
    }

    return true;
}
 
void clean_up( Tile *tiles[] )
{
    SDL_FreeSurface( tileSheet );

    for( int t = 0; t < TOTAL_TILES; t++ )
    {
        delete tiles[ t ];    
    }

}
///////////////////////////////////////////////////
/////////////////CLIP/////////////////////////////
void set_camera()
{
    int x = 0, y = 0;

    SDL_GetMouseState( &x, &y );

    if( x < TILE_WIDTH )
    {
        camera2.x -= 20;
    }

    if( x > SCREEN_WIDTH - TILE_WIDTH )
    {
        camera2.x += 20;
    }

    if( y < TILE_WIDTH )
    {
        camera2.y -= 20;
    }

    if( y > SCREEN_HEIGHT - TILE_WIDTH )
    {
        camera2.y += 20;
    }

    if( camera2.x < 0 )
    {
        camera2.x = 0;    
    }
    if( camera2.y < 0 )
    {
        camera2.y = 0;    
    }
    if( camera2.x > LEVEL_WIDTH - camera2.w )
    {
        camera2.x = LEVEL_WIDTH - camera2.w;    
    }
    if( camera2.y > 3000 - camera2.h )
    {
        camera2.y = 3000 - camera2.h;    
    } 
}

void put_tile( Tile *tiles[], int tileType )
{

    int x = 0, y = 0;

    SDL_GetMouseState( &x, &y );//koordinate misa
    

    x += camera2.x;
    y += camera2.y;
    
    //kroz sve tajlove
    for( int t = 0; t < TOTAL_TILES; t++ )
    {
        SDL_Rect box = tiles[ t ]->get_box();
        
        //ukoliko je mish u tajlu
        if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
        {
            delete tiles[ t ];
            tiles[ t ] = new Tile( box.x, box.y, tileType );
        }
    }
}

void clip_tiles()
{
   clips[ 0 ].x = 50;
   clips[ 0 ].y = 0;
   clips[ 0 ].w = TILE_WIDTH;
   clips[ 0 ].h = TILE_HEIGHT;
    
   clips[ 1 ].x = 100;
   clips[ 1 ].y = 0;
   clips[ 1 ].w = TILE_WIDTH;
   clips[ 1 ].h = TILE_HEIGHT;
   
   clips[ 2 ].x = 150;
   clips[ 2 ].y = 0;
   clips[ 2 ].w = TILE_WIDTH;
   clips[ 2 ].h = TILE_HEIGHT;
   
   clips[ 3 ].x = 200;
   clips[ 3 ].y = 0;
   clips[ 3 ].w = TILE_WIDTH;
   clips[ 3 ].h = TILE_HEIGHT;
   
   clips[ 4 ].x = 250;
   clips[ 4 ].y = 0;
   clips[ 4 ].w = TILE_WIDTH;
   clips[ 4 ].h = TILE_HEIGHT;
    
   clips[ 5 ].x = 300;
   clips[ 5 ].y = 0;
   clips[ 5 ].w = TILE_WIDTH;
   clips[ 5 ].h = TILE_HEIGHT;
   
   clips[ 6 ].x = 350;
   clips[ 6 ].y = 0;
   clips[ 6 ].w = TILE_WIDTH;
   clips[ 6 ].h = TILE_HEIGHT;
   
   clips[ 7 ].x = 400;
   clips[ 7 ].y = 0;
   clips[ 7 ].w = TILE_WIDTH;
   clips[ 7 ].h = TILE_HEIGHT;
   
   clips[ 8 ].x = 450;
   clips[ 8 ].y = 0;
   clips[ 8 ].w = TILE_WIDTH;
   clips[ 8 ].h = TILE_HEIGHT;
    
   clips[ 9 ].x = 500;
   clips[ 9 ].y = 0;
   clips[ 9 ].w = TILE_WIDTH;
   clips[ 9 ].h = TILE_HEIGHT;
   
   clips[ 10 ].x = 550;
   clips[ 10 ].y = 0;
   clips[ 10 ].w = TILE_WIDTH;
   clips[ 10 ].h = TILE_HEIGHT;
   
   clips[ 11 ].x = 600;
   clips[ 11 ].y = 0;
   clips[ 11 ].w = TILE_WIDTH;
   clips[ 11 ].h = TILE_HEIGHT;
   
   clips[ 12 ].x = 650;
   clips[ 12 ].y = 0;
   clips[ 12 ].w = TILE_WIDTH;
   clips[ 12 ].h = TILE_HEIGHT;
    
   clips[ 13 ].x = 700;
   clips[ 13 ].y = 0;
   clips[ 13 ].w = TILE_WIDTH;
   clips[ 13 ].h = TILE_HEIGHT;
   
   clips[ 14 ].x = 750;
   clips[ 14 ].y = 0;
   clips[ 14 ].w = TILE_WIDTH;
   clips[ 14 ].h = TILE_HEIGHT;
   
   clips[ 15 ].x = 800;
   clips[ 15 ].y = 0;
   clips[ 15 ].w = TILE_WIDTH;
   clips[ 15 ].h = TILE_HEIGHT;
   
   clips[ 16 ].x = 850;
   clips[ 16 ].y = 0;
   clips[ 16 ].w = TILE_WIDTH;
   clips[ 16 ].h = TILE_HEIGHT;
    
   clips[ 17 ].x = 900;
   clips[ 17 ].y = 0;
   clips[ 17 ].w = TILE_WIDTH;
   clips[ 17 ].h = TILE_HEIGHT;
   
   clips[ 18 ].x = 950;
   clips[ 18 ].y = 0;
   clips[ 18 ].w = TILE_WIDTH;
   clips[ 18 ].h = TILE_HEIGHT;
   
   clips[ 19 ].x = 1000;
   clips[ 19 ].y = 0;
   clips[ 19 ].w = TILE_WIDTH;
   clips[ 19 ].h = TILE_HEIGHT;
}

bool set_tiles( Tile *tiles[] )
{
    
    int x = 0, y = 0;
    
    //ovori mapu
    std::ifstream map( "fency.map" );

    if( map == NULL )
    {
 
        for( int t = 0; t < TOTAL_TILES; t++ )
        {
            
            tiles[ t ] = new Tile( x, y, t % ( 3 + 1 ) );
            
            //Move to next tile spot
            x += TILE_WIDTH;
        
            //ukoliko je mish otiso predaleko
            if( x >= LEVEL_WIDTH )
            {

                x = 0;
   
                y += TILE_HEIGHT;    
            }
        }
    }
    else
    {
        for( int t = 0; t < TOTAL_TILES; t++ )
        {
            int tileType = -1;

            map >> tileType;//procitaj vrstu tajla iz mape
        
            //ukoliko mapa nemoze da se ucita
            if( map.fail() == true )
            {
                map.close();
                return false;
            }
        
            //ukoliko je broj dobar
            if( ( tileType >= 0 ) && ( tileType < TILE_SPRITES ) )
            {
                tiles[ t ] = new Tile( x, y, tileType );    
            }
            //ukoliko nepostoji takav tip tajla gasimo program
            else 
            {
                map.close();
                return false;
            }

            x += TILE_WIDTH;

            if( x >= LEVEL_WIDTH )
            {
                x = 0;
                y += TILE_HEIGHT;    
            }
        }

        map.close();
    }
    
    return true;
}

void save_tiles( Tile *tiles[] )//kada zavrsimo editovanje levela nase izmene se sacuvaju
{
    std::ofstream map( "fency.map" );

    for( int t = 0; t < TOTAL_TILES; t++ )
    {
        map << tiles[ t ]->get_type() << " ";
    }

    map.close();
}

Tile::Tile( int x, int y, int tileType )
{
    box.x = x;
    box.y = y;

    box.w = TILE_WIDTH;
    box.h = TILE_HEIGHT;

    type = tileType;
}

void Tile::show()
{
    //ukoliko je tajl na ekranu i vidi se
    if( check_collision( camera2, box ) == true )
    {
        apply_surface( box.x - camera2.x, box.y - camera2.y, tileSheet, screen, &clips[ type ] );    
    }
}    

int Tile::get_type()
{
    return type;
}

SDL_Rect &Tile::get_box()
{
    return box;
}

///////////////////////////////////////////////////////////////////////
int currentType = 0;

Tile *tiles[ TOTAL_TILES ];



class LevelEditor : public GameState
{
    private:
    SDL_Surface *background;

    public:

    LevelEditor();

    ~LevelEditor();
    

    void handle_events();
    void logic();
    void render();
};

LevelEditor::LevelEditor()
{
   b_background=load_image("grafika/plavo.bmp");
   Button a(770,700,ex,ex2,STATE_MAIN_MENU);
   back1=a;
   
   LEload_files() ;

   clip_tiles();

   set_tiles( tiles ) ;
}

LevelEditor::~LevelEditor()
{
    SDL_FreeSurface( background );
    save_tiles( tiles ) ;
}

void LevelEditor::handle_events()
{
   while( SDL_PollEvent( &event ) )
        {
            back1.proces_events();

            if( event.type == SDL_MOUSEBUTTONDOWN )
            {

                if( event.button.button == SDL_BUTTON_LEFT )
                {
                    put_tile( tiles, currentType );
                }
                else
                if( event.button.button == SDL_BUTTON_RIGHT )
                {
                    put_tile( tiles, 0 );
                }
                ////////////////////////////////////////////////////
                //OVDE SE OBRADJIVE VRTENJE TOCKA NA MISU I TAKO SE TAJLOVI MENJAJU
                ///////////////////////////////////////////////////
                else if( event.button.button == SDL_BUTTON_WHEELUP )
                {
                    currentType--;
                    
                    if( currentType < 0 )
                    {
                        currentType = 19;
                    }

                }
                else if( event.button.button == SDL_BUTTON_WHEELDOWN )
                {
                    currentType++;
                    
                    if( currentType > 19 )
                    {
                        currentType = 0;
                    }              
                }
            }
        }
}

void LevelEditor::logic()
{

}

void LevelEditor::render()
{
        set_camera();
        apply_surface( 0, 0, b_background, screen);

        for( int t = 0; t < TOTAL_TILES; t++ )
        {
            tiles[ t ]->show();
        }
        apply_surface(934, 20, tileSheet, screen, &clips[ currentType ] );///TRENUTNI TAJL
        apply_surface(850, 0, triangle, screen);
        back1.show();
        
}

#endif
