#include <common.hpp>

struct X {
  bool is_list = true;
  std::vector<X*> list;
  double num;
};

int main(int argc, char** argv) {
  auto [str, day, part] = aoc_init(argc, argv);
  std::string::const_iterator curr_it = str.begin();

  X* root = new X{true, {}, 0};
  while (curr_it != str.end()) {
    std::function<X*()> parse_list = [&, &str = str]() -> X* {
      X* x = new X;
      x->is_list = true;

      ++curr_it;
      while (*curr_it != ']') {
        if (*curr_it == '[')
          x->list.push_back(parse_list());
        else
          x->list.push_back(new X{false, {}, parse_double(curr_it, str.end())});
        if (*curr_it == ',') ++curr_it;
      }
      ++curr_it;
      return x;
    };

    if (*curr_it == '[')
      root->list.push_back(parse_list());
    ++curr_it;
  }

  std::function<int(X*, X*)> compare = [&](X* lhs, X* rhs) -> int {
    if (lhs->is_list && rhs->is_list) {
      int min = std::min(lhs->list.size(), rhs->list.size());
      for (int i = 0; i < min; ++i) {
        if (lhs->list.at(i) == rhs->list.at(i)) continue;
        int res = compare(lhs->list.at(i), rhs->list.at(i));
        if (res != 0) return res;
      }
      if (min == lhs->list.size() && min < rhs->list.size()) return -1;
      if (min == rhs->list.size() && min < lhs->list.size()) return 1;
      return 0;
    }
    else if (!lhs->is_list && !rhs->is_list) {
      return lhs->num == rhs->num ? 0 : lhs->num < rhs->num ? -1 : 1;
    }
    else if (!lhs->is_list) {
      X new_lhs = {true, {lhs}, 0};
      return compare(&new_lhs, rhs);
    }
    else {
      X new_rhs = {true, {rhs}, 0};
      return compare(lhs, &new_rhs);
    }
    return 0;
  };

  int answer = 0;
  if (part == 1)
    for (int i = 0; i < root->list.size(); i += 2) {
      int res = compare(root->list.at(i), root->list.at(i + 1));
      if (res == -1) answer += (i / 2) + 1;
    }
  else if (part == 2) {
    X* x1 = new X{true, { new X{true, { new X{false, {}, 6} }, 0} }, 0},
     * x2 = new X{true, { new X{true, { new X{false, {}, 2} }, 0} }, 0};
    root->list.push_back(x1);
    root->list.push_back(x2);

    std::sort(root->list.begin(), root->list.end(), [&](X* lhs, X* rhs) -> bool {
      return compare(lhs, rhs) == -1;
    });

    answer = 1;
    for (auto it = root->list.begin(); it != root->list.end(); ++it)
      if (*it == x1 || *it == x2)
        answer *= (it - root->list.begin()) + 1;
  }

  fmt::print("{}\n", answer);

  std::function<void(X*)> cleanup = [&](X* x) -> void {
    if (x->is_list)
      for (auto it = x->list.begin(); it != x->list.end(); ++it)
        cleanup(*it);
    delete x;
  };
  cleanup(root);

  return 0;
}