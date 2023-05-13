#ifndef Def_H_INCLUDED
#define Def_H_INCLUDED

#include "global.h"
#include "attacker.h"
#include "fight.h"

class Att;
class Fight;

class Def
{
public:
    Def(int,int,int);
    virtual ~Def();

    void draw();
    bool harm(int);
    void update_fight();
    static void select(int,int,int);

    bool detect(Att*);
    bool trigger(Att*);
    bool same_y(Att*);

    int getx() {return my_x;}
    int gety() {return my_y;}
    int getdmg() {return dmg;}
    int gettype() {return my_type;}
    int buff() {hp+=(level-1)*5,dmg+=level/3;}

    void set_img_id(int tmp) {img_id=tmp;}
    void fighting_flip(bool tmp) {fighting=tmp;}


    friend class Att;
    friend class Fight;
protected:
    int frq = 50;
    int frq_count=0;
    int hp = 10;
    int dmg = 1;
    int dmg_speed = 1;

    int my_x,my_y;
    int my_type=-1;
    bool isClicked = false;

    std::vector<Fight*> fight_set;
    ALLEGRO_BITMAP *img[3];
    int img_id=0;
    bool fighting=false;

    char filename[50];

    ALLEGRO_TIMER *id_timer = NULL;
    int tiktok=0;

    ALLEGRO_SAMPLE *sound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *att_sound = NULL;
};


#endif

