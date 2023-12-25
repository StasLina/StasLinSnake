#include "GlobalVars.h"

const ModelIndex &StandartModel::GetModelIndex(short const &pos_x,
                                               const short &pos_y) {

  if (pos_x < 0 || pos_y < 0) {
    return ModelIndex('?');
  }

  if (pos_x >= GlobalVars::x_size || pos_y >= GlobalVars::y_size) {
    return ModelIndex('?');
  }
  auto row = data.begin();
  short n = 0;

  while (n != pos_y) {
    ++row;
    ++n;
  }
  n = 0;
  auto col = row->begin();

  while (n != pos_x) {
    ++col;
    ++n;
  }
  return *col;
}
