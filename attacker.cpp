#include "defender.h"

bool reach(Invade *a,Def* b){
    if( (a->getx()==b->getx()) && (a->gety()==b->gety()) ) return true;
    return false;
}

Att::Att(int road,int type){
    st_x=750,ed_x=0,st_y=ed_y=road*80+80;
    my_type=type;
    my_x=st_x,my_y=st_y;

    for(int i=0;i<3;i++){
        sprintf(filename, "./attacker/%s%d.png", attackerclass[type],i);
        img[i] = al_load_bitmap(filename);
    }

    att_timer=al_create_timer(1.0 / 60);
    al_start_timer(att_timer);

    sprintf(filename, "./attacker/%s.wav", attackerclass[type]);
    sound=al_load_sample(filename);
    att_sound=al_create_sample_instance(sound);
    al_set_sample_instance_playmode(att_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(att_sound, al_get_default_mixer());

}

Att::~Att()
{
    al_destroy_bitmap(img[0]);
    al_destroy_bitmap(img[1]);
    al_destroy_bitmap(img[2]);

    al_destroy_timer(att_timer);

    al_destroy_sample(sound);
    al_destroy_sample_instance(att_sound);
}

bool Att::harm(int point){
    hp-=point+bonus_damage;
    printf("%d\n",hp);
    return hp<=0;
}

bool Att::speed_cal(){
    speed_count++;
    speed_count%=speed_mod;
    if(!speed_count) return true;
    return false;
}

void Att::draw(){
    tiktok=al_get_timer_count(att_timer);

    if(tiktok-water_time>debuff_time){
        onwater=false;
    }
    if(tiktok-fire_time>debuff_time){
        bonus_damage=0;
        onfire=false;
    }
    if(tiktok-ice_time>debuff_time){
        onice=false;
    }
    if(tiktok-freeze_time>debuff_time){
        onfreeze=false;
    }


    tiktok%=frq;
    if(speed_cal() && invade_object==NULL && !onfreeze){
      my_x-=speed;
      img_count++;
      img_count%=2;
    }

    if(invade_object&&tiktok<frq/2&&my_type!=HUMAN&&my_type!=KNIGHT) invade_object->draw();


    if(invade_object&&tiktok<10&&!onfreeze){
        if(tiktok==0){
            al_play_sample_instance(att_sound);
        }
        al_draw_bitmap(img[2], my_x, my_y, 0);

    }else{
        al_draw_bitmap(img[img_count], my_x, my_y, 0);
    }
    if(onfreeze){

        al_draw_filled_rectangle(my_x+20, my_y+20, my_x+60, my_y+60, al_map_rgba(0, 250, 250, 50));
    }
    if(onfire){

        al_draw_filled_rectangle(my_x+20, my_y+20, my_x+60, my_y+60, al_map_rgba(255, 55, 0, 50));
    }
    if(onmelt){

        al_draw_filled_rectangle(my_x+20, my_y+20, my_x+60, my_y+60, al_map_rgba(0, 0, 0, 50));
        onmelt=false;
    }
}

void Att::debuff(int type){

    tiktok=al_get_timer_count(att_timer);

    if(type==WATER_SLIME){
        this->onwater=1;
        this->water_time=tiktok;
    }
    if(type==FIRE_SLIME){
        this->onfire=1;
        this->fire_time=tiktok;
    }
    if(type==ICE_SLIME){
        this->onice=1;
        this->ice_time=tiktok;
    }

    if(onwater && onice){
        this->onfreeze=true;
        this->freeze_time=tiktok;
        onwater=false,onice=false;
    }
    if(onwater && onfire){
        this->onmelt=true;
        onwater=false,onfire=false;
        this->hp-=5+(level-1)*level;
        if(this->hp<=0) this->hp=1;
    }
    if(onfire){
        bonus_damage+=0.2+(level-1)*0.2;
    }
}

bool Att::detect(Def* target){
    bool iattack=false;
    Invade *tmp=NULL;

    if(onfreeze) return false;
    if (target->my_y==this->my_y){

        if(target->my_x+dis>=this->my_x && target->my_x<=this->my_x){


                if(this->invade_object) return true;
                tmp=new Invade(my_type,this,target);
                this->invade_object=tmp;

                iattack=true;

        }
    }

    return true;

}

bool Att::trigger(Def *target){

    if(onfreeze) return false;
    if(invade_object==NULL) return false;
    if(!reach(invade_object,target)) return false;
    tiktok=al_get_timer_count(att_timer)%frq;

    if(tiktok) return false;
    bool dead=false;
    current_target=target;
    dead=target->harm(invade_object->getdmg());
    if(dead){
        printf("dead\n");
        invade_object=NULL;
        return true;

    }

    return false;
}

bool Att::same_target(Def* tmp){
    if(tmp==current_target) return true;
    return false;
}
