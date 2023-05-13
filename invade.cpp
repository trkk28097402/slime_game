#include "invade.h"

Invade::Invade(int type,Att *a,Def *b){
    if(a->getx()>=b->getx()) dir=-1;
    else dir=1;

    this->my_x=b->getx();
    this->my_y=b->gety();
    this->my_type=type;
    this->dmg=a->getdmg();
    this->speed=a->getdmg_speed();
    sprintf(filename, "./attacker/%s3.png", attackerclass[type]);
    img = al_load_bitmap(filename);

}

Invade::~Invade(){
    al_destroy_bitmap(img);
}

void Invade::draw(){

    if(my_type==ARCHER) al_draw_bitmap(img,my_x+40,my_y,0);
    else al_draw_bitmap(img,my_x,my_y,0);

}
