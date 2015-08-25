#ifndef SMAP_H
#define SMAP_H


#include "global.h"

class STile
{
      public:
   int type;	
   SDL_Surface	*spr;
   SDL_Rect box;

   STile()
   {
      type = -1;
      spr=NULL;
   };
};

class SMap
{
	public:
		void loadMap(const char *file);		
		void draw();
        
		int map(int x, int y)
        {
            if (tiles[x][y].type == 0 || tiles[x][y].type == 7)			//return the tiletype at the specific position (map coordinates)
			return t_nonsolid;
			
            if ((tiles[x][y].type > 0 && tiles[x][y].type< 7)||	tiles[x][y].type==12)		//return the tiletype at the specific position (map coordinates)
			return t_solid;
			
            if (tiles[x][y].type==14)
            return t_jumpwall;
            
             if (tiles[x][y].type==15)
            return t_ice;
			
             if (tiles[x][y].type > 7 && tiles[x][y].type < 12)			//return the tiletype at the specific position (map coordinates)
			return t_toponly;
		}

	    STile tiles[MAPWIDTH][MAPHEIGHT];
}mapy;

//////////////////////////////////////////////////
// razvrstavanje tajlova po vrsti
///////////////////////////////////////////////////

//ucitavanje table iz fajla
void SMap::loadMap(const char *file)
{
	std::ifstream map( file );//fajl
	int t, i, j;

	for(j = 0; j < MAPHEIGHT; j++)
    {
		for(i = 0; i < MAPWIDTH; i++)
        {
			map >> tiles[i][j].type;//ucitavanje vrednosti
			tiles[i][j].spr = spr_t[tiles[i][j].type-1];
		}
	}
	map.close();
}

//iscrtavanje ble
void SMap::draw()
{
	int i, j;
    SDL_Rect box;
	box.w = TILESIZE;
	box.h = TILESIZE;

	for(i = 0; i < MAPWIDTH; i++)
    {
		for(j = 0; j < MAPHEIGHT; j++)
        {
			if(tiles[i][j].spr != NULL)
            {
			    box.x=i*TILESIZE;   
			    box.y=j*TILESIZE;

			    if (check_collision(box,camera))
				   apply_surface(box.x-camera.x, box.y-camera.y,tiles[i][j].spr,screen);
            }
		}
	}
}

#endif
