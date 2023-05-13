#include "attacker.h"

class bishop:public Att{
public:
    bishop(int road,int type):Att(road,type)
    {
        frq=300-(level-1)*10;
        hp=25+(level-1)*3;
        speed=1+level;
        speed_mod=20;
        dmg=3+(level-1)/2;
        dmg_speed=2;
        dis=200+(level-1)/2*10;

    }

};

