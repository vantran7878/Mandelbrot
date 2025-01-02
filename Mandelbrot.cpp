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
  std::complex<double> result = std::pow(seed, 2);
  result += c;
  return result;
}

Color pixel_to_draw(std::complex<double> seed, uint32_t max_iteration) {
  uint32_t iteration = 0;
  std::complex<double> test_result = julia_equation(seed, seed);

  while(iteration++ < max_iteration) {
    if (abs(test_result) >=2) {
      break;
    }
    test_result = julia_equation(test_result, seed);
  }

  unsigned char r = iteration % 256, g = iteration % 128, b = iteration % 64;
  return (iteration >= max_iteration) ? BLACK : Color {r, g, b, 0};
}


std::deque<ColorPoint> get_julia_set() {
  Point traverse = START_POINT;

  std::deque<ColorPoint> point_set;
  for (traverse.x = START_POINT.x; 
       traverse.x < END_POINT.x; 
       traverse.x += STEP) {

    for (traverse.y = START_POINT.y; 
         traverse.y < END_POINT.y; 
         traverse.y += STEP) {
       Color c = pixel_to_draw(std::complex<double>{traverse.x, traverse.y}, 100);
       point_set.emplace_back(ColorPoint{traverse, c}); 
    }
  }
  return point_set;
}

RenderTexture2D get_texture(std::deque<ColorPoint> point_set) {
  std::cout << "In function OK\n";
  RenderTexture2D texture = LoadRenderTexture(RESOLUTION.x, RESOLUTION.y);
  std::cout << "Load Render OK\n";
  BeginTextureMode(texture);
  ClearBackground(SKYBLUE);

  for (ColorPoint p : point_set) {
    Point point = p.cordinate;
    Color color = p.color;
    Point mid_point = {RESOLUTION.x / 2, RESOLUTION.y / 2};
    Point draw_point = {SCALE * point.x, SCALE * point.y};
    draw_point.x += mid_point.x;
    draw_point.y = mid_point.y - draw_point.y;
    DrawPixel(draw_point.x, draw_point.y, color);
  }

  std::cout << "Draw OK\n";

  EndTextureMode();
  return texture;
}

int main() {
  // Code to benchmark
  auto start = std::chrono::high_resolution_clock::now();
  std::deque<ColorPoint> fractal_set = get_julia_set();
  auto end = std::chrono::high_resolution_clock::now();


  std::chrono::duration<double> duration = end - start;
  
  std::cout << std::setprecision(8) << "\nCalc fractal set: " << duration.count() << '\n';
  
  InitWindow(1280, 720, "Mandelbrot");
  RenderTexture2D texture = get_texture(fractal_set);
  SetTargetFPS(60);

  while(!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexture(texture.texture, 0, 0, WHITE);

    EndDrawing();
  }
  CloseWindow();

  return 0;
}

