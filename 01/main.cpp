#include <common.hpp>

#define PART 2

int main(int argc, char** argv) {
  std::string str = get_file(argc, argv);
  std::string::const_iterator curr_it = str.begin();

  std::vector<int> cals;

  int curr = 0;
  while (curr_it != str.end()) {
    if (*curr_it == '\n') {
      cals.push_back(curr);
      curr = 0;
      ++curr_it;
    }

    curr += parse_double(curr_it, str.end());
    ++curr_it;
  }

  std::sort(cals.begin(), cals.end());

  int total = 0;

#if PART == 1
  total = cals.back();
#elif PART == 2
  total = std::accumulate(cals.end() - 3, cals.end(), 0);
#endif

  fmt::print("{}\n", total);
  
  return 0;
}