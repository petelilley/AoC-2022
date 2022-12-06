#include <common.hpp>

int main(int argc, char** argv) {
  auto [str, day, part] = aoc_init(argc, argv);
  std::string::const_iterator curr_it = str.begin();

  std::string line = parse_until(curr_it, str.end(), "\n");

  int iter = part == 1 ? 4 : 14;

  for (int i = 0; i < line.size(); i += 1) {
    std::string recents = line.substr(i, iter);

    for (int j = 0; j < recents.length() - 1; j++) {
      for (int k = j + 1; k < recents.length(); k++) {
        if (recents[j] == recents[k]) {
          goto bad;
        }
      }
    }

    fmt::print("{}\n", i + iter);
    break;

bad:
    continue;
  }

  return 0;
}