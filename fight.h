#ifndef FIGHT_H_INCLUDED
#define FIGHT_H_INCLUDED


#include "defender.h"
#include "attacker.h"
#include "global.h"
class Def;
class Att;

class Fight{
public:
    Fight(int,Def*,Att*);
    virtual ~Fight();

    int getx() {return my_x;}
    int gety() {return my_y;}
    int getdmg() {return dmg;}
    int gettype() {return my_type;}

    void draw();
protected:
    ALLEGRO_BITMAP *img;
    int dir=0;
    int my_x=0,my_y=0;
    int my_type=0;
    int speed=1;
    int dmg=0;
    char filename[50];
};


#endif // FIGHT_H_INCLUDED
