#pragma once

#include <algorithm>

#include "definitions.hpp"

// trivial for current types
void SortPosition(Position& pos) { std::sort(pos.begin(), pos.end()); }

void ReduceLineIfNeeded(Position& pos, std::size_t line_num) {
  if (pos[line_num].size() < kStartCardCount) {
    return;
  }
  bool need_to_clear_line = true;
  for (std::size_t j = pos[line_num].size() - kStartCardCount;
       j < pos[line_num].size() - 1; ++j) {
    if (pos[line_num][j] < pos[line_num][j + 1]) {
      need_to_clear_line = false;
      break;
    }
  }
  if (need_to_clear_line) {
    for (std::size_t cnt = 0; cnt < kStartCardCount; ++cnt) {
      pos[line_num].pop_back();
    }
  }
}

void ReducePositionIfNeeded(Position& pos) {
  for (std::size_t i = 0; i < pos.size(); ++i) {
    ReduceLineIfNeeded(pos, i);
  }
}