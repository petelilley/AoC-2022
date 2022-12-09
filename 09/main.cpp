#include <common.hpp>

int main(int argc, char** argv) {
  auto [str, day, part] = aoc_init(argc, argv);
  std::string::const_iterator curr_it = str.begin();

  int nknots = part == 2 ? 10 : 2;

  std::array<std::pair<int, int>, 10> knots;
  std::set<std::pair<int, int>> grid;
  grid.insert(knots[nknots - 1]);

  while (curr_it != str.end()) {
    char dir = *curr_it;
    curr_it += 2;
    int dist = parse_double(curr_it, str.end());
    ++curr_it;

    for (int i = 0; i < dist; i++) {
      switch (dir) {
        case 'U': knots[0].second++; break;
        case 'D': knots[0].second--; break;
        case 'R': knots[0].first++; break;
        case 'L': knots[0].first--; break;
      }

      for (int j = 1; j < nknots; j++) {
        const std::pair<int, int>& hpos = knots[j - 1];
        std::pair<int, int>& tpos = knots[j];

        int dx = hpos.first - tpos.first;
        int dy = hpos.second - tpos.second;
        if (std::abs(dx) > 1 || std::abs(dy) > 1) {
          int x = dx ? dx / std::abs(dx) : 0;
          int y = dy ? dy / std::abs(dy) : 0;

          tpos = std::make_pair(tpos.first + x, tpos.second + y);
          if (j == nknots - 1)
            grid.insert(tpos);
        }
      }
    }
  }

  fmt::print("{}\n", grid.size());

  return 0;
}