#include "defender.h"

class nut:public Def
{
public:
    nut(int x,int y,int type):Def(x,y,type)
    {
        frq=1000;
        hp=35;
        dmg=2;

    }
};

