#ifndef Att_H_INCLUDED
#define Att_H_INCLUDED


#include "defender.h"
#include "global.h"
#include "invade.h"

class Invade;
class Def;

class Att
{
public:
    Att(int,int);
    virtual ~Att();

    void draw();

    void debuff(int type);
    bool harm(int);
    void heal(int point) {harm(-point);}
    bool speed_cal();

    bool detect(Def*);
    bool trigger(Def*);

    int getx() {return my_x;}
    int gety() {return my_y;}
    int gettype() {return my_type;}
    int getdmg() {return dmg;}
    int getdmg_speed() {return dmg_speed;}

    bool freezing() {return onfreeze;}

    bool same_target(Def*);
    void my_target_dead() {invade_object=NULL;}

    friend class Def;
    friend class Fight;
protected:
    int frq=50;
    int frq_count=1;
    int hp=50;
    int speed=1;
    int speed_mod=3;
    int speed_count=0;
    int my_x,my_y;
    int my_type;
    int img_count=0;

    int dis=0;
    int dmg=1;

    int dmg_speed=1;

    double bonus_damage=0;

    Invade* invade_object=NULL;
    int st_x,st_y,ed_x,ed_y;
    ALLEGRO_BITMAP *img[3];
    char filename[50];

    ALLEGRO_TIMER *att_timer = NULL;

    int water_time=0,fire_time=0,ice_time=0,freeze_time=0;
    int debuff_time=300;
    bool onwater=false,onfire=false,onice=false,onfreeze=false,onmelt=false;

    int tiktok=0;

    Def *current_target=NULL;

    ALLEGRO_SAMPLE *sound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *att_sound = NULL;
};

#endif
