#include "Render.h"

void draw_point_pixel(Point point) {
  Point mid_point = {RESOLUTION.x / 2, RESOLUTION.y / 2};
  Point draw_point = {SCALE * point.x, SCALE * point.y};
  draw_point.x += mid_point.x;
  draw_point.y = mid_point.y - draw_point.y;
  DrawPixel(draw_point.x, draw_point.y, BLACK);
}
