#include "attacker.h"

class black_knight:public Att{
public:
    black_knight(int road,int type):Att(road,type)
    {
        frq=120-(level-1)*5;
        hp=55+(level-1)*20;
        speed=1+(level-1);
        speed_mod=10+(level-1);
        dmg=10+(level-1)*10;
        dmg_speed=1+(level-1);
        dis=100+(level-1)*20;

    }

};

