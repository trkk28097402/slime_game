#ifndef MAINWINDOW_H_INCLUDED
#define MAINWINDOW_H_INCLUDED

#include <vector>
#include <list>
#include <time.h>

#include "allegro_include.h"
#include "global.h"
#include "menu.h"
#include "object_include.h"

#define GAME_INIT -1
#define GAME_SETTING 0
#define GAME_SELECT 1
#define GAME_BEGIN 2
#define GAME_CONTINUE 3
#define GAME_FAIL 4
#define GAME_TERMINATE 5
#define GAME_NEXT_LEVEL 6
#define GAME_EXIT 7

#define YOU_SUCK -2
#define RESTART -3
#define START -4

// clock rate
const float FPS = 60;

// total number of level
const int LevelNum = 4;

// 1 coin every 2 seconds
const int CoinSpeed = FPS * 2;
const int Coin_Time_Gain = 1;

class gamewindow
{
public:
    // constructor
    gamewindow();
    // each process of scene
    void game_init();
    void game_reset();
    void game_play();
    void game_begin();

    void reset_map();

    int game_run();


    int mod_x(int);
    int mod_y(int);
    //int game_update();

    int game_update();
    void show_err_msg(int msg);
    void game_destroy();

    void draw_running_map();

    int process_event();

    bool mouse_hover(int, int, int, int);

    Def* create_defender(int);
    Att* create_attacker(int);

    void level_up();
    bool initial = true;

    int restart();

    int start();

private:
    ALLEGRO_BITMAP *icon;
    ALLEGRO_BITMAP *defender[defender_num][3];
    ALLEGRO_BITMAP *attacker[attacker_num][3];
    ALLEGRO_BITMAP *background = NULL;

    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_FONT *font = NULL;
    ALLEGRO_FONT *font_small = NULL;
    char msg1[50];
    char msg2[50];
    char title[50];

    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_EVENT event;
    ALLEGRO_TIMER *timer = NULL;

    ALLEGRO_TIMER *summon_timer = NULL;

    ALLEGRO_SAMPLE *sound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *bgm = NULL;

    Menu *menu = NULL;;

    std::vector<Def*> def_set;
    std::vector<Att*> att_set;

    int Coin_Inc_Count = 0;
    int mouse_x, mouse_y;
    int def_select = -1, lastClicked = -1;
    int group=0;
    int reset_time=0;
    bool redraw = false;
    bool mute = false;
};


#endif
