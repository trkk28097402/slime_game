#include "gamemap.h"

void gamemap::reset(){
    for(int i=0;i<w_x;i++)for(int j=0;j<w_y;j++) _map[{i,j}]=0;
}

int gamemap::select(int x,int y){

    x=(x-80)/w_x,y=(y-64)/w_y;

    if(x>0&&y>0 && _map[{x,y}]==0) _map[{x,y}]=1;

    return 1;

}
