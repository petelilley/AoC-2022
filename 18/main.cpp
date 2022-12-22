#include <common.hpp>

int main(int argc, char** argv) {
  auto [str, day, part] = aoc_init(argc, argv);
  std::string::const_iterator curr_it = str.begin();

  double answer = 0;

  std::set<std::tuple<int, int, int>> lava;
  while (curr_it != str.end()) {
    int x = parse_double(curr_it, str.end());
    ++curr_it;
    int y = parse_double(curr_it, str.end());
    ++curr_it;
    int z = parse_double(curr_it, str.end());
    ++curr_it;
    lava.insert({x, y, z});
  }

  std::map<std::tuple<int, int, int>, bool> saved;
  auto is_free = [&lava, &saved](int _x, int _y, int _z, int depth) -> bool {
    if (saved.count({_x, _y, _z})) return saved[{_x, _y, _z}];

    std::queue<std::tuple<int, int, int>> to_check {{{_x, _y, _z}}};
    std::set<std::tuple<int, int, int>> seen;

    while (!to_check.empty()) {
      auto [x, y, z] = to_check.front();
      to_check.pop();
      if (lava.count({x, y, z})) continue;
      if (seen.count({x, y, z})) continue;

      seen.insert({x, y, z});
      if (seen.size() >= depth) {
        for (auto& r : seen)
          saved[r] = true;
        return true;
      }

      for (int i = -1; i <= 1; ++i) {
        to_check.push({x + i, y, z});
        to_check.push({x, y + i, z});
        to_check.push({x, y, z + i});
      }
    }
    for (auto& r : seen)
      saved[r] = false;
    return false;
  };

  for (auto& [x, y, z] : lava) {
    int depth = part == 1 ? 1 : 3000;

    for (int i = -1; i <= 1; ++i) {
      if (is_free(x + i, y, z, depth)) answer++;
      if (is_free(x, y + i, z, depth)) answer++;
      if (is_free(x, y, z + i, depth)) answer++;
    }
  }

  fmt::print("{}\n", answer);

  return 0;
}