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
  short temp_offset = 0;

  while (temp_offset != pos_y) {
    ++row;
    ++temp_offset;
  }
  temp_offset = 0;
  auto col = row->begin();

  while (temp_offset != pos_x) {
    ++col;
    ++temp_offset;
  }
  return *col;
}
