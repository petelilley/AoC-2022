#include <common.hpp>

enum Type { NUMBER, EQUATION };

struct Equation {
  std::string lhs, rhs;
  char op;
};

struct Monkey {
  Type type;
  Equation eq;
  int64_t num;
};

int main(int argc, char** argv) {
  auto [str, day, part] = aoc_init(argc, argv);
  std::string::const_iterator curr_it = str.begin();

  std::map<std::string, Monkey> monkeys;

  while (curr_it != str.end()) {
    std::string name = parse_until(curr_it, str.end(), ":");
    curr_it += 2;
    Type type = EQUATION;
    int64_t num;
    Equation eq;

    if (std::isdigit(*curr_it)) {
      type = NUMBER;
      num = parse_double(curr_it, str.end());
    }
    else {
      eq.lhs = parse_until(curr_it, str.end(), " ");
      ++curr_it;
      eq.op = *curr_it;
      curr_it += 2;
      eq.rhs = parse_until(curr_it, str.end(), "\n");
    }

    ++curr_it;

    monkeys.emplace(name, Monkey{type, eq, num});
  }

  std::function<int64_t(const std::string&, int64_t)> eval_monkey = [&](const std::string& name, int64_t me) -> int64_t {
    if (name == "humn" && me >= 0)
      return me;

    auto& m = monkeys[name];
    auto& [type, eq, num] = m;
    if (type == NUMBER)
      return num;
    else {
      int64_t lhs = eval_monkey(eq.lhs, me);
      int64_t rhs = eval_monkey(eq.rhs, me);
      if (eq.op == '+')
        return lhs + rhs;
      else if (eq.op == '*')
        return lhs * rhs;
      else if (eq.op == '-')
        return lhs - rhs;
      else if (eq.op == '/')
        return lhs / rhs;
      else
        throw std::runtime_error("Unknown operator: " + std::string(1, eq.op));
    }
  };

  int64_t answer = 0;
  if (part == 1) {
    answer = eval_monkey("root", -1);
  }
  else if (part == 2) {
    std::string lhs = monkeys["root"].eq.lhs,
                rhs = monkeys["root"].eq.rhs;

    if (eval_monkey(rhs, 0) != eval_monkey(rhs, 1))
      std::swap(lhs, rhs);

    int64_t targ = eval_monkey(rhs, -1);
    int64_t low = 0, high = 4000000000000;
    while (true) {
      int64_t mid = (low + high) / 2LL;
      int64_t eval = eval_monkey(lhs, mid);
      if (eval == targ) {
        answer = mid;
        break;
      }
      else if (eval > targ)
        low = mid;
      else
        high = mid;
    }
  }

  fmt::print("{}\n", answer);

  return 0;
}