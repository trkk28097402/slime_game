#include "defender.h"

bool reach(Fight *a,Att* b){
    if( (abs(a->getx() - b->getx())<=max_dmg_speed) && (a->gety()==b->gety()) ) return true;
    return false;
}

Def::Def(int x,int y,int type){
    mapdata[x-1][y-1]=type;
    my_type=type;
    my_x=x*80,my_y=y*80;
    for(int i=0;i<3;i++){
        sprintf(filename, "./defender/%s%d.png", defenderclass[type],i);
        img[i] = al_load_bitmap(filename);
    }

    id_timer=al_create_timer(1.0 / 60);
    al_start_timer(id_timer);

    sprintf(filename, "./defender/%s.wav", defenderclass[type]);
    sound=al_load_sample(filename);
    att_sound=al_create_sample_instance(sound);
    al_set_sample_instance_playmode(att_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(att_sound, al_get_default_mixer());
}

Def::~Def()
{
    mapdata[my_x/80-1][my_y/80-1]=-1;
    al_destroy_bitmap(img[0]);
    al_destroy_bitmap(img[1]);
    al_destroy_bitmap(img[2]);
    al_destroy_timer(id_timer);
    for(auto &&i:this->fight_set) delete i;

    this->fight_set.clear();

    al_destroy_sample(sound);
    al_destroy_sample_instance(att_sound);
}

bool Def::harm(int point){


    hp-=point;

    printf("%d\n",hp);
    return hp<=0;
}

void Def::draw(){


    tiktok=al_get_timer_count(id_timer)%frq;

    if(frq_count==0 && fighting) al_play_sample_instance(att_sound);
    if(tiktok==0 && my_type==NUT) harm(-2);
    if(tiktok==0 && my_type==MEGANUT) harm(-5);

    if(tiktok>frq/2){
        set_img_id(0);
        if(fighting) fighting_flip(false);
    }
    else{
        if(fighting) set_img_id(2);
        else set_img_id(1);
    }

    al_draw_bitmap(img[img_id], my_x, my_y, 0);

    for(int i=0; i < fight_set.size(); i++){
        fight_set[i]->draw();
    }

    //if(fighting) fighting_flip(false);

}

void Def::update_fight(){
    int pos_x=0;
    for(int i=0; i < fight_set.size(); i++)
    {
        Fight *tmp = fight_set[i];
        pos_x=fight_set[i]->getx();
        if(pos_x>=800 || pos_x<=0) {
            fight_set.erase(fight_set.begin() + i);
            i--;
            delete tmp;
        }
    }
}

void Def::select(int x,int y,int type){
    char filename[50];
    ALLEGRO_BITMAP *bitmap;

    int draw_x=x/80*80,draw_y=y/80*80;
    sprintf(filename, "./defender/%s0.png", defenderclass[type]);
    bitmap = al_load_bitmap(filename);
    al_draw_bitmap(bitmap, draw_x, draw_y, 0);

    al_destroy_bitmap(bitmap);
}

bool Def::detect(Att *target){
    bool idefend=false;
    Fight *tmp;


    if (target->my_y==this->my_y){

        if(target->my_x>this->my_x){
            if(frq_count==0){
                tmp=new Fight(my_type,this,target);
                this->fight_set.push_back(tmp);

                idefend=true;
                //if(idefend) printf("me:%d target:%d\n",this->my_x,target->my_x);
            }
            frq_count++;
            frq_count%=frq;
        }
    }

    return idefend;
}

bool Def::trigger(Att *target){
    bool dead=false;

    for(int i=0;i<this->fight_set.size();i++){
        if(reach(fight_set[i],target)){

            target->debuff(fight_set[i]->gettype());
            dead = target->harm(fight_set[i]->getdmg());
            fight_set.erase(fight_set.begin()+i);
            if(dead) return true;

        }

    }

    return false;
}

bool Def::same_y(Att *target){
    if (target->my_y==this->my_y) return true;
    return false;
}

