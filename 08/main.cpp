#include <common.hpp>

int main(int argc, char** argv) {
  auto [str, day, part] = aoc_init(argc, argv);
  std::string::const_iterator curr_it = str.begin();

  int answer = 0;

  std::map<std::pair<int, int>, int> grid;

  std::string line;
  int x_max = 0, y_max = 0;
  while ((line = parse_until(curr_it, str.end(), "\n")) != "") {
    curr_it++;

    x_max = 0;
    for (char c : line) {
      grid.emplace(std::make_pair(x_max, y_max), c - '0');
      ++x_max;
    }
    ++y_max;
  }

  std::map<std::pair<int, int>, bool> visible;
  for (int x = 0; x < x_max; x++)
    for (int y = 0; y < y_max; y++)
      visible.emplace(std::make_pair(x, y), false);

  for (auto [p, d] : grid) {
    auto [x, y] = p;
    int score = 1;

    auto count = [&, &x = x, &y = y, &d = d](int x_dir, int y_dir) {
      int prev = d;
      int c = x;
      int r = y;
      int n = 0;
      while (true) {
        if (c == 0 || c == x_max - 1 || r == 0 || r == y_max - 1) {
          visible.at(std::make_pair(x, y)) = true;
          break;
        }
        c += x_dir;
        r += y_dir;
        ++n;
        int a = grid.at(std::make_pair(c, r));
        if (a >= d) break;
        prev = a;
      }
      score *= n;
    };

    count(1, 0);
    count(-1, 0);
    count(0, 1);
    count(0, -1);

    if (part == 2 && score > answer)
      answer = score;
  }

  if (part == 1)
    answer = std::accumulate(visible.begin(), visible.end(), 0, [](int acc, auto& p) {
      return acc + p.second;
    });

  fmt::print("{}\n", answer);

  return 0;
}