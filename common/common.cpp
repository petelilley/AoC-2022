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

Init aoc_init(int argc, char** argv) {
  std::filesystem::path path;
  int part = 1;
  if (argc != 3) {
    fmt::print("Usage: {} [input file] [part number]\n", argv[0]);
    exit(1);
  }

  // Executable name (remove leading path)
  std::string day_substr = std::filesystem::path(argv[0]).filename().string().substr(0, 2);

  int day = std::stoi(day_substr);

  if (day < 1 || day > 25) {
    fmt::print("Error: Invalid day number: {}\n", day);
    exit(1);
  }

  path = argv[1];

  part = std::stoi(argv[2]);

  if (part != 1 && part != 2) {
    fmt::print("Error: Part number must be 1 or 2\n");
    exit(1);
  }

  fmt::print("Init day = {}, part = {}\n\n", day, part);

  return Init { get_file(path), day, part };
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