#pragma once
#include <list>
#include <ostream>
#include <vector>
class pos {
public:
  pos(){};
  pos(const short &x1, const short &y1) {
    x = x1;
    y = y1;
  }
  short x = 0, y = 0;
};
class GlobalVars {
  // private:

public:
  static bool isEated;

public:
  static short x_size, y_size;
  static bool isGameOver;
  static const char eat;
  static long speed_time;
  static int score;
  static bool proverka_empty(const char &elm, bool set_eat = true) {
    switch (elm) {
    case ' ':
      return true;
    case '#':
      return false;
    case '*': {

      if (set_eat) {

        if (elm == GlobalVars::eat) {
          GlobalVars::isEated = true;
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
    return GetModelIndex(smth_pos.x, smth_pos.y);
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
  virtual void SetModelSize(unsigned short x, unsigned short y) {
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
    short 
 temp_offset = 0;

    while (
 temp_offset != pos_y) {
      ++row;
      ++
 temp_offset;
    }
    
 temp_offset = 0;
    auto col = row->begin();

    while (
 temp_offset != pos_x) {
      ++col;
      ++
 temp_offset;
    }
    *col = smth_index;
  };
  unsigned short GetXSize() override { return data.begin()->size(); }
  unsigned short GetYSize() override { return data.size(); }
  void SetModelSize(unsigned short x, unsigned short y) override {
    data.resize(y);
    auto row = data.begin();
    short 
 temp_offset = 0;

    while (
 temp_offset != y) {
      row->resize(x);
      ++row;
      ++
 temp_offset;
    }
  };

  std::list<std::vector<ModelIndex>> data;

private:
};
