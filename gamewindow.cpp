#include "gamewindow.h"

bool attcmp(Att* a,Att* b){
    if(a->getx()<b->getx()) return true;
    return false;
}
bool defcmp(Def* a,Def* b){
    if(a->getx()>b->getx()) return true;
    return false;
}

void gamewindow::game_init()
{
    char buffer[50];

    icon = al_load_bitmap("./icon.png");
    background = al_load_bitmap("./map.png");

    for(int i = 0; i < defender_num; i++)
    {
        for(int j = 0; j < 3; j++){
            sprintf(buffer, "./defender/%s%d.png", defenderclass[i], j);
            defender[i][j] = al_load_bitmap(buffer);
        }
    }

    for(int i = 0; i < attacker_num; i++)
    {
        for(int j = 0; j < 3; j++){
            sprintf(buffer, "./attacker/%s%d.png", attackerclass[i], j);
            attacker[i][j] = al_load_bitmap(buffer);
        }
    }

    al_set_display_icon(display, icon);
    al_reserve_samples(3);

    sound=al_load_sample("bgm.mp3");
    bgm=al_create_sample_instance(sound);
    al_set_sample_instance_playmode(bgm, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(bgm, al_get_default_mixer());

    font = al_load_ttf_font("myfont.ttf", 32, 0);
    sprintf(msg1, "PRESS P TO RESTART");

    font_small = al_load_ttf_font("myfont.ttf", 16, 0);

    sprintf(title, "PRESS ANY KEY TO START");

    menu = new Menu();
    menu->reset();
    reset_map();

}

void gamewindow::game_reset()
{
    reset_map();
    def_select = -1;
    lastClicked = -1;
    Coin_Inc_Count = 0;
    mute = false;
    redraw = false;

    // stop timer
    al_stop_timer(timer);
    al_stop_timer(summon_timer);

    al_stop_sample_instance(bgm);

    for(auto &&def:def_set) delete def;
    for(auto &&att:att_set) delete att;

    def_set.clear();
    att_set.clear();
    menu->reset();

    level=1;
    time_level=2500;
    score=0;


}

void gamewindow::game_play()
{
    int msg;

    srand(time(NULL));


    msg = -1;
    game_reset();

    game_begin();
    while(msg != GAME_EXIT)
    {

        msg = game_run();

        if(msg==YOU_SUCK) sprintf(msg2, "YOUR SCORE %05d",score);
        while(msg==YOU_SUCK){
            msg=restart();

        }
        if(msg==RESTART){
            game_reset();
            game_begin();
        }
    }

    show_err_msg(msg);
}

int gamewindow::restart(){

    al_wait_for_event(event_queue, &event);

    al_draw_text(font, al_map_rgb(255, 255, 255), 100, 280, 0, msg1);

    al_draw_text(font_small, al_map_rgb(255, 255, 255), 100, 350, 0, msg2);

    al_flip_display();
    if(event.type == ALLEGRO_EVENT_KEY_DOWN){
        if(event.keyboard.keycode==ALLEGRO_KEY_P){
            return RESTART;
        }
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        return GAME_EXIT;
    }
    return YOU_SUCK;

}

int gamewindow::start(){ //fail

    al_wait_for_event(event_queue, &event);
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_text(font, al_map_rgb(255, 255, 255), 10, 280, 0, title);

    al_flip_display();
    if(event.type == ALLEGRO_EVENT_KEY_DOWN){
            return GAME_CONTINUE;
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        return GAME_EXIT;
    }
    return START;

}

void gamewindow::game_begin()
{
    draw_running_map();

    al_play_sample_instance(bgm);

    al_start_timer(timer);
    al_start_timer(summon_timer);

    reset_time=al_get_timer_count(timer);
}

void gamewindow::reset_map(){
    for(int i=0;i<w_x;i++){
        for(int j=0;j<w_y;j++){
            mapdata[i][j]=-1;
        }
    }
    for(int j=0;j<w_y;j++) mapheart[j]=2;
}

int gamewindow::mod_x(int i){
    if(i<=80 || i>=800) return -1;

    return i/80;
}

int gamewindow::mod_y(int i){
    if(i<=80 || i>=480) return -1;

    return i/80;
}

int gamewindow::game_run()
{
    int error = GAME_CONTINUE;

    if (!al_is_event_queue_empty(event_queue)) {

        error = process_event();
    }
    return error;
}

int gamewindow::game_update()
{
    int i=0,j=0;

    std::sort(att_set.begin(),att_set.end(),attcmp);
    std::sort(def_set.begin(),def_set.end(),defcmp);

    bool skip=false;
    for(auto &def:def_set){

        if(def->gettype()==NUT || def->gettype()==MEGANUT) continue;

        for(auto &att:att_set){


            skip=false;
            if(def->getx()>=att->getx()) continue;

            if(def->same_y(att)){
                skip=true;
                if(def->detect(att)){
                    def->fighting_flip(true);
                    break;
                }
            }

            if(skip) break;
        }
    }

    for(auto &att:att_set){

        //if(att->gettype()== || def->gettype()== ) continue;

        for(auto &def:def_set){


            skip=false;
            if(att->getx()<def->getx()) continue;

            if(def->same_y(att)){ //用def的function(懶得寫兩個)
                skip=true;
                if(att->detect(def)){
                    //att->invade_flip(true);
                    break;
                }
            }

            if(skip) break;
        }
    }


    for(i=0;i<att_set.size();i++){
        bool isdead=false;
        bool dead=false;
        for(auto def:def_set){
            isdead=def->trigger(att_set[i]);
            if(isdead) dead=true;
        }

        if(dead){ //死了

            Att *tmp=att_set[i];
            menu->change(tmp->gettype());
            score+=tmp->gettype()*level;
            att_set.erase(att_set.begin()+i);
            i--;
            delete tmp;

        }else if(att_set[i]->getx()<=0){ //走到底線
            Att *tmp=att_set[i];

            mapheart[tmp->gety()/80-1]--;
            att_set.erase(att_set.begin()+i);
            i--;
            delete tmp;

            for(auto &&att:att_set) delete att;
            att_set.clear();
            break;
        }
    }

    for(i=0;i<def_set.size();i++){
        bool isdead=false;
        bool dead=false;
        for(j=0;j<att_set.size();j++){
            if(att_set[j]->freezing()) continue;
                isdead=att_set[j]->trigger(def_set[i]);
                if(isdead){
                    if(att_set[j]->gettype()==BISHOP){
                        for(int k=0;k<(3+level/2) && j-k>=0;k++){
                            att_set[j-k]->heal(att_set[j]->getdmg());
                        }
                    }
                    dead=true;
                }
        }

        if(dead){
            Def* tmp=def_set[i];

            for(auto att:att_set){
                if(att->same_target(tmp)) att->my_target_dead();

            }

            def_set.erase(def_set.begin()+i);
            i--;
            delete tmp;

        }

    }


    for(auto &def:def_set){
        def->update_fight();

    }

    for(int i=0;i<w_y;i++){
        if(mapheart[i]==0) return YOU_SUCK;

    }
    return GAME_CONTINUE;
}


void gamewindow::show_err_msg(int msg)
{
    if(msg == GAME_TERMINATE)
        fprintf(stderr, "Game Terminated...");
    else
        fprintf(stderr, "unexpected msg: %d", msg);

    game_destroy();
    exit(9);
}

void gamewindow::game_destroy()
{
    game_reset();

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_font(font);

    al_destroy_timer(timer);
    al_destroy_timer(summon_timer);
/*
    for(int i = 0; i < defender_num; i++)
        al_destroy_bitmap(defender[i]);

    for(int i = 0; i < attacker_num; i++)
        al_destroy_bitmap(attacker[i]);
*/
    al_destroy_bitmap(icon);
    al_destroy_bitmap(background);

    delete menu;

    al_destroy_sample(sound);
    al_destroy_sample_instance(bgm);
}

void gamewindow::draw_running_map()
{
    al_clear_to_color(al_map_rgb(100, 100, 100));
    al_draw_bitmap(background, 0, 0, 0);
    for(int i=0;i<w_y;i++){
        if(mapheart[i]==2) al_draw_bitmap(icon, 0, i*80+80, 0);
    }

    for(std::vector<Def*>::iterator it = def_set.begin(); it != def_set.end(); it++){

        //(*it)->fighting_flip(true);
        (*it)->draw();

    }

    for(std::vector<Att*>::iterator it = att_set.begin(); it != att_set.end(); it++)
        (*it)->draw();

    if(def_select != -1) Def::select(mouse_x, mouse_y, def_select);

    menu->draw();




    al_flip_display();


}

int gamewindow::process_event()
{

    int instruction=GAME_CONTINUE;
    al_wait_for_event(event_queue, &event);
    redraw = false;
    //timer
    if(event.type == ALLEGRO_EVENT_TIMER) {
        redraw = true;
        if(event.timer.source == timer) {

            if(Coin_Inc_Count == 0)
                menu->change(Coin_Time_Gain);
            Coin_Inc_Count = (Coin_Inc_Count + 1) % CoinSpeed;

            if((al_get_timer_count(timer)-reset_time)%time_level==0) level_up();

        }
        else if(event.timer.source == summon_timer) {

            group=((int)rand()%(500/level));
            int counting=al_get_timer_count(summon_timer)+1-reset_time;

            int mod_level=(level*level/2)%5;
            if(mod_level<=0) mod_level=1;
            int difficult_boost=level%(mod_level+1);
            if(difficult_boost==0) difficult_boost+=1;
            while(difficult_boost--){
                if(counting%(600/mod_level)==0){
                    Att *t = create_attacker(HUMAN);
                    if(group==HUMAN){
                        Att *t1 = create_attacker(HUMAN);
                        if(t1) att_set.push_back(t1);
                        Att *t2 = create_attacker(HUMAN);
                        if(t2) att_set.push_back(t2);
                        Att *t3 = create_attacker(HUMAN);
                        if(t3) att_set.push_back(t3);
                        Att *t4 = create_attacker(HUMAN);
                        if(t4) att_set.push_back(t4);
                    }
                    if(t) att_set.push_back(t);
                }
                if(counting%(980/mod_level)==0){
                    Att *t = create_attacker(ARCHER);
                    if(group==ARCHER){
                        Att *t1 = create_attacker(ARCHER);
                        if(t1) att_set.push_back(t1);
                        Att *t2 = create_attacker(ARCHER);
                        if(t2) att_set.push_back(t2);
                        Att *t3 = create_attacker(ARCHER);
                        if(t3) att_set.push_back(t3);
                    }
                    if(t) att_set.push_back(t);
                }
                if(counting%(1240/mod_level)==0){
                    Att *t = create_attacker(WITHER);
                    if(group==WITHER){
                        Att *t1 = create_attacker(WITHER);
                        if(t1) att_set.push_back(t1);
                        Att *t2 = create_attacker(WITHER);
                        if(t2) att_set.push_back(t2);
                    }
                    if(t) att_set.push_back(t);
                }
                if(counting%(1550/mod_level)==0){
                    Att *t = create_attacker(KNIGHT);
                    if(group==KNIGHT){
                        Att *t1 = create_attacker(KNIGHT);
                        if(t1) att_set.push_back(t1);
                        Att *t2 = create_attacker(KNIGHT);
                        if(t2) att_set.push_back(t2);
                    }
                    if(t) att_set.push_back(t);
                }
                if(counting%(2000/mod_level)==0){
                    Att *t = create_attacker(BISHOP);
                    if(group==BISHOP){
                        Att *t1 = create_attacker(BISHOP);
                        if(t1) att_set.push_back(t1);
                        Att *t2 = create_attacker(BISHOP);
                        if(t2) att_set.push_back(t2);
                    }
                    if(t) att_set.push_back(t);
                }
                if(counting==time_level-1){
                    Att *t = create_attacker(BLACK_KNIGHT);
                    if(t) att_set.push_back(t);

                }

            }

        }
    }
    //select
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        if(event.mouse.button == 1) {
            if(def_select != -1 && mouse_hover(0, 0, 800, 640)) {
                Def *t = create_defender(def_select);

                if(t == NULL)
                    printf("Wrong place\n");
                else {
                    def_set.push_back(t);
                }
            }
        }
        def_select = menu->mousein(mouse_x, mouse_y);
    }else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
        mouse_x = event.mouse.x;
        mouse_y = event.mouse.y;
        menu->mousein(mouse_x, mouse_y);

    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        return GAME_EXIT;
    }
    if(redraw) {
        // update each object in game
        instruction = game_update();

        // Re-draw map
        draw_running_map();
        redraw = false;
    }

    return instruction;
}

Def* gamewindow::create_defender(int type){
    Def *tmp = NULL;

    int x=mod_x(mouse_x),y=mod_y(mouse_y);
    printf("%d %d:",mouse_x,mouse_y);
    if(x!=-1 && y!=-1)if(mapdata[x-1][y-1]==-1){
        printf("%d %d\n",x,y);
        switch(type){
            case SLIME:
                tmp=new slime(x,y,type);
                break;
            case WATER_SLIME:
                tmp=new water_slime(x,y,type);
                break;
            case FIRE_SLIME:
                tmp=new fire_slime(x,y,type);
                break;
            case THREE_SLIME:
                tmp=new three_slime(x,y,type);
                break;
            case ICE_SLIME:
                tmp=new ice_slime(x,y,type);
                break;
            case NUT:
                tmp=new nut(x,y,type);
                break;
            case MEGANUT:
                tmp=new meganut(x,y,type);
                for(auto &&def:def_set) def->buff();
                break;
            default:
                break;
        }
        menu->change(menu->get_price(type));
    }

    return tmp;

}

Att* gamewindow::create_attacker(int type){
    Att *tmp=NULL;

    int road=((int)std::rand())%5;
    switch(type){
        case HUMAN:
            tmp=new human(road,type);
            break;
        case WITHER:
            tmp=new wither(road,type);
            break;
        case KNIGHT:
            tmp=new knight(road,type);
            break;
        case ARCHER:
            tmp=new archer(road,type);
            break;
        case BISHOP:
            tmp=new bishop(road,type);
            break;
        case BLACK_KNIGHT:
            tmp=new black_knight(road,type);
            break;
        default:
            break;
    }

    return tmp;

}

bool gamewindow::mouse_hover(int startx, int starty, int width, int height)
{
    if(mouse_x >= startx && mouse_x <= startx + width)
        if(mouse_y >= starty && mouse_y <= starty + height)
            return true;

    return false;
}

gamewindow::gamewindow(){
    if(!al_init())
        show_err_msg(-1);
    printf("Game Initializing...\n");

    display = al_create_display(window_width, window_height);
    event_queue = al_create_event_queue();

    timer = al_create_timer(1.0 / FPS);
    summon_timer = al_create_timer(1.0 / FPS);

    if(timer == NULL)
        show_err_msg(-1);

    if (display == NULL || event_queue == NULL)
        show_err_msg(-1);

    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon

    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_timer_event_source(summon_timer));



    game_init();
}


void gamewindow::level_up(){
    time_level=time_level*(level+2)/level;
    level+=1;
    menu->change((level+5)*level);


}
