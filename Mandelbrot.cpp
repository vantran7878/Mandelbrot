#include <iostream>
#include <iomanip>
#include <cstdint>
#include <complex>
#include "raylib-5.0_linux_amd64/include/raylib.h"
#include <deque>
#include <chrono>
#include "Render.h"

using namespace std::complex_literals;


const Point START_POINT = {-2.0, -2.0};
const Point END_POINT = {2.0, 2.0};
const double STEP = 0.001;
const std::complex<double> c_start = -0.8 + 0.156i;

std::complex<double> julia_equation(std::complex<double> seed, std::complex<double> c) {
  //equation: y = z^2 - 1
  std::complex<double> result = std::pow(seed, 2);
  result += c;
  return result;
}

bool check_to_draw(std::complex<double> seed, uint32_t test_time) {
  uint32_t run_time = 0;
  std::complex<double> test_result = julia_equation(seed, seed);

  while(run_time++ < test_time) {
    if (abs(test_result) >=2) {
      run_time = 1;
      break;
    }
    test_result = julia_equation(test_result, seed);
  }

  if (run_time >= test_time) {
    return true;
  }
  return false;
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
  // Code to benchmark
  auto start = std::chrono::high_resolution_clock::now();
  std::deque<Point> julia_set = get_julia_set();
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration = end - start;
  
  std::cout << std::setprecision(8) << "\nCalc julia_set: " << duration.count() << '\n';
  
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

