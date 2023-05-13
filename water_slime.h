#include "defender.h"

class water_slime:public Def
{
public:
    water_slime(int x,int y,int type):Def(x,y,type)
    {
        frq=100;
        hp=15+(level-1)*5;
        dmg=2+(level-1)*2;
        dmg_speed=2;

    }
};

