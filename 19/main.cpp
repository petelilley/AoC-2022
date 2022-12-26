#include <common.hpp>

#include <algorithm>
#include <deque>
#include <unordered_set>
#include <tuple>

struct State {
  int ore, clay, obs, geo, r1, r2, r3, r4, time;

  bool operator<(const State& other) const {
    return std::tie(ore, clay, obs, geo, r1, r2, r3, r4, time) <
           std::tie(other.ore, other.clay, other.obs, other.geo,
                    other.r1, other.r2, other.r3, other.r4, other.time);
  }
};

int solve(int ore_cost, int clay_cost, int obs_ore_cost, int obs_clay_cost, int geo_ore_cost, int geo_clay_cost, int start_time) {
  int best = 0;

  std::deque<State> queue = { {0, 0, 0, 0, 1, 0, 0, 0, start_time} };
  std::set<State> saved;
  while (!queue.empty()) {
    State state = queue.front();
    queue.pop_front();
    auto& [ore, clay, obs, geo, r1, r2, r3, r4, time] = state;
    best = std::max(best, geo);
    if (time == 0) continue;
    int cost = std::max({ore_cost, clay_cost, obs_ore_cost, geo_ore_cost});
    r1 = std::min(r1, cost);
    r2 = std::min(r2, obs_clay_cost);
    r3 = std::min(r3, geo_clay_cost);
    ore = std::min(ore, time * cost - r1 * (time - 1));
    clay = std::min(clay, time * obs_clay_cost - r2 * (time - 1));
    obs = std::min(obs, time * geo_clay_cost - r3 * (time - 1));
    if (saved.count(state)) continue;
    saved.insert(state);
    queue.push_back(State{ore + r1, clay + r2, obs + r3, geo + r4, r1, r2, r3, r4, time - 1});
    if (ore >= ore_cost)
        queue.push_back(State{ore - ore_cost + r1, clay + r2, obs + r3, geo + r4, r1 + 1, r2, r3, r4, time - 1});
    if (ore >= clay_cost)
        queue.push_back(State{ore - clay_cost + r1, clay + r2, obs + r3, geo + r4, r1, r2 + 1, r3, r4, time - 1});
    if (ore >= obs_ore_cost && clay >= obs_clay_cost)
        queue.push_back(State{ore - obs_ore_cost + r1, clay - obs_clay_cost + r2, obs + r3, geo + r4, r1, r2, r3 + 1, r4, time - 1});
    if (ore >= geo_ore_cost && obs >= geo_clay_cost)
        queue.push_back(State{ore - geo_ore_cost + r1, clay + r2, obs - geo_clay_cost + r3, geo + r4, r1, r2, r3, r4 + 1, time - 1});
  }
  return best;
}


int main(int argc, char** argv) {
  auto [str, day, part] = aoc_init(argc, argv);
  std::string::const_iterator curr_it = str.begin();

  int answer = part == 2;
  while (curr_it != str.end()) {
    curr_it += 10;
    int id = parse_double(curr_it, str.end());
    curr_it += 23;
    int ore_cost = parse_double(curr_it, str.end());
    curr_it += 28;
    int clay_cost = parse_double(curr_it, str.end());
    curr_it += 32;
    int obs_ore_cost = parse_double(curr_it, str.end());
    curr_it += 9;
    int obs_clay_cost = parse_double(curr_it, str.end());
    curr_it += 30;
    int geo_ore_cost = parse_double(curr_it, str.end());
    curr_it += 9;
    int geo_clay_cost = parse_double(curr_it, str.end());
    curr_it += 11;

    if (part == 1)
      answer += id * solve(ore_cost, clay_cost, obs_ore_cost, obs_clay_cost, geo_ore_cost, geo_clay_cost, 24);
    else if (part == 2 && id < 4)
      answer *= solve(ore_cost, clay_cost, obs_ore_cost, obs_clay_cost, geo_ore_cost, geo_clay_cost, 32);
  }

  fmt::print("{}\n", answer);

  return 0;
}