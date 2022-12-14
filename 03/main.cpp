#include <common.hpp>

int main(int argc, char** argv) {
  auto [str, day, part] = aoc_init(argc, argv);
  std::string::const_iterator curr_it = str.begin();

  int answer = 0;

  std::vector<std::string> parts;
  std::string line;
  int n = 0;
  while ((line = parse_until(curr_it, str.end(), "\n")) != "") {
    curr_it++;

    if (part == 1) {
      auto mysort = [](std::string s) -> std::string {
        std::sort(s.begin(), s.end());
        return s;
      };

      parts.push_back(mysort(line.substr(0, line.size() / 2)));
      parts.push_back(mysort(line.substr(line.size() / 2)));
    }
    else if (part == 2) {
      std::sort(line.begin(), line.end());
      parts.push_back(line);
      if (n++ != 2) continue;
      n = 0;
    }

    // find intersection of all parts.
    std::string in = parts[0];
    for (int i = 1; i < parts.size(); i++) {
      std::string new_in;
      std::set_intersection(in.begin(), in.end(),
                            parts[i].begin(), parts[i].end(),
                            std::back_inserter(new_in));
      in = new_in;
    }
    parts.clear();

    answer += in.at(0);
    if (in.at(0) <= 'Z')
      answer += 27 - 'A';
    else
      answer += 1 - 'a';
  }

  fmt::print("{}\n", answer);

  return 0;
}