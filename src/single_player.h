#ifndef SINGLE_PLAYER_H
#define SINGLE_PLAYER_H

#include "SDL/SDL.h"

#include "SDL/SDL_mixer.h"

#include "Sglobal.h"
#include "Sfunctions.h"

#include "global.h"
#include "Senemys.h"
class SinglePlayer : public GameState
{
    private:
    SDL_Surface *shit_background;
    public:

    SinglePlayer();
    ~SinglePlayer();

    void handle_events();
    void logic();
    void render();
};


/////////////////////////////////////////////
SinglePlayer::SinglePlayer()
{
                    
    camera.x=0;
    camera.y=0;            
    living=true;
    lives=3;
    win=false;
    player.box.x=100;
    player.box.y=4200;
    beam=true; 
    spr_dugme_pr=spr_dugme;
    spr_svetlost=spr_crveno;
    
    Button a(770,700,ex,ex2,STATE_MAIN_MENU);

    back2=a;

   load_files();
   load_roll();
   /////////////////////////////////////////////////////////////////////
   //SVI NEPRIJATELJI I SVE PREPREKE U TABLI SE INICIJALIZUJU OVDE
   ///////////////////////////////////////////////////////////////////

  
    Simple_enemy p(350-camera.x,(38*50)-camera.y,350,550,2,2);
    simp = p;
    Simple_enemy pp(13*50-camera.x,46*50+1500-camera.y,13*50,16*50,2,2);
    simp2 =pp; 
    Simple_enemy ppp(350-camera.x,57*50+1500-camera.y,350,14*50,3,4);
    simp3=ppp;
    
    
   Simple_enemy pppp(7*50-camera.x,21*50-camera.y,7*50,11*50,2,2);
   simp4=pppp;
   rolling_enemy c(200-camera.x,63*50-camera.y,0,15*50);
   si_en1=c;

   


    shooting_enemy cc(15*50-camera.x,79*50-camera.y,15*50,25*50-50,4);
    sh_en=cc;
    shooting_enemy d(13*50-camera.x,66*50-camera.y,9*50,23*50,8);
    sh_en1=d;
    shooting_enemy dd(19*50-camera.x,14*50-camera.y,18*50,29*50,7);
    sh_en2=dd;
    
    shooting_enemy e(0*50-camera.x,14*50-camera.y,0*50,6*50,5);
    sh_en3=e;
    
    shooting_enemy ee(4*50-camera.x,32*50-camera.y,4*50,12*50,2);
    sh_en4=ee;
    
    shooting_enemy f(12*50-camera.x,57*50-camera.y,12*50,29*50,5);
    sh_en5=f;
  

    red_object ff(7*50,16*50,30,40,spr_emiter1);
    emiter1=ff;
   
    red_object g(17*50,16*50,30,40,spr_emiter2);
    emiter2=g;
   
    moving_object gg(true,0,2600,2300,3080,3,spr_stefan);
    mobj=gg;
   
   
    moving_object h(false,130,2780,130,600,4,spr_stefan);
    mobj3=h;
    moving_object hh(false,400,2375,400,700,3,spr_lift_long_upright);
    mobj4=hh;

    moving_object j(false,400,2500,400,700,3,spr_lift_long);
    mobj5=j;
    
    moving_object jj(false,150,2375,150,450,3,spr_lift_medium);
    mobj6=jj;
    
    moving_object k(false,765,2375,765,1065,3,spr_lift_long_upright);
    mobj7=k;
    moving_object kk(false,765,2375,765,1065,3,spr_lift_medium);
    mobj8=kk;
    moving_object l(true,1000,2180,2180,1450,3,spr_lift_fat);
    mobj9=l;
    moving_object ll(true,700,1820,1820,1330,3,spr_sekac);
    mobj10=ll;
    moving_object q(true,100,1450,1450,1320,3,spr_lift_fat);
    mobj11=q;
    
    moving_object qq(false,100,400,100,1100,3,spr_stefan);
    mobj12=qq;
    
    moving_object w(false,120,100,390,1100,5,spr_stefan);
    mobj13=w;
   
    moving_object ww(false,30,2600+1350,30,500,2,spr_stefan);
    mobj14=ww;
    
    moving_object ej(false,00,2600+1200,00,500,5,spr_stefan);
    mobj15=ej;
   
    pushing_enemy r(mobj9,mobj9.box.x+300, mobj9.box.y,3,7);
    pue=r;
    pushing_enemy rr(mobj6,mobj6.box.x+100, mobj6.box.y,2,7);
    pue2=rr;
    pushing_enemy t(mobj8,mobj8.box.x+100, mobj8.box.y,2,7);
    pue3=t;
   
    Smart_enemy y(2*50-camera.x,72*50-camera.y,2*50,11*50,1,6);
    sm_en=y;
    Smart_enemy yy(13*50-camera.x,72*50-camera.y,13*50,20*50,1,6);
    sm_en1=yy;
    Smart_enemy u(13*50-camera.x,23*50-camera.y,13*50,28*50,2,4);
    sm_en2=u;
    
    Smart_enemy uu(25*50-camera.x,23*50-camera.y,13*50,28*50,2,4);
    sm_en3=uu;
    
    Smart_enemy i(0-camera.x,(38*50)-camera.y,0,5*50,1,6);
    sm_en4=i;
    Smart_enemy ii(3*50-camera.x,(58*50)-camera.y,3*50,8*50,1,6);
    sm_en5=ii;
    
    
    Smart_enemy2 o(mobj11,mobj11.box.x+150-camera.x,mobj11.box.y-camera.y,1,6,1);
    sm_en6=o;
    
    Smart_enemy2 oo(mobj5,mobj5.box.x+300-camera.x,mobj5.box.y-camera.y,2,6,2);
    sm_en7=oo;
    
    keystates = SDL_GetKeyState(0);
    shit_background=load_image("grafika/bg.bmp");
    mapy.loadMap("mape/map02.map");

}

SinglePlayer::~SinglePlayer()
{

}
    
void SinglePlayer::handle_events()
{
    while( SDL_PollEvent( &event ) )
    {
        player.handle_events();
        back2.proces_events();
    }
}

void SinglePlayer::logic()
{
    player.set_camera();
       
            
      player.x=player.box.x+(player.box.w/2);
      player.y=player.box.y+(player.box.h/2);
      player.think();
      
      simp.think();
      simp2.think();
      simp3.think();
      simp4.think();
   
      sm_en.think();
      sm_en1.think();
      sm_en2.think();
      sm_en3.think();
      sm_en4.think();
      sm_en5.think();
      sm_en6.think(mobj11.box.y-50,mobj11);
      sm_en7.think(mobj5.box.y-100,mobj5);
      
      si_en1.think();
      
      sh_en.think();
      sh_en1.think();
      sh_en2.think();
	  sh_en3.think();
	  sh_en4.think();
	  sh_en5.think();

      mobj.think();
      mobj3.think();
      mobj4.think();
      mobj5.think();
      mobj6.think();
      mobj7.think();
      mobj8.think();
      mobj9.think();
      mobj10.think();
      mobj11.think();
      mobj12.think();
      mobj13.think();
      mobj14.think();
      mobj15.think();
      
      pue.think(mobj9);
      pue2.think(mobj6);
      pue3.think(mobj8);
	  sm_en1.think_again();
	  sm_en2.think_again();
	  sm_en3.think_again();
	  sm_en4.think_again();
	  sm_en5.think_again();
	  sm_en6.think_again(mobj11.box.y-50,mobj11);
	  sm_en7.think_again(mobj5.box.y-100,mobj5);
	  
	  
	  
  	  sh_en.think_again();
      sh_en1.think_again();
  	  sh_en2.think_again();
      sh_en3.think_again();
      sh_en4.think_again();
      sh_en5.think_again();
      sm_en.think_again();
      
      pue.think_again(mobj9);
      pue2.think_again(mobj6);
      pue3.think_again(mobj8);
   ///SVA PROVERA SUDARA   
  if ((check_collision(sm_en.box, player.box)) || (check_collision(sh_en.box, player.box)) ||
      (check_collision(sm_en1.box, player.box)) || (check_collision(si_en1.box, player.box)) || (check_collision(sh_en3.box, player.box)) || 
      (check_collision(sh_en5.box, player.box)) || (check_collision(sh_en2.box, player.box)) || (check_collision(sm_en2.box, player.box)) || 
      (check_collision(sm_en3.box, player.box)) || (check_collision(emiter1.box, player.box)) || (check_collision(sm_en7.box, player.box)) || 
      (check_collision(simp.box, player.box)) || (check_collision(sm_en4.box, player.box)) || (check_collision(emiter2.box, player.box))||
      (check_collision(thorn, player.box))|| (check_collision(simp4.box, player.box)) || (check_collision(simp3.box, player.box))  || 
      (check_collision(simp2.box, player.box)) || (check_collision(sm_en6.box, player.box)) || (check_collision(sm_en5.box, player.box)) || 
      (check_collision(sh_en1.box, player.box))) { living=false; }
     
     
     
     //SLOZENA PROVERA SUDARA
      check_cool_collision(player.box,mobj.box,player,mobj);
  
      check_cool_collision(player.box,mobj3.box,player,mobj3);
      check_cool_collision(player.box,mobj4.box,player,mobj4);
      check_cool_collision(player.box,mobj5.box,player,mobj5);
      check_cool_collision(player.box,mobj6.box,player,mobj6);  
      check_cool_collision(player.box,mobj7.box,player,mobj7);
      check_cool_collision(player.box,mobj8.box,player,mobj8);
      check_cool_collision(player.box,mobj9.box,player,mobj9);
      if (living==true) check_cool_cutter_collision(player.box,mobj10.box,player,mobj10);
      check_cool_collision(player.box,mobj11.box,player,mobj11);
      check_cool_collision(player.box,mobj12.box,player,mobj12);
      check_cool_collision(player.box,mobj13.box,player,mobj13);
      
      check_cool_collision(player.box,mobj14.box,player,mobj14);
      check_cool_collision(player.box,mobj15.box,player,mobj15);
      
      check_cool_push_collision(player.box,pue.box,player,pue);
      check_cool_push_collision(player.box,pue2.box,player,pue2);
      check_cool_push_collision(player.box,pue3.box,player,pue3);
      
      
       if ((beam==true) && (check_collision(player.box, bar)))
       {
          living=false; 
       }
        
       if (check_collision(player.box, over_line))
       {
          win=true;
       }
       
       
     for(int s=0; s<10000; s++)
       {
          if (sh_en1.array[s].active==true)
             if (check_collision( sh_en1.array[s].box, player.box))
                living=false;
                
          if (sh_en.array[s].active==true)
             if (check_collision( sh_en.array[s].box, player.box))
                living=false;
                
          if (sh_en2.array[s].active==true)
             if (check_collision( sh_en2.array[s].box, player.box))
                living=false;
                
          if (sh_en3.array[s].active==true)
             if (check_collision( sh_en3.array[s].box, player.box))
                living=false;
                
          if (sh_en4.array[s].active==true)
             if (check_collision( sh_en4.array[s].box, player.box))
                living=false;
                
          if (sh_en5.array[s].active==true)
             if (check_collision( sh_en5.array[s].box, player.box))
                living=false;
       }
       
     
}

void SinglePlayer::render()
{
     
		apply_surface(0,0,shit_background,screen);
		
		apply_surface(over_line.x-camera.x,over_line.y-camera.y,spr_finish_line,screen);
		apply_surface(3*50-camera.x,52*50+11-camera.y,spr_thorns,screen);

		mapy.draw();
        bar_draw();
		
        player.draw();

	    for(int s=0; s<10000; s++)
	    {
           if (sh_en3.array[s].active==true)
           {
              sh_en3.array[s].draw();
              sh_en3.array[s].boolet_fire();   
           }
           
           if (sh_en2.array[s].active==true)
           {
              sh_en2.array[s].draw();
              sh_en2.array[s].boolet_fire();
           }
           
           if (sh_en1.array[s].active==true)
           {
              sh_en1.array[s].draw();
              sh_en1.array[s].boolet_fire();
           }
           
           if (sh_en.array[s].active==true)
           {
              sh_en.array[s].draw();
              sh_en.array[s].boolet_fire();
           }
           
           if (sh_en4.array[s].active==true)
           {
              sh_en4.array[s].draw();
              sh_en4.array[s].boolet_fire();
           }
           
           if (sh_en5.array[s].active==true)
           {
              sh_en5.array[s].draw();
              sh_en5.array[s].boolet_fire();
           }
        }
          int hg = si_en1.box.x+(25-spr_ball[k]->w)+spr_ball[k]->w/2;
        int hj = si_en1.box.y+(25-spr_ball[k]->h)+spr_ball[k]->h/2;
  	 		
        si_en1.draw(hg,hj,k);  
        	
        simp.draw();	
        simp2.draw();
        simp3.draw();
        simp4.draw();
        
        sm_en.draw();
		sm_en1.draw();
		sm_en2.draw();
		sm_en3.draw();
		sm_en4.draw();
		sm_en5.draw();
		sm_en6.draw(mobj11.box.y-50);
		sm_en7.draw(mobj5.box.y-100);
		
		pue.draw();
		pue2.draw();
		pue3.draw();
	
		emiter1.draw();
		emiter2.draw();
		
		mobj.draw(true);
		mobj3.draw(true);

		mobj5.draw(true);
		mobj6.draw(true);

	    mobj8.draw(true);
	    mobj9.draw(true);
	    mobj10.draw(true);
 	    mobj11.draw(true);
 	    mobj12.draw(true);
 	    mobj13.draw(true);
  	    mobj14.draw(true);
 	    mobj15.draw(true);
   		mobj4.draw(true);
	   	mobj7.draw(true);
	    		
		sh_en.draw();
		sh_en1.draw();
		sh_en2.draw();
		sh_en3.draw();
		sh_en4.draw();
		sh_en5.draw();
		
		button();
		calculate_height();
        apply_surface(0,647,spr_bar,screen);
        apply_surface(160,700,spr_height,screen);
        back2.show();
        calculate_life();
        
        
}

#endif
