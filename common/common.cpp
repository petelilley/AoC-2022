#include <common.hpp>

// --- File Stuff ---

std::string get_file(std::filesystem::path path) {
  std::ifstream file(path);
  if (!file) {
    fmt::print("Error: Could not open file \"{}\" from directory \"{}\"\n", path.string(), std::filesystem::current_path().string());
    exit(1);
  }

  std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
  return str;
}

std::string get_file(int argc, char** argv, std::filesystem::path path) {
  if (argc == 2) {
    path = argv[1];
  }
  else if (argc > 2) {
    fmt::print("Usage: {} [input file]\n", argv[0]);
    exit(1);
  }

  return get_file(path);
}

// --- Parsing Stuff ---

std::ptrdiff_t count_while(std::string::const_iterator curr_it, std::string::const_iterator end_it, std::function<bool(char)> cond_func) {
  std::ptrdiff_t count = 0;
  while (curr_it != end_it && cond_func(*curr_it)) {
    ++curr_it;
    ++count;
  }
  return count;
}

std::string parse_while(std::string::const_iterator& curr_it, std::string::const_iterator end_it, std::function<bool(char)> cond_func) {
  std::ptrdiff_t count = count_while(curr_it, end_it, cond_func);
  std::string str(curr_it, curr_it + count);
  curr_it += count;
  return str;
}

std::ptrdiff_t count_until(std::string::const_iterator curr_it, std::string::const_iterator end_it, std::string chars) {
  return count_while(curr_it, end_it, [&chars](char c) {
    return chars.find(c) == std::string::npos;
  });
}

std::string parse_until(std::string::const_iterator& curr_it, std::string::const_iterator end_it, std::string chars) {
  std::ptrdiff_t count = count_until(curr_it, end_it, chars);
  std::string str(curr_it, curr_it + count);
  curr_it += count;
  return str;
}

double parse_double(std::string::const_iterator& curr_it, std::string::const_iterator end_it) {
  // Handle + and -
  int sign = 1;
  if (*curr_it == '-') {
    sign = -1;
    ++curr_it;
  }
  else if (*curr_it == '+') {
    ++curr_it;
  }

  // Parse the integer part.
  std::string int_str = parse_while(curr_it, end_it, [](char c) {
    return std::isdigit(c);
  });
  
  if (curr_it == end_it || *curr_it != '.') {
    return std::stoi(int_str) * sign;
  }

  // Parse the decimal part.
  ++curr_it;
  std::string dec_str = parse_while(curr_it, end_it, [](char c) {
    return std::isdigit(c);
  });

  std::string str = int_str + "." + dec_str;
  return std::stod(str) * sign;
}