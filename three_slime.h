#include "defender.h"

class three_slime:public Def
{
public:
    three_slime(int x,int y,int type):Def(x,y,type)
    {
        frq=90;
        hp=40+(level-1)*3;
        dmg=7+(level-1)*3;
        dmg_speed=3;
    }
};
