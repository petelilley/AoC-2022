#include <common.hpp>

int main(int argc, char** argv) {
  std::string str = get_file(argc, argv);
  std::string::const_iterator curr_it = str.begin();

  double answer = 0;



  fmt::print("{}\n", answer);

  return 0;
}