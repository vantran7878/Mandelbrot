#include "raylib-5.0_linux_amd64/include/raylib.h"
#include <complex>

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

const Point RESOLUTION = {1280, 720};
const double SCALE = 300;

void draw_point_pixel(Point point);
