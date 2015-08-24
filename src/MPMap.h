#ifndef MPMAP_H
#define MPMAP_H

#include "MPglobal.h"


class MPTile///tile klasa
{public:
    int type;	
	SDL_Surface	*spr;
    SDL_Rect box;

	MPTile(){
        box.w=50;
        box.h=50;
		type = -1;
	    spr=NULL;
	};
};

class MPMap{
	public:
		void loadMap(const char *file);		

		void draw();

		int colmapxy(int x, int y)
        {		//podela tajlova na podgrupe
			if (tiles[x][y].type > 7 && tiles[x][y].type < 12)
			return mTOP_ONLY;
			
            if (tiles[x][y].type ==0 || tiles[x][y].type==7)
			return mNOTHING;
			
			if ((tiles[x][y].type >0 && tiles[x][y].type < 7) || tiles[x][y].type==12)
			return mSOLID;
			
			if (tiles[x][y].type==13)
			return mBRICK_WALL;
		}

	MPTile tiles[20][17];//mapa u multylayer modu
}map;

void MPMap::loadMap(const char *file)
{
	std::ifstream map( file );
	int t, i, j;

	for(j = 0; j < 17; j++)
    {
		for(i = 0; i < 20; i++)
        {
			map >> tiles[i][j].type;
			tiles[i][j].spr = m_spr_t[tiles[i][j].type-1];
		}
	}
	map.close();
}



void MPMap::draw(){
	int i, j;
SDL_Rect box;
	for(i = 0; i < 20; i++){
		for(j = 0; j < 17; j++){
			if(tiles[i][j].spr != NULL)
            {
			    box.x=i*TILESIZE;   
			    box.y=j*TILESIZE;

				apply_surface(box.x, box.y,tiles[i][j].spr,screen);
            }
		}
	}
}

#endif
