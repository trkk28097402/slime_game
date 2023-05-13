#include "defender.h"

class meganut:public Def
{
public:
    meganut(int x,int y,int type):Def(x,y,type)
    {
        frq=640;
        hp=60;
        dmg=5;

    }
};


