#include <iostream>
#include "MapController.h"

bool GlobalVars::isGameOver = false;
short GlobalVars::x_size=20, GlobalVars::y_size=10;
bool GlobalVars::isEated = false;
const char GlobalVars::eat = '*';
long GlobalVars::speed_time = 500;
int GlobalVars::score = 0;
//очки скорость карта голова
int main(){
    setlocale(0, "RUS");
    //char ch;
    //while (ch=_getch()) {
    //    std::cout << (int)ch << std::endl;
    //}
    //
    //ch = _getch();//-32
    //ch = _getch();//-32
    //ch = _getch();//-32
    srand(time(0));
    bool repeat = true;
    while (true) {
        MapController my_map;
        my_map.AddSnake();
        my_map.Run();
        std::cout << "You are die press r to reload" << std::endl;
        while (repeat) {
            switch (_getch()) {
            case 't': return 0; break;
            case 'r':repeat = false; break;
            }
        }
        repeat = true;
        GlobalVars::isGameOver = false;
        GlobalVars::isEated = false;
        GlobalVars::speed_time = 500;
    }

}
