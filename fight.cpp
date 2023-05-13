#include "fight.h"

Fight::Fight(int type,Def* a,Att *b){
    if(a->getx()<b->getx()) dir=1;
    else dir=-1;

    this->my_x=a->my_x;
    this->my_y=a->my_y;
    this->my_type=type;
    this->dmg=a->getdmg();
    this->speed=a->dmg_speed;
    sprintf(filename, "./defender/%s3.png", defenderclass[type]);
    img = al_load_bitmap(filename);
}

Fight::~Fight(){
    al_destroy_bitmap(img);
}

void Fight::draw(){
    al_draw_bitmap(img,my_x,my_y,0);

    my_x+= dir*(speed);
}
