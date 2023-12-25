#include "MapController.h"

#include <iostream>
#include <string>

void MapController::Move() {
  auto smth_snake = list_snakes.begin();
  auto smth_snake_end = list_snakes.end();

  while (smth_snake != smth_snake_end) {
    (*smth_snake)->Move();

    if (GlobalVars::isEated) {
      //++GlobalVars::score;
      auto snake_model = (*smth_snake)->GetModel();
      auto segment = snake_model->GetModelSegment(0);
      cur_map_model->SetModelIndex(' ', segment.cur_pos.x,
                                   segment.cur_pos.y);
      addEat();
    }
    ++smth_snake;
  }
}
// добавл€ем еду на карту
void MapController::addEat() {
  bool is_not_empty = true;
  short x, y;

  while (is_not_empty) {
    x = rand() % GlobalVars::x_size;
    y = rand() % GlobalVars::y_size;

    if (cur_map_model->GetModelIndex(x, y).data == ' ') {
      cur_map_model->SetModelIndex(GlobalVars::eat, x, y);
      is_not_empty = false;
    }
  }
}

void MapController::Draw() {
  // block_draw.lock();
  system("cls");

  if (GlobalVars::isGameOver) {
    std::cout << "Game Oveeeerrrrr press r to restart" << std::endl;
    return;
  }
  std::string res_map_str;
  std::list<std::string> res_map;
  auto score_snake = list_snakes.begin();
  auto score_snake_end = list_snakes.end();
  char fill_top = '$';
  char fill_char = '$';

  for (int j = 0; j != my_indent.top; ++j) {
    res_map_str = "";

    for (int i = 0; i != my_indent.left - 1; ++i) {
      res_map_str += fill_char;
    }
    res_map_str += '$';

    for (short cur_col = 0; cur_col != GlobalVars::x_size;
         ++cur_col) {
      res_map_str += fill_top;
    }
    res_map_str += '$';

    for (int i = 1; i != my_indent.right; ++i) {
      res_map_str += fill_char;
    }
    std::string str_score =
     "\speed: " + std::to_string(GlobalVars::speed_time);
    res_map_str += str_score;
    //++score_snake;
    res_map.push_back(res_map_str);
  }

  // карта

  for (short cur_row = 0; cur_row != GlobalVars::y_size; ++cur_row) {
    res_map_str = "";

    for (int i = 0; i != my_indent.left - 1; ++i) {
      res_map_str += fill_char;
    }
    res_map_str += '$';

    for (short cur_col = 0; cur_col != GlobalVars::x_size;
         ++cur_col) {
      res_map_str +=
       this->cur_map_model->GetModelIndex(cur_col, cur_row).data;
    }
    res_map_str += '$';

    for (int i = 1; i != my_indent.right; i++) {
      res_map_str += fill_char;
    }

    if (score_snake != score_snake_end) {
      char ch =
       (*score_snake)->GetModel()->GetModelSegment(0).data.data;
      std::string str_score = "\tscore ";
      str_score +=
       ch; //+
           //((*score_snake)->GetModel()->GetModelSegment(0).data.data)
      str_score += " : ";
      str_score += std::to_string((*score_snake)->GetScore());
      res_map_str += str_score;
      ++score_snake;
    }
    res_map.push_back(res_map_str);
  }
  // indent bot

  for (int j = 0; j != my_indent.bot; j++) {
    res_map_str = "";

    for (int i = 0; i != my_indent.left - 1; i++) {
      res_map_str += fill_char;
    }
    res_map_str += '$';

    for (short cur_col = 0; cur_col != GlobalVars::x_size;
         ++cur_col) {
      res_map_str += '$';
    }
    res_map_str += '$';

    for (int i = 1; i != my_indent.right; i++) {
      res_map_str += fill_char;
    }
    res_map.push_back(res_map_str);
  }

  // auto smth_model=smth_snake->GetModel();

  // auto x_size=smth_model->GetXSize();
  std::list<std::string>::iterator smth_row = res_map.begin();
  std::list<std::string>::iterator smth_row_end = res_map.end();
  // auto

  for (short i = 0; i != my_indent.top; ++i, ++smth_row)
    ;

  // draw snake
  auto smth_snake = list_snakes.begin();
  auto smth_snake_end = list_snakes.end();

  while (smth_snake != smth_snake_end) {
    draw_snake(*smth_snake, res_map);
    ++smth_snake;
  }
  // вывод
  smth_row = res_map.begin();
  smth_row_end = res_map.end();

  if (GlobalVars::isGameOver) {
    smth_snake = list_snakes.begin();

    while (smth_snake != smth_snake_end) {
      if ((*smth_snake)->isLife()) {
        std::cout
         << "«мейка "
         << (*smth_snake)->GetModel()->GetModelSegment(0).data
         << " победила" << std::endl;
      }
      ++smth_snake;
    }
  }

  while (smth_row != smth_row_end) {
    std::cout << *smth_row << std::endl;
    ++smth_row;
  }
}
