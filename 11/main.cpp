#include <common.hpp>

struct Monkey {
  std::vector<uint64_t> items;
  int op, val, div, mt, mf;
  uint64_t insp = 0;
};

int main(int argc, char** argv) {
  auto [str, day, part] = aoc_init(argc, argv);
  std::string::const_iterator curr_it = str.begin();

  std::vector<Monkey> monkeys;

  while (curr_it-1 != str.end()) {
    // Monkey number
    curr_it += 7;
    int monkey = parse_double(curr_it, str.end());
    curr_it += 18;
    // Items
    std::vector<uint64_t> items;
    do {
      curr_it += 2;
      items.push_back(parse_double(curr_it, str.end()));
    } while (*curr_it != '\n');
    curr_it += 24;
    // Operator
    char op = *curr_it;
    curr_it += 2;
    // Operand
    int val = -1;
    if (*curr_it == 'o')
      curr_it += 3;
    else
      val = parse_double(curr_it, str.end());
    curr_it += 22;
    // Divisor
    int div = parse_double(curr_it, str.end());
    curr_it += 30;
    // True monkey
    int mt = parse_double(curr_it, str.end());
    curr_it += 31;
    // False monkey
    int mf = parse_double(curr_it, str.end());
    curr_it += 2;

    monkeys.push_back({items, op, val, div, mt, mf});
  }

  int r = 1;
  for (auto& m : monkeys) r *= m.div;

  for (int i = 0; i < (part == 1 ? 20 : 10000); i++) {
    for (auto& m : monkeys) {
      for (int j = m.items.size() - 1; j >= 0; j--) {
        uint64_t worry = m.items.back();
        m.items.pop_back();

        auto val = m.val == -1 ? worry : m.val;
        if (m.op == '*')
          worry *= val;
        else
          worry += val;

        if (part == 1)
          worry /= 3;
        else
          worry %= r;

        monkeys.at(worry % m.div == 0 ? m.mt : m.mf).items.push_back(worry);
        m.insp++;
      }
    }
  }

  std::sort(monkeys.begin(), monkeys.end(), [](auto& a, auto& b) { return a.insp > b.insp; });
  fmt::print("{}\n", monkeys.at(0).insp * monkeys.at(1).insp);

  return 0;
}