#pragma once
#include <list>
#include <ostream>
#include <vector>
class pos {
public:
  pos(){};
  pos(const short &x1, const short &y1) {
    cord_x = x1;
    cord_y = y1;
  }
  short cord_x = 0, cord_y = 0;
};
class GlobalVars {
  // private:

public:
  static bool is_eated;
  static short x_size, y_size;
  static bool is_game_over;
  static const char eat;
  static long time_of_update_speed;
  static int score;
  static bool check_empty(const char &elm, bool set_eat = true) {
    switch (elm) {
    case ' ':
      return true;
    case '#':
      return false;
    case '*': {
      if (set_eat) {
        if (elm == GlobalVars::eat) {
          GlobalVars::is_eated = true;
          return true;
        }
      }
      return true;
    } break;
    default:
      return false;
    }
  }
};

class ModelIndex {
public:
  ModelIndex(){};
  ModelIndex(const char ch) { data = ch; };
  char data = ' ';
  // pos position;
  friend std::ostream &operator<<(std::ostream &os,
                                  const ModelIndex &index) {
    os << index.data;
    return os;
  }
};
class AbstractModel {
public:
  const ModelIndex &GetModelIndex(const pos &smth_pos) {
    return GetModelIndex(smth_pos.cord_x, smth_pos.cord_y);
  }
  virtual const ModelIndex &GetModelIndex(short const &pos_x,
                                          const short &pos_y) {
    return ModelIndex();
  };
  virtual void SetModelIndex(const ModelIndex &smth_index,
                             const short &pox_x,
                             const short &pos_y){};
  virtual unsigned short GetXSize() { return 0; }
  virtual unsigned short GetYSize() { return 0; }
  virtual void SetModelSize(unsigned short cord_x, unsigned short cord_y) {
    return;
  };
};

class StandartModel : public AbstractModel {
public:
  const ModelIndex &GetModelIndex(short const &pos_x,
                                  const short &pos_y) override;
  ;
  void SetModelIndex(const ModelIndex &smth_index, const short &pos_x,
                     const short &pos_y) override {
    auto row = data.begin();
    short cur_offset = 0;

    while (cur_offset != pos_y) {
      ++row;
      ++cur_offset;
    }

    cur_offset = 0;
    auto col = row->begin();

    while (cur_offset != pos_x) {
      ++col;
      ++cur_offset;
    }
    *col = smth_index;
  };
  unsigned short GetXSize() override { return data.begin()->size(); }
  unsigned short GetYSize() override { return data.size(); }
  void SetModelSize(unsigned short cord_x, unsigned short cord_y) override {
    data.resize(cord_y);
    auto row = data.begin();
    short cur_offset = 0;

    while (cur_offset != cord_y) {
      row->resize(cord_x);
      ++row;
      ++cur_offset;
    }
  };

  std::list<std::vector<ModelIndex>> data;

private:
};
