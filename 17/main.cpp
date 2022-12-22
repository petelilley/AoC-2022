#include <common.hpp>

int main(int argc, char** argv) {
  auto [str, day, part] = aoc_init(argc, argv);
  str.pop_back();

  using coord_list = std::set<std::pair<int, int>>;
   constexpr auto get_piece = [](int i, int y) -> coord_list {
    switch (i) {
      case 0: return coord_list{{2, y}, {3, y}, {4, y}, {5, y}};
      case 1: return coord_list{{3, y+2}, {2, y+1}, {3,y+1}, {4,y+1}, {3,y}};
      case 2: return coord_list{{2, y}, {3,y}, {4,y}, {4,y+1}, {4,y+2}};
      case 3: return coord_list{{2,y},{2,y+1},{2,y+2},{2,y+3}};
      case 4: return coord_list{{2,y+1},{2,y},{3,y+1},{3,y}};
    }
  };

  constexpr auto does_intersect = [](const coord_list& a, const coord_list& b) -> bool {
    for (auto& [x, y] : b)
      if (a.find({x, y}) != a.end())
        return true;
    return false;
  };

  std::map<std::tuple<uint64_t, uint64_t, coord_list>, std::pair<uint64_t, uint64_t>> saved;
  coord_list placed = coord_list{{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}};
  coord_list rock, new_rock;
  uint64_t jet_i = 0, top = 0, answer = 0;
  for (uint64_t i = 0; i < (part == 1 ? 2022 : 1e12); ++i) {
    rock = get_piece(i % 5, top+4);

    while (true) {
      if (str[jet_i] == '>') { // move right
        bool wall = false;
        for (auto& [x, y] : rock)
          if (x == 6) wall = true;
        new_rock.clear();
        for (auto& [x, y] : rock)
          new_rock.insert({x+1, y});
        new_rock = wall ? rock : new_rock;

        if (!does_intersect(placed, new_rock))
          rock = new_rock;
      }
      else { // move left
        bool wall = false;
        for (auto& [x, y] : rock)
          if (x == 0) wall = true;
        new_rock.clear();
        for (auto& [x, y] : rock)
          new_rock.insert({x-1, y});
        new_rock = wall ? rock : new_rock;

        if (!does_intersect(placed, new_rock))
          rock = new_rock;
      }

      jet_i = (jet_i + 1) % str.size();
      
      new_rock.clear();
      for (auto& [x, y] : rock)
        new_rock.insert({x, y-1});

      if (does_intersect(placed, new_rock)) {
        for (auto& [x, y] : rock)
          placed.insert({x, y});
        for (auto& [x, y] : placed)
          if (y > top)
            top = y;
        
        if (part == 1) break;

        coord_list top_placed;
        for (int y = top - 50; y <= top; ++y) // top 50 rows or something
          for (int x = 0; x < 7; ++x) {
            if (placed.find({x, y}) != placed.end())
              top_placed.insert({x, top-y});
          }

        auto key = std::make_tuple(jet_i, i%5, top_placed);
        if (saved.find(key) != saved.end()) {
          auto [old_i, old_top] = saved[key];
          auto dy = top - old_top;
          auto di = i - old_i;
          uint64_t amt = (1e12 - i) / di;
          answer += amt * dy;
          i += amt * di;          
        }
        saved[key] = {i, top};
        break;
      }
      else rock = new_rock;
    }
  }

  answer += top;
  fmt::print("{}\n", answer);

  return 0;
}