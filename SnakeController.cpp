#include "SnakeController.h"

SnakeModel::SnakeModel() {
  cur_orentation = top;
  map = 0;
}

void SnakeModel::Move() {
  bool is_next_empty = false;
  SnakeSegment head = *snake_body.begin();
  char smth_elm = false;
  new_pos = head.cur_pos;
  switch (cur_orentation) {
  case SnakeModel::bot:
    --new_pos.cord_y;
    smth_elm = map->GetModelIndex(new_pos).data;

    if (smth_elm == '?') {
      new_pos.cord_y = GlobalVars::y_size - 1;
      smth_elm = map->GetModelIndex(new_pos).data;
    }

    is_next_empty |= check_empty(smth_elm);
    break;
  case SnakeModel::left:
    --new_pos.cord_x;
    smth_elm = map->GetModelIndex(new_pos).data;

    if (smth_elm == '?') {
      new_pos.cord_x = GlobalVars::x_size - 1;
      smth_elm = map->GetModelIndex(new_pos).data;
    }
    
    is_next_empty |= check_empty(smth_elm);
    break;
  case SnakeModel::top:
    ++new_pos.cord_y;
    smth_elm = map->GetModelIndex(new_pos).data;

    if (smth_elm == '?') {
      new_pos.cord_y = 0;
      smth_elm = map->GetModelIndex(new_pos).data;
    }
    
    is_next_empty |= check_empty(smth_elm);
    break;
  case SnakeModel::right:
    ++new_pos.cord_x;
    smth_elm = map->GetModelIndex(new_pos).data;

    if (smth_elm == '?') {
      new_pos.cord_x = 0;
      smth_elm = map->GetModelIndex(new_pos).data;
    }
    
    is_next_empty |= check_empty(smth_elm);
    break;
  }

  if (is_next_empty) {
    all_move();
  } else {
    GlobalVars::is_game_over = true;
  }
}

void SnakeModel::SetMapModel(AbstractModel *smth_model) {
  this->map = smth_model;
}

bool SnakeModel::check_empty(const char &elm) {
  auto ret_val = (GlobalVars::check_empty(elm));
  is_eat = (elm == GlobalVars::eat);
  return ret_val;
}

void SnakeModel::all_move() {
  SnakeModel::SnakeSegment last = snake_body.back();
  last.cur_pos = new_pos;
  snake_body.push_front(last);

  if (is_eat) {
    ++score;

    if (score > GlobalVars::score) {
      GlobalVars::score = score;

      if (GlobalVars::score % 2 == 0) {
        GlobalVars::time_of_update_speed -= 100;
      }
    }
    
    is_eat = false;
  } else {
    snake_body.pop_back();
  }
}

SnakeController::SnakeController() {
  model = new SnakeModel();
  SetStartPos();
}

void SnakeController::SetMap(AbstractModel *smth_model) {
  model->SetMapModel(smth_model);
}
void SnakeController::SetBodyChar(const char &ch) {
  model->SetModelIndex(ch, 0, 0);
}
void SnakeController::SetStartPos() {
  model->SetModelSize(1, 0);
  model->SetModelIndex('@', 0, 0);
  pos
   start_pos; // = { GlobalVars::x_size / 2, GlobalVars::y_size / 2 };
  start_pos.cord_x = GlobalVars::x_size / 2;
  start_pos.cord_y = GlobalVars::y_size / 2;
  model->SetPosition(0, start_pos);
}
void SnakeController::SetStartPos(int cord_x, int cord_y) {
  pos start_pos;
  start_pos.cord_x = cord_x;
  start_pos.cord_y = cord_y;
  model->SetPosition(0, start_pos);
}

void SnakeController::SetNewOrentation(
 const SnakeModel::orentation &smth_or) {
  if (model->GetXSize() != 1) {
    if ((smth_or & 0xe) == (model->cur_orentation & 0xe)) {
      if ((smth_or & 0x1) != (model->cur_orentation & 0x1)) {
        return;
      }
    }
  }

  new_oren = smth_or;
  did_orientation_change = true;
  return;
}

void SnakeController::Move() {
  if (did_orientation_change) {
    model->cur_orentation = new_oren;
  }

  model->Move();
}
