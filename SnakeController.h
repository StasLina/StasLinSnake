#pragma once
#include "GlobalVars.h"
class SnakeModel : public AbstractModel {
public:
  SnakeModel();
  enum orentation {
    bot,
    top,
    left,
    right
  };
  orentation cur_orentation;
  struct SnakeSegment {
    SnakeSegment(){};
    SnakeSegment(const ModelIndex &i, const pos &p) {
      this->data = i;
      this->cur_pos = p;
    }
    ModelIndex data;
    pos cur_pos;
  };

  void Move();
  void SetMapModel(AbstractModel *smth_model);
  const ModelIndex &GetModelIndex(short const &pos_x,
                                  const short &) override {
    auto smth_seg = body_snake.begin();

    for (short i = 0; i != pos_x; ++i, ++smth_seg)
      ;
    return smth_seg->data;
  };
  void SetModelIndex(const ModelIndex &smth_index, const short &pos_x,
                     const short &) override {
    auto smth_seg = body_snake.begin();

    for (short i = 0; i != pos_x; ++i, ++smth_seg)
      ;
    smth_seg->data = smth_index;
  };
  unsigned short GetXSize() override { return body_snake.size(); }
  void SetModelSize(unsigned short x, unsigned short) override {
    body_snake.resize(x);
  };
  void SetPosition(const short &pos_x, const pos &smth_pos) {
    auto smth_seg = body_snake.begin();

    for (short i = 0; i != pos_x; ++i, ++smth_seg)
      ;
    smth_seg->cur_pos = smth_pos;
  };
  const SnakeSegment &GetModelSegment(const short &pos_x) {
    auto smth_seg = body_snake.begin();

    for (short i = 0; i != pos_x; ++i, ++smth_seg)
      ;
    return *smth_seg;
  }
  size_t GetScore() { return score; }

private:
  std::list<SnakeSegment> body_snake;
  AbstractModel *map;
  bool is_eat = false;
  pos new_pos;
  size_t score = 0;

  bool proverka_empty(const char &elm);

  void all_move();
};

class SnakeController {
public:
  SnakeController();
  void SetMap(AbstractModel *smth_model);
  void SetBodyChar(const char &ch);
  void SetStartPos();
  void SetStartPos(int x, int y);
  void SetNewOrentation(const SnakeModel::orentation &smth_or);
  void Move();
  size_t GetScore() { return model->GetScore(); };
  SnakeModel *GetModel() { return model; };
  bool isLife() { return !snake_die; }
  void SetDie() { snake_die = true; }

private:
  SnakeModel *model;
  SnakeModel::orentation new_oren;
  bool orent_changed;
  int snake_model_lenght = 1;
  bool snake_die = false;
};
