#include <vector>

#include "definitions.hpp"
#include "utils.hpp"

Position ProduceNewPositionHelper(const Position& pos,
                                  std::size_t source_heap,
                                  std::size_t target_heap) {
  Position new_pos = pos;
  auto source_card = pos[source_heap].back();

  new_pos[source_heap].pop_back();
  new_pos[target_heap].push_back(source_card);

  ReduceLineIfNeeded(new_pos, target_heap);
  SortPosition(new_pos);

  return new_pos;  // copy elision
}

std::vector<Position> PossibleTurnsGenerator(const Position& pos) {
  // we can move a card if target heap is empty or it's head is bigger than our
  std::vector<Position> new_positions;

  for (size_t heap_num = 0; heap_num < kHeapCount; ++heap_num) {
    if (pos[heap_num].empty()) {
      continue;
    }
    auto source_card = pos[heap_num].back();
    for (size_t target_num = 0; target_num < kHeapCount; ++target_num) {
      if (target_num == heap_num) {
        continue;
      }

      if (pos[target_num].empty() ||
          pos[target_num].back() > source_card) {
        new_positions.push_back(
            std::move(ProduceNewPositionHelper(pos, heap_num, target_num)));
      }
    }
  }

  return new_positions;
}