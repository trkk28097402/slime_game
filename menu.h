#include "global.h"

class Menu
{
public:
    Menu();
    virtual ~Menu();
    void reset();
    void draw();

    int mousein(int,int);
    int get_price(int type) {return price[type];}
    bool can_buy(int);

    void change(int change) {coin+=change;}

private:
    std::vector<ALLEGRO_BITMAP*> menus[defender_num];
    int coin=0;
    int price[defender_num]={-6,-10,-12,-20,-18,-15,-30};

    ALLEGRO_FONT *menuFont_big;
    ALLEGRO_FONT *menuFont_small;
    ALLEGRO_FONT *menuFont_mini;

    ALLEGRO_TIMER *clock = NULL;

    int tiktok=0;
    int reset_time=0;
};
