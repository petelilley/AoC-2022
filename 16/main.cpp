#include <common.hpp>

int main(int argc, char** argv) {
  auto [str, day, part] = aoc_init(argc, argv);
  std::string::const_iterator curr_it = str.begin();

  std::vector<std::pair<std::string, std::pair<int, std::vector<std::string>>>> valves;
  {
    std::string valve;
    int rate;
    std::vector<std::string> to_valves;
    while (curr_it != str.end()) {
      curr_it += 6;
      valve = parse_until(curr_it, str.end(), " ");
      curr_it += 15;
      rate = parse_double(curr_it, str.end());
      curr_it += 24;
      if (*curr_it == ' ') curr_it++;
      to_valves.clear();
      while (*curr_it != '\n') {
        to_valves.push_back(parse_until(curr_it, str.end(), ",\n"));
        if (*curr_it == ',')
          curr_it += 2;
      }
      curr_it++;
      valves.emplace_back(valve, std::make_pair(rate, to_valves));
    }
  }

  int aa_idx = 0;
  for (int i = 0; i < valves.size(); i++)
    if (valves[i].first == "AA") {
      aa_idx = i;
      break;
    }

  std::map<std::string, int> val_to_idx;
  for (int i = 0; i < valves.size(); i++)
    val_to_idx[valves.at(i).first] = i;

                      //rate, to_valves
  std::vector<std::pair<int, std::vector<int>>> new_valves;

  for (auto& [valve, p] : valves) {
    auto& [rate, to_valves] = p;
    std::vector<int> to;
    for (auto& v : to_valves)
      to.push_back(val_to_idx.at(v));
    new_valves.emplace_back(rate, std::move(to));
  }

  std::map<std::tuple<int, int, int, int>, int> saved;

  std::function<int(int, int, int, int)> solve =
    [&](int valve, int opened, int time, int following) -> int {
      if (time == 0)
        return following>0 ? solve(aa_idx, opened, 26, following - 1) : 0;

      auto k = std::make_tuple(valve, opened, time, following);
      if (saved[k]) return saved.at(k);

      int a = 0;
      int rate = new_valves.at(valve).first;
      if (!(opened & (1 << valve)) && rate > 0) { // not open and rate greater than 0
        a = std::max(a, ((time - 1) * rate) + solve(valve, opened | (1 << valve), time - 1, following));
      }
      for (int& idx : new_valves.at(valve).second) // next valve
        a = std::max(a, solve(idx, opened, time - 1, following));
      saved[k] = a;

      return a;
  };

  int answer = 0;
  if (part == 1) {
    answer = solve(aa_idx, 0, 30, 0);
  }
  else if (part == 2) {
    answer = solve(aa_idx, 0, 26, 1);
  }

  fmt::print("{}\n", answer);

  return 0;
}