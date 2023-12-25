#include "MapController.h"

#include <iostream>

bool GlobalVars::is_game_over = false;
short GlobalVars::x_size = 20, GlobalVars::y_size = 10;
bool GlobalVars::is_eated = false;
const char GlobalVars::eat = '*';
long GlobalVars::time_of_update_speed = 500;
int GlobalVars::score = 0;
// очки скорость карта голова два типа
int main() {
  setlocale(0, "RUS");
  srand(time(0));
  bool repeat = true;

  while (true) {
    MapController my_map;
    my_map.AddSnake();
    my_map.Run();
    std::cout << "You are die press r to reload" << std::endl;

    while (repeat) {
      switch (_getch()) {
      case 't':
        return 0;
        break;
      case 'r':
        repeat = false;
        break;
      }
    }
    repeat = true;
    GlobalVars::is_game_over = false;
    GlobalVars::is_eated = false;
    GlobalVars::time_of_update_speed = 500;
  }
}
