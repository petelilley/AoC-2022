#include <common.hpp>

int main(int argc, char** argv) {
  auto [str, day, part] = aoc_init(argc, argv);
  std::string::const_iterator curr_it = str.begin();

  auto to_base10 = [](std::string snafu) -> int64_t {
    int64_t num = 0, base = 1;
    const std::map<char, int64_t> b10_map { {'=', -2}, {'-', -1}, {'0', 0}, {'1', 1}, {'2', 2} };

    for (int64_t i = snafu.size() - 1; i >= 0; --i) {
      num += b10_map.at(snafu[i]) * base;
      base *= 5;
    }
    return num;
  };

  std::function<int64_t(int64_t)> max_value = [&](int64_t power) -> int64_t {
    if (power == 1) return 2;
    return power * 2 + max_value(power / 5);
  };

  std::function<std::string(int64_t, int64_t)> to_snafu = [&](int64_t base10, int64_t power) -> std::string {
    std::map<int64_t, char> snafu_map{ {-2, '='}, {-1, '-'}, {0, '0'}, {1, '1'}, {2, '2'} };

    if (snafu_map.count(base10))
      return std::string(1, snafu_map.at(base10));

    for (int i = -2; i <= 2; ++i) {
      int64_t num = base10 - power * i;
      if (std::abs(num) <= max_value(power / 5))
        return std::string(1, snafu_map.at(i)) + to_snafu(base10 - power * i, power / 5);
    }
    return "";
  };

  int64_t answer = 0;
  std::string line;
  while ((line = parse_until(curr_it, str.end(), "\n")) != "") {
    answer += to_base10(line);
    ++curr_it;
  }

  int64_t power = 1;
  while (std::abs(answer) > max_value(power)) power *= 5;

  fmt::print("{}\n", to_snafu(answer, power));

  return 0;
}