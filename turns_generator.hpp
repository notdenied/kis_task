#include <cstddef>
#include <vector>

#include "definitions.hpp"
#include "utils.hpp"

Position ProduceNewPositionHelper(const Position& current, std::size_t source_pos,
                            std::size_t target_pos) {
  Position new_pos = current;
  auto source_card = current[source_pos].back();

  new_pos[source_pos].pop_back();
  new_pos[target_pos].push_back(source_card);
  bool need_to_clear_line = true;
  for (size_t i = 0; i < new_pos[target_pos].size() - 1; ++i) {
    if (new_pos[target_pos][i] < new_pos[target_pos][i + 1]) {
      need_to_clear_line = false;
      break;
    }
  }
  if (need_to_clear_line) {
    new_pos[target_pos].clear();
  }

  SortPosition(new_pos);

  return new_pos;  // copy elision
}

std::vector<Position> PossibleTurnsGenerator(const Position& current) {
  // we can move a card if target heap is empty or it's head is bigger than our
  std::vector<Position> out;

  for (size_t heap_num = 0; heap_num < kHeapCount; ++heap_num) {
    if (current[heap_num].empty()) {
      continue;
    }
    auto source_card = current[heap_num].back();
    for (size_t target_num = 0; target_num < kHeapCount; ++target_num) {
      if (target_num == heap_num) {
        continue;
      }

      if (current[target_num].empty() ||
          current[target_num].back() > source_card) {
        out.push_back(
            std::move(ProduceNewPositionHelper(current, heap_num, target_num)));
      }
    }
  }

  return out;
}