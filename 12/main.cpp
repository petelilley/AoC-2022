#include <common.hpp>

int main(int argc, char** argv) {
  auto [str, day, part] = aoc_init(argc, argv);
  std::string::const_iterator curr_it = str.begin();

  std::map<std::pair<int, int>, char> grid;

  std::pair<int, int> start, end;
  int x = 0, y = 0;
  std::string line;
  while ((line = parse_until(curr_it, str.end(), "\n")) != "") {
    curr_it++;

    x = 0;
    for (char c : line) {
      std::pair<int, int> p = std::make_pair(x, y);
      if (c == 'S') {
        start = p;
        c = 'a';
      }
      if (c == 'E') {
        end = p;
        c = 'z';
      }
      grid.emplace(p, c);
      ++x;
    }
    ++y;
  }

  int answer = -1;

  std::set<std::pair<int, int>> v { start };
  std::deque<std::pair<int, std::pair<int, int>>> q { std::make_pair(0, part == 1 ? start : end) };

  constexpr static std::array<std::pair<int, int>, 4> dirs { { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } } };

  while (true) {
    auto [d, p] = q.front();
    q.pop_front();
    
    for (auto dir : dirs) {
      std::pair<int, int> next = std::make_pair(p.first + dir.first, p.second + dir.second);

      if (next.first < 0 || next.second < 0 || next.first >= x || next.second >= y) continue;
      if (v.find(next) != v.end()) continue;

      int dc = grid[next] - grid[p];
      if (part == 1 && dc > 1 || part == 2 && dc < -1) continue;

      if (part == 1 && next == end || part == 2 && grid[next] == 'a') {
        answer = d + 1;
        goto end;
      }

      v.insert(next);
      q.push_back(std::make_pair(d + 1, next));
    }
  }

end:
  fmt::print("{}\n", answer);

  return 0;
}