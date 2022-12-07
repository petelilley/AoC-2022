#include <common.hpp>

int main(int argc, char** argv) {
  auto [str, day, part] = aoc_init(argc, argv);
  std::string::const_iterator curr_it = str.begin();

  double answer = 0;

  std::map<std::filesystem::path, int> dir_sizes;

  std::filesystem::path cwd = "";

  while (curr_it != str.end()) {
    if (*curr_it == '$')
      curr_it += 2;
    std::string cmd = parse_until(curr_it, str.end(), " \n");
    curr_it++;
    if (cmd == "cd") {
      std::string dir = parse_until(curr_it, str.end(), "\n");
      curr_it++;

      if (dir == "..")
        cwd = cwd.parent_path();
      else
        cwd /= dir;

      dir_sizes.emplace(cwd, 0);
    }
    if (cmd == "ls") {
      int size = 0;
      while (1) {
        if (*curr_it == '$' || curr_it == str.end()) {
          std::filesystem::path x = cwd;
          while (true) {
            dir_sizes.at(x) += size;
            if (x == "/") break;
            x = x.parent_path();
          }
          break;
        }
        if (*curr_it == 'd') {
          parse_until(curr_it, str.end(), "\n");
          ++curr_it;
        }
        else { // number
          size += parse_double(curr_it, str.end());
          parse_until(curr_it, str.end(), "\n");
          ++curr_it;
        }
      }
    }
  }

  if (part == 1) {
    for (auto& [path, size] : dir_sizes) {
      if (size <= 100000)
        answer += size;
    }
  }
  else if (part == 2) {
    int free_space = 70000000 - dir_sizes.at("/");
    int target = 30000000 - free_space;
    answer = dir_sizes.at("/");

    for (auto& [path, size] : dir_sizes) {
      if (size >= target && size < answer)
        answer = size;
    }
  }
  
  fmt::print("{}\n", answer);

  return 0;
}