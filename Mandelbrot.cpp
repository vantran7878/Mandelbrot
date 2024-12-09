#include <cstdint>
#include <complex>
#include "raylib-5.0_linux_amd64/include/raylib.h"
#include <deque>

using namespace std::complex_literals;

struct Point {
  double x;
  double y;
  Point() {
    this->x = 0.0;
    this->y = 0.0;
  }
  Point(double x, double y) : x{x}, y{y} {
  }
  Point(std::complex<double> c_num)
  : x{c_num.real()},
    y{c_num.imag()} {
  }

  Point(const Point &other)
  : x{other.x},
    y{other.y} {
  }

  void from_complex(std::complex<double> c_num) {
    this->x = c_num.real();
    this->y = c_num.imag();
  }
};

const Point START_POINT = {-5.0, -5.0};
const Point END_POINT = {5.0, 5.0};
const Point RESOLUTION = {1280, 720};
const double STEP = 0.01;
const double SCALE = 300;
const std::complex<double> c = -0.8 + 0.156i;

using namespace std::complex_literals;

std::complex<double> julia_equation(std::complex<double> seed) {
  //equation: y = z^2 - 1
  std::complex<double> result = std::pow(seed, 2);
  result += c;
  return result;
}

bool check_to_draw(std::complex<double> seed, uint32_t test_time) {
  uint32_t run_time = 0;
  std::complex<double> test_result = julia_equation(seed);
  bool can_draw = false;

  while(run_time++ < test_time) {
    if (std::isnan(test_result.real()) || std::isnan(test_result.imag())) {
      run_time = 1;
      break;
    }
    if (std::isinf(test_result.real()) || std::isinf(test_result.imag())) {
      run_time = 1;
      break;
    }
    test_result = julia_equation(test_result);
  }

  if (run_time >= test_time) {
    return true;
  }
  return false;
}

void draw_point_pixel(Point point) {
  Point mid_point = {RESOLUTION.x / 2, RESOLUTION.y / 2};
  Point draw_point = {SCALE * point.x, SCALE * point.y};
  draw_point.x += mid_point.x;
  draw_point.y = mid_point.y - draw_point.y;
  //draw_point.x += mid_point.x;
  //draw_point.y += mid_point.y;
  DrawPixel(draw_point.x, draw_point.y, BLACK);
}

void draw_julia_set(std::deque<Point> point_set) {
  for (Point p : point_set) {
    draw_point_pixel(p);
  }
}

std::deque<Point> get_julia_set() {
  Point traverse_point = START_POINT;
  std::deque<Point> point_set;
  for (traverse_point.x = START_POINT.x; 
       traverse_point.x < END_POINT.x; 
       traverse_point.x += STEP) {

    for (traverse_point.y = START_POINT.y; 
         traverse_point.y < END_POINT.y; 
         traverse_point.y += STEP) {
      if (check_to_draw(std::complex<double>{traverse_point.x, traverse_point.y}, 100)) {
        point_set.push_back(traverse_point); 
      }
    }
  }

  return point_set;
}

int main() {
  std::deque<Point> julia_set = get_julia_set();
  InitWindow(1280, 720, "Mandelbrot");
  SetTargetFPS(60);

  while(!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    draw_julia_set(julia_set);
    EndDrawing();
  }
  CloseWindow();

  return 0;
}

