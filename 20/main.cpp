#include <common.hpp>

int main(int argc, char** argv) {
  auto [str, day, part] = aoc_init(argc, argv);
  std::string::const_iterator curr_it = str.begin();

  std::vector<std::pair<int64_t, int64_t>> numbers;
  int l = 0;
  while (curr_it != str.end()) {
    int64_t n = parse_double(curr_it, str.end()) * (part == 2 ? 811589153 : 1);
    ++curr_it;
    numbers.emplace_back(n, l++);
  }

  auto get_pos = [](int64_t curr, int64_t n, int64_t sz) -> int64_t {
    curr += n;
    while (curr <= 0) curr += sz - 1;
    curr %= sz-1;
    return curr;
  };

  int64_t c = 0;

restart:
  int64_t n = 0;
  while (n < numbers.size()) {
    decltype(numbers)::iterator it = std::find_if(numbers.begin(), numbers.end(), [n](auto p) { return p.second == n; });

    int64_t x = it->first;
    int64_t p = get_pos(it - numbers.begin(), x, numbers.size());
    
    numbers.erase(it);
    numbers.insert(numbers.begin() + p, std::make_pair(x, n++));
  }

  if (part == 2 && c != 9) {
    c++;
    goto restart;
  }

  int64_t pos = std::find_if(numbers.begin(), numbers.end(), [](auto p) { return p.first == 0ll; }) - numbers.begin();

  int64_t answer = 0;
  for (int64_t i = 0; i < 3; ++i) {
    pos = get_pos(pos, 1000, numbers.size());
    answer += numbers[pos].first;
  }

  fmt::print("{}\n", answer);

  return 0;
}