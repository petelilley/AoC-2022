#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cctype>
#include <ctime>
#include <cassert>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <functional>
#include <memory>
#include <utility>
#include <limits>
#include <numeric>
#include <iterator>
#include <chrono>
#include <random>
#include <array>
#include <tuple>
#include <initializer_list>
#include <filesystem>
#include <variant>
#include <optional>
#include <queue>

#include <fmt/format.h>

// --- File Stuff ---

/**
 * @brief Returns the contents of a file as a string.
 * 
 * @param path The path to the file.
 * @return The contents of the file.
 */
std::string get_file(std::filesystem::path path = "input.txt");

// --- Init stuff ---

struct Init {
  std::string file;
  int day;
  int part = 1;
};

/**
 * @brief Returns the initial data for the program.
 * 
 * @param argc The number of arguments.
 * @param argv The arguments.
 * @return A struct containing the initial data (file string, day, part).
 */
Init aoc_init(int argc, char** argv);

// --- Parsing Stuff ---

/**
 * @brief Counts the number of characters while a condition is met.
 * 
 * @param curr_it The current iterator of the string.
 * @param end_it The end iterator of the string.
 * @param cond_func The condition that must be met.
 * @return The number of characters that met the condition.
 */
std::ptrdiff_t count_while(std::string::const_iterator curr_it, std::string::const_iterator end_it, std::function<bool(char)> cond_func);

/**
 * @brief Parses a string while a condition is met.
 * 
 * @param curr_it The current iterator of the string (will be iterated when parsing).
 * @param end_it The end iterator of the string.
 * @param cond_func The condition that must be met.
 * @return The parsed string of characters that met the condition.
 */
std::string parse_while(std::string::const_iterator& curr_it, std::string::const_iterator end_it, std::function<bool(char)> cond_func);

/**
 * @brief Counts the number of characters until a character is met.
 * 
 * @param curr_it The current iterator of the string.
 * @param end_it The end iterator of the string.
 * @param chars A list of characters that will stop the count.
 * @return The number of characters that were counted before a character was met.
 */
std::ptrdiff_t count_until(std::string::const_iterator curr_it, std::string::const_iterator end_it, std::string chars);

/**
 * @brief Parses a string until a character is met.
 * 
 * @param curr_it The current iterator of the string (will be iterated when parsing).
 * @param end_it The end iterator of the string.
 * @param chars A list of characters that will stop the parsing.
 * @return The parsed string of characters that were counted before a character was met.
 */
std::string parse_until(std::string::const_iterator& curr_it, std::string::const_iterator end_it, std::string chars);

/**
 * @brief Parses a double from a string.
 * 
 * @param curr_it The current iterator of the string (will be iterated when parsing).
 * @param end_it The end iterator of the string.
 * @return The parsed double.
 */
double parse_double(std::string::const_iterator& curr_it, std::string::const_iterator end_it);
