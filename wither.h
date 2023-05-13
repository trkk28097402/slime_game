#include "attacker.h"

class wither:public Att{
public:
    wither(int road,int type):Att(road,type)
    {
        frq=150;
        hp=20+(level-1)*5;
        speed=2;
        speed_mod=13;
        dmg=5+(level-1);
        dmg_speed=1;
        dis=250;
    }

};

