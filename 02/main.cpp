#include <common.hpp>

int main(int argc, char** argv) {
  auto [str, day, part] = aoc_init(argc, argv);
  std::string::const_iterator curr_it = str.begin();

  int answer = 0;

  while (curr_it != str.end()) {
    char s0 = *curr_it - 'A';
    curr_it += 2;
    char s1 = *curr_it - 'X';
    curr_it += 2;

    if (part == 2) {
      s1 = ((s0 + 2 + s1) % 3);
    }

    if (s0 == s1) { // tie
      answer += 3;
    }
    else if (s1 == (s0 + 1) % 3) { // win
      answer += 6;
    }

    answer += s1 + 1;
  }

  fmt::print("{}\n", answer);

  return 0;
}