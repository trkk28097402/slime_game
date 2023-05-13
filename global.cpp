#include "global.h"

//int TowerRadius[] = {80, 80, 70, 110, 150};
char defenderclass[][20] = {"slime","water_slime","fire_slime","three_slime","ice_slime","nut","meganut"};
char attackerclass[][20] = {"human","wither","knight","archer","bishop","black_knight"};
int mapdata[w_x][w_y];
int mapheart[w_y];
int defenderwidth = 80, defenderheight = 80;
int attackerwidth = 80, attackerheight = 80;
int level=1;
int time_level=2500;
int score=0;
int best=0;
