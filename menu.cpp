#include "menu.h"

Menu::Menu(){
    char filename[50];

    coin=0;

    for(int i=0;i<defender_num;i++){
        for(int j=0;j<3;j++){

            ALLEGRO_BITMAP *tmp;
            sprintf(filename, "./defender/%s%d.png", defenderclass[i],j);

            tmp = al_load_bitmap(filename);
            menus[i].push_back(tmp);

        }

    }

    menuFont_big = al_load_ttf_font("myfont.ttf", 20, 0);
    menuFont_small = al_load_ttf_font("myfont.ttf", 12, 0);
    menuFont_mini = al_load_ttf_font("myfont.ttf", 8, 0);

    clock=al_create_timer(1.0 / 1);
    al_start_timer(clock);
}

Menu::~Menu(){
    al_destroy_font(menuFont_big);
    al_destroy_font(menuFont_small);
    al_destroy_font(menuFont_mini);

    al_destroy_timer(clock);
}

void Menu::reset(){
    coin=1000;
    reset_time=al_get_timer_count(clock);
}

void Menu::draw(){
    char buffer[50];

    sprintf(buffer, "Score %d", score);
    al_draw_text(menuFont_big, al_map_rgb(255, 255, 255), 80, 480, 0, buffer);

    sprintf(buffer, "Energy %d", coin);
    al_draw_text(menuFont_small, al_map_rgb(255, 255, 255), 80, 540, 0, buffer);

    sprintf(buffer, "Level %d", level);
    al_draw_text(menuFont_mini, al_map_rgb(255, 255, 255), 80, 580, 0, buffer);

    tiktok=al_get_timer_count(clock)-reset_time;
    sprintf(buffer, " Timer  %02d %02d", tiktok/60, tiktok%60);
    al_draw_text(menuFont_mini, al_map_rgb(255, 255, 255), 160, 580, 0, buffer);

    int gx=80,gy=0;
    int x=20,y=0;
    for(int i=0;i<defender_num;i++){
        sprintf(buffer,"%d", -price[i]);

        if(can_buy(i)){
            al_draw_bitmap(menus[i][1],x+gx*i,y+gy*i,0);
        }else{
            al_draw_bitmap(menus[i][0],x+gx*i,y+gy*i,0);
        }
        al_draw_text(menuFont_small, al_map_rgba(255, 255, 255,50), x+gx*i, y+gy*i+50, 0, buffer);
    }
}

int Menu::mousein(int mouse_x,int mouse_y){
    if(mouse_y>=0 && mouse_y<=80 && mouse_x <= menu_x*80 && mouse_x>=0){
        int type=mouse_x/80;
        if(can_buy(type)) return type;

    }

    return -1;

}

bool Menu::can_buy(int type){
    if(type<0 || type>=defender_num) return false;

    return (coin + price[type] >= 0);
}

