#ifndef MPGLOBAL_H
#define MPGLOBAL_H

typedef const int freez;

SDL_Surface* m_spr_left_bar;
SDL_Surface* m_spr_right_bar;

SDL_Surface* m_spr_loser_right;
SDL_Surface* m_spr_winner_right;
SDL_Surface* m_spr_loser_left;
SDL_Surface* m_spr_winner_left;

SDL_Surface* m_spr_blue[5];
SDL_Surface* m_spr_red[5];

SDL_Surface* m_spr_boolet_right;	
SDL_Surface* m_spr_boolet_left;
SDL_Surface* m_spr_shit;
SDL_Surface* m_spr_enemy1;
SDL_Surface* m_spr_enemy2;
SDL_Surface* m_spr_enemy3;
SDL_Surface* m_spr_enemy1_red;
SDL_Surface* m_spr_enemy2_red;
SDL_Surface* m_spr_enemy3_red;
SDL_Surface* m_spr_enemy_shoot=NULL;
SDL_Surface* m_spr_t[13];
SDL_Surface* m_spr_player[2];
SDL_Surface* m_spr_dead[2];	
SDL_Surface* m_spr_background;

SDL_Surface* m_spr_boolet;
SDL_Surface* m_spr_player_left[2][8];	
SDL_Surface* m_spr_player_right[2][8];
SDL_Surface* m_spr_lift;

int mNOTHING=0;
int mSOLID=1;
int mTOP_ONLY=2;
int mBRICK_WALL=3;

int mveljump=0;

bool sudar   =true;
bool over   =false;

SDL_Rect p1,p2;

SDL_Rect bounding[6] = {{150,100,200,50},{600,100,200,50},
{100,450,100,50},
{750,450,100,50},{350,450,250,50},{400,600,150,100}};
#endif
