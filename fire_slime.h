#include "defender.h"

class fire_slime:public Def
{
public:
    fire_slime(int x,int y,int type):Def(x,y,type)
    {
        frq=180;
        hp=12;
        dmg=4+(level-1)*3;
        dmg_speed=1+(level/2);

    }
};
