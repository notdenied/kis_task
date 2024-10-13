#pragma once

#include <algorithm>

#include "definitions.hpp"

// trivial for current types
void SortPosition(Position& pos) { std::sort(pos.begin(), pos.end()); }

void ReducePosition(Position& pos) {
  for (std::size_t i = 0; i < pos.size(); ++i) {
    if (pos[i].size() < kStartCardCount) {
      continue;
    }
    bool need_to_clear_line = true;
    for (std::size_t j = pos[i].size() - kStartCardCount; j < pos[i].size() - 1;
         ++j) {
      if (pos[i][j] < pos[i][j + 1]) {
        need_to_clear_line = false;
        break;
      }
    }
    if (need_to_clear_line) {
      for (std::size_t cnt = 0; cnt < kStartCardCount; ++cnt) {
        pos[i].pop_back();
      }
    }
  }
}