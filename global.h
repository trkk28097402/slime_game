#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <utility>
#include <cstdlib>
#include <string>

#include "allegro_include.h"

#define window_width 800
#define window_height 640
#define w_x 9
#define w_y 5
#define menu_x 7
#define max_dmg_speed 10
#define font_size 24

#define defender_num 7
#define attacker_num 6

extern char defenderclass[][20];
extern char attackerclass[][20];
extern int mapdata[w_x][w_y];
extern int mapheart[w_y];
extern int defenderwidth;
extern int defenderheight;
extern int level;
extern int time_level;
extern int score;
extern int best;

enum {SLIME = 0, WATER_SLIME, FIRE_SLIME, THREE_SLIME, ICE_SLIME, NUT, MEGANUT};
enum {HUMAN = 0, WITHER, KNIGHT, ARCHER, BISHOP, BLACK_KNIGHT};

#endif
