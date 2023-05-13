#ifndef INVADE_H_INCLUDED
#define INVADE_H_INCLUDED

#include "defender.h"
#include "attacker.h"
#include "global.h"
class Def;
class Att;

class Invade{
public:
    Invade(int,Att*,Def*);
    virtual ~Invade();

    int getx() {return my_x;}
    int gety() {return my_y;}
    int getdmg() {return dmg;}

    bool nothing();

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

#endif
