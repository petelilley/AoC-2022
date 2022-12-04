#include <common.hpp>

int main(int argc, char** argv) {
  auto [str, day, part] = aoc_init(argc, argv);
  std::string::const_iterator curr_it = str.begin();

  int answer = 0;

  while (curr_it != str.end()) {
    auto parse_num = [&]() -> int {
      int n = parse_double(curr_it, str.end());
      ++curr_it;
      return n;
    };

    int a = parse_num(),
        b = parse_num(),
        x = parse_num(),
        y = parse_num();

    if (b - a < y - x) {
      std::swap(a, x);
      std::swap(b, y);
    }

    if (part == 1) {
      if (a <= x && b >= y)
        answer++;
    }
    else if (part == 2) {
      if (x >= a && x <= b || y >= a && y <= b)
        answer++;
    }
  }

  fmt::print("{}\n", answer);

  return 0;
}