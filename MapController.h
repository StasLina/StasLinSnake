#pragma once
#include "SnakeController.h"

#include <conio.h>
#include <thread>
class MapModel : public StandartModel {
public:
  void SetShape(const std::string &str) {
    auto smth_elm = str.begin();
    auto smth_elm_end = str.end();
    int cur_row = 0;
    int cur_col = 0;
    int max_col = 0;

    while (smth_elm != smth_elm_end) {
      if (*smth_elm == '\n') {
        if (max_col < cur_col) {
          cur_col = max_col;
        }
        ++cur_row;
        cur_col = 0;
      } else {
        // SetModelIndex(*smth_elm, cur_col, cur_row);
      }
      ++cur_col;
      ++smth_elm;
    }
    GlobalVars::x_size = ++max_col;
    GlobalVars::y_size = ++cur_row;
    SetModelSize(GlobalVars::x_size, GlobalVars::y_size);
    cur_col = 0;
    cur_row = 0;

    while (smth_elm != smth_elm_end) {
      if (*smth_elm == '\n') {
        if (max_col < cur_col) {
          cur_col = max_col;
        }
        ++cur_row;
        cur_col = 0;
      } else {
        SetModelIndex(*smth_elm, cur_col, cur_row);
      }
      ++cur_col;
      ++smth_elm;
    }
  }
};
class MapController {
public:
  MapController() {
    this->cur_map_model = new MapModel();
    cur_map_model->SetModelSize(GlobalVars::x_size,
                                GlobalVars::y_size);
  }
  ~MapController() {
    if (cur_map_model) {
      delete cur_map_model;
    }
  }
  void SetMapModel(MapModel *smth_model) {
    this->cur_map_model = smth_model;
  }
  void Move();
  void addEat();
  void Draw();
  void Run() {
    addEat();
    addEat();
    std::thread th(&MapController::time_move, this);
    th.detach();
    SnakeController *smth_snake = 0, *smth_snake2 = 0;
    auto temp = list_snakes.begin();
    // smth_snake = *temp;
    smth_snake2 = *temp++;
    smth_snake = *temp++;
    char ch;

    while (GlobalVars::is_game_over == false) {
      ch = _getch();
      switch (ch) {
      case 'w':
        smth_snake->SetNewOrentation(SnakeModel::orentation::bot);
        break;
      case 'a':
        smth_snake->SetNewOrentation(SnakeModel::orentation::left);
        break;
      case 's':
        smth_snake->SetNewOrentation(SnakeModel::orentation::top);
        break;
      case 'd':
        smth_snake->SetNewOrentation(SnakeModel::orentation::right);
        break;
      case -32: {
        switch (_getch()) {
        case 72:
          smth_snake2->SetNewOrentation(SnakeModel::orentation::bot);
          break;
        case 75:
          smth_snake2->SetNewOrentation(SnakeModel::orentation::left);
          break;
        case 80:
          smth_snake2->SetNewOrentation(SnakeModel::orentation::top);
          break;
        case 77:
          smth_snake2->SetNewOrentation(
           SnakeModel::orentation::right);
          break;
        }
        break;
      }
      default:

        break;
      }
    }
  }
  void AddSnake() {
    auto smth_snake = new SnakeController();
    list_snakes.push_back(smth_snake);
    smth_snake->SetStartPos(GlobalVars::x_size - 1,
                            GlobalVars::y_size - 1);
    smth_snake->SetBodyChar('@');
    smth_snake->SetMap(this->cur_map_model);
    auto smth_snake2 = new SnakeController();
    list_snakes.push_back(smth_snake2);
    smth_snake2->SetStartPos(0, 0);
    smth_snake2->SetBodyChar('$');
    smth_snake2->SetMap(this->cur_map_model);
  }

private:
  void time_move() {
    while (GlobalVars::is_game_over == false) {
      this->Move();
      Draw();
      GlobalVars::is_eated = false;
      std::this_thread::sleep_for(
       std::chrono::milliseconds(GlobalVars::time_of_update_speed));
    }
  }

private:
  void draw_snake(SnakeController *smth_cnake,
                  std::list<std::string> &res_map) {
    auto smth_model = smth_cnake->GetModel();
    auto x_size = smth_model->GetXSize();
    std::list<std::string>::iterator smth_row = res_map.begin();
    std::list<std::string>::iterator smth_row_end = res_map.end();
    // auto

    for (short cur_row_indent = 0; cur_row_indent != my_indent.top; ++cur_row_indent, ++smth_row)
      ;
    unsigned short cur_row_indent = 0;
    auto segment = smth_model->GetModelSegment(cur_row_indent);
    short cur_x = 0;
    short cur_y = 0;
    auto nedded_row = smth_row;

    while (cur_y != segment.cur_pos.y) {
      ++nedded_row;
      ++cur_y;
    }
    auto needed_char = nedded_row->begin();

    while (cur_x != segment.cur_pos.x) {
      ++cur_x;
      ++needed_char;
    }
    cur_x = 0;

    while (cur_x != my_indent.left) {
      ++cur_x;
      ++needed_char;
    }

    if (GlobalVars::proverka_empty(*needed_char, false) == false) {
      GlobalVars::is_game_over = true;
      *needed_char = 'G';
      smth_cnake->SetDie();
    } else {
      *needed_char = '#';
    }

    for (cur_row_indent = 1; cur_row_indent != x_size; ++cur_row_indent) {
      auto segment = smth_model->GetModelSegment(cur_row_indent);
      short cur_x = 0;
      short cur_y = 0;
      auto nedded_row = smth_row;

      while (cur_y != segment.cur_pos.y) {
        ++nedded_row;
        ++cur_y;
      }
      auto needed_char = nedded_row->begin();

      while (cur_x != segment.cur_pos.x) {
        ++cur_x;
        ++needed_char;
      }
      cur_x = 0;

      while (cur_x != my_indent.left) {
        ++cur_x;
        ++needed_char;
      }

      if (GlobalVars::proverka_empty(*needed_char, false) == false) {
        GlobalVars::is_game_over = true;
        smth_cnake->SetDie();
        *needed_char = 'G';
      } else {
        *needed_char = segment.data.data;
      }
    }
  }

  MapModel *cur_map_model = 0;
  std::list<SnakeController *> list_snakes;
  // SnakeController* smth_snake = 0,*smth_snake2=0;

  struct indent {
    short left = 1, right = 1, bot = 1, top = 1;
  };
  indent my_indent;
};
