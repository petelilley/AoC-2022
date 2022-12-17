#include <common.hpp>

int main(int argc, char** argv) {
  auto [str, day, part] = aoc_init(argc, argv);
  std::string::const_iterator curr_it = str.begin();

  std::vector<std::pair<int, int>> ranges;
  std::vector<int> beacons;

  std::vector<std::pair<std::pair<int, int>, int>> sensors;

  while (curr_it != str.end()) {
    curr_it += 12;
    int x0 = parse_double(curr_it, str.end());
    curr_it += 4;
    int y0 = parse_double(curr_it, str.end());
    curr_it += 25;
    int x1 = parse_double(curr_it, str.end());
    curr_it += 4;
    int y1 = parse_double(curr_it, str.end());
    curr_it++;
    int dist = std::abs(x0 - x1) + std::abs(y0 - y1);
    if (part == 1) {
      if (dist >= std::abs(y0 - 2e6)) {
          int v = dist - std::abs(y0 - 2e6);
          std::pair<int, int> p(x0 - v, x0 + v);
          ranges.push_back(p);
      }
      if (y1 == 2e6) {
          bool found = false;
          for (int i = 0; i < beacons.size(); i++)
            if (beacons[i] == x1)
              found = true;
          if (!found)
            beacons.push_back(x1);
      }
    }
    else if (part == 2) {
      sensors.push_back(std::make_pair(std::make_pair(x0, y0), dist));
    }
  }

  std::uint64_t answer = 0;

  if (part == 1) {
    std::sort(ranges.begin(), ranges.end());

    for (auto it = ranges.begin(); it != ranges.end() - 1; it++) {
        if ((it + 1)->first >= it->first && (it + 1)->first <= it->second) {
            (it + 1)->first = it->first;
            (it + 1)->second = std::max(it->second, (it + 1)->second);
            it->first = 0;
            it->second = -1;
        }
    }

    for (auto [a, b] : ranges) {
        answer += b - a + 1;
        for (auto x : beacons)
          if (x >= a && x <= b)
            answer--;
    }
  }
  else if (part == 2) {
    for (auto it = sensors.begin(); it != sensors.end(); it++) {
      for (auto jt = it + 1; jt != sensors.end(); jt++) {
        int ix = it->first.first, iy = it->first.second, ir = it->second,
            jx = jt->first.first, jy = jt->first.second, jr = jt->second;

        if (std::abs(ix - jx) + std::abs(iy - jy) == ir + jr + 2) {
          int x1 = ix + (jx - ix) / std::abs(jx - ix) * (ir + 1), y1 = iy;
          int x2 = ix, y2 = iy + (jy - iy) / std::abs(jy - iy) * (ir + 1);

          for (int qx = x1, qy = y1; qx != x2 && qy != y2; qx += (x2 - x1) / std::abs(x2 - x1), qy += (y2 - y1) / std::abs(y2 - y1)) {
            bool done = true;
            for (int k = 0; k < sensors.size(); k++) {
              int kx = sensors[k].first.first;
              int ky = sensors[k].first.second;
              int kr = sensors[k].second;
              if (std::abs(qx - kx) + std::abs(qy - ky) <= kr)
                done = false;
            }
            if (done) {
              answer = qx * 4e6 + qy;
              goto end;
            }
          }
        }
      }
    }
    end:;
  }

  fmt::print("{}\n", answer);

  return 0;
}