#include "defender.h"

class slime:public Def
{
public:
    slime(int x,int y,int type):Def(x,y,type)
    {
        frq=70;
        hp=10+(level-1)*2;
        dmg=2+(level-1)*2;
        dmg_speed=3;

    }
};
