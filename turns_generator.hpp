#include <cstddef>
#include <vector>

#include "definitions.hpp"

std::vector<PositionType> PossibleTurnsGenerator(const PositionType& position) {
  // we can move a card if target heap is empty or it's head is bigger than our
  std::vector<PositionType> out;

  for (size_t heap_num = 0; heap_num < kHeapCount; ++heap_num) {
    if (position[heap_num].empty()) {
      continue;
    }
    auto source_card = position[heap_num].back();
    for (size_t target_num = 0; target_num < kHeapCount; ++target_num) {
      if (target_num == heap_num) {
        continue;
      }

      if (position[target_num].empty() ||
          position[target_num].back() > source_card) {
        PositionType new_pos = position;
        new_pos[heap_num].pop_back();
        new_pos[target_num].push_back(source_card);
        out.push_back(std::move(new_pos));
      }
    }
  }

  return out;
}