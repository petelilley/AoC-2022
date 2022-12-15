#include <common.hpp>

int main(int argc, char** argv) {
  auto [str, day, part] = aoc_init(argc, argv);
  std::string::const_iterator curr_it = str.begin();

  int answer = 0;

  std::map<std::pair<int, int>, bool> rocks;
  int xmin = -1, xmax = -1, ymin = -1, ymax = -1;
  while (curr_it != str.end()) {
    int x0 = -1, y0 = -1;
    while (true) {
      int x = parse_double(curr_it, str.end());
      curr_it++;
      int y = parse_double(curr_it, str.end());

      if (xmin == -1) {
        xmin = xmax = x;
        ymin = ymax = y;
      }
      if (x < xmin) xmin = x;
      if (x > xmax) xmax = x;
      if (y < ymin) ymin = y;
      if (y > ymax) ymax = y;

      if (x0 != -1 && y0 != -1) {
        rocks[{x0, y0}] = true;
        rocks[{x, y}] = true;

        int xdir = x - x0;
        int ydir = y - y0;
            
        if (xdir) xdir = xdir / std::abs(xdir);
        if (ydir) ydir = ydir / std::abs(ydir);

        while (true) {
          rocks[{x0, y0}] = true;
          if (x0 == x && y0 == y) break;
          x0 += xdir;
          y0 += ydir;
        }
      }
      x0 = x;
      y0 = y;

      if (*curr_it == ' ')
        curr_it += 4;
      else if (*curr_it == '\n') {
        ++curr_it;
        break;
      }
    }
  }

  if (part == 2)
    for (int x = xmin/2; x <= xmax*2; ++x)
      rocks[{x, ymax + 2}] = true;

  bool gone = false;
  int x = -1, y = -1;
  while (!gone) {
    int x = 500, y = 0;
    while (true) {
      if (y+1 > ymax && part != 2) {
        gone = true;
        break;
      }
      if (rocks[{x, y+1}]) {
        if (!rocks[{x-1, y+1}])
          x--;
        else if (!rocks[{x+1, y+1}])
          x++;
        else {
          rocks[{x, y}] = true;
          break;
        }
      }
      ++y;
    }
    if (!gone) answer++;
    if (x == 500 && y == 0) break;
  }

  fmt::print("{}\n", answer);

  return 0;
}