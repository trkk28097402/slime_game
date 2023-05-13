#include "attacker.h"

class knight:public Att{
public:
    knight(int road,int type):Att(road,type)
    {
        frq=200;
        hp=50+(level-1)*20;
        speed=1;
        speed_mod=10;
        dmg=1+(level-1)/2;
        dmg_speed=0;
        dis=50+(level-1)*5;

    }

};
