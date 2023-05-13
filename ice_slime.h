#include "defender.h"

class ice_slime:public Def
{
public:
    ice_slime(int x,int y,int type):Def(x,y,type)
    {
        frq=30-(level-1)*2;
        hp=5+(level-1)*3;
        dmg=0;
        dmg_speed=5;
    }
};

