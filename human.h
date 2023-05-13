#include "attacker.h"

class human:public Att{
public:
    human(int road,int type):Att(road,type)
    {
        frq=150;
        hp=30+(level-1)*5;
        speed=1+(level-1);
        speed_mod=5;
        dmg=2;
        dmg_speed=0;
        dis=50;

    }

};
