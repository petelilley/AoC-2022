#include <common.hpp>

int main(int argc, char** argv) {
  auto [str, day, part] = aoc_init(argc, argv);
  std::string::const_iterator curr_it = str.begin();

  int answer = 0;
  int cycle = 1, x = 1;
  std::map<std::pair<int, int>, bool> crt;

  auto update_sig_str = [&]() {
    if ((cycle - 20) % 40 == 0)
      answer += cycle * x;
  };

  auto update_crt = [&]() {
    int c = (cycle - 1) % 40;
    if (c >= x - 1 && c <= x + 1)
      crt[std::make_pair(c, cycle / 40)] = true;
  };

  auto update_fn = [&, &part = part]() {
    if (part == 1) update_sig_str();
    else if (part == 2) update_crt();
  };

  while (curr_it != str.end()) {
    if (*curr_it == 'n') {
      curr_it += 5;
      update_fn();
      cycle++;
    }
    else if (*curr_it == 'a') {
      curr_it += 5;
      int n = parse_double(curr_it, str.end());
      curr_it++;
      update_fn();
      cycle++;
      update_fn();
      cycle++;
      x += n;
    }
  }

  if (part == 1)
    fmt::print("{}\n", answer);
  else if (part == 2)
    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 40; j++) {
        fmt::print("{} ", crt[std::make_pair(j, i)] ? '#' : ' ');
      }
      fmt::print("\n");
    }

  return 0;
}
