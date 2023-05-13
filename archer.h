#include "attacker.h"

class archer:public Att{
public:
    archer(int road,int type):Att(road,type)
    {
        frq=90;
        hp=25+(level-1)*5;
        speed=1;
        speed_mod=6;
        dmg=2;
        dmg_speed=3;
        dis=300+(level-1)*10;
    }

};

