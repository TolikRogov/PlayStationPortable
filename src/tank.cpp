#include "Tank.hpp"

void Tank::draw() {
  // background restoration didn't give significant performance boost, so I decided to comment it out for now.
  // just uncomment the corresponding lines in this function and in the constructor of Entity class
  // if (old_x != pos_x || old_y != pos_y) {
  //   restore_background(tft_);
  //   save_background(tft_);  
  // }
  
  old_x = pos_x;
  old_y = pos_y;
  
  tft_.setSwapBytes(true); 
  const uint16_t* current_sprite = skins[tank_type][orientation];
  tft_.pushImage(pos_x, pos_y, width, height, current_sprite, TRANSPARENT_COLOR);
}

void Tank::update_orientation(int dx, int dy) {
  if (dy > 0) orientation = DIR_DOWN;
  else if (dy < 0) orientation = DIR_UP;
  else if (dx < 0) orientation = DIR_LEFT;
  else if (dx > 0) orientation = DIR_RIGHT;
}