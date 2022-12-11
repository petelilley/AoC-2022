#include <common.hpp>

int main(int argc, char** argv) {
  auto [str, day, part] = aoc_init(argc, argv);
  std::string::const_iterator curr_it = str.begin();

  std::array<std::vector<char>, 9> stacks;

  std::string line;
  int n = 0;

  while (n++ < 8) {
    line = parse_until(curr_it, str.end(), "\n");
    ++curr_it;

    for (int i = 0; i < 9; i++) {
      char c = line.at(1 + (4 * i));
      if (c != ' ')
        stacks.at(i).push_back(c);
    }
  }
  for (int i = 0; i < 9; i++)
    std::reverse(stacks.at(i).begin(), stacks.at(i).end());
  parse_until(curr_it, str.end(), "\n");
  curr_it += 2;

  while (curr_it != str.end()) {
    curr_it += 5;
    int num = parse_double(curr_it, str.end());
    curr_it += 6;
    int from = parse_double(curr_it, str.end())-1;
    curr_it += 4;
    int to = parse_double(curr_it, str.end())-1;
    curr_it++;
    
    std::vector<char>& from_stack = stacks.at(from);
    std::vector<char>& to_stack = stacks.at(to);
  
    for (int i = num - 1; i >= 0; i--) {
      if (part == 1) {
        to_stack.push_back(from_stack.back());
        from_stack.pop_back();
      }
      else if (part == 2) {
        int from_index = from_stack.size() - 1 - i;
        to_stack.push_back(from_stack.at(from_index));
        from_stack.erase(from_stack.begin() + from_index);
      }
    }
  }

  std::string answer = "";
  for (auto& stack : stacks)
    answer.push_back(stack.back());

  fmt::print("{}\n", answer);

  return 0;
}