#include "definitions.hpp"

std::size_t CardCountHeuristic(const Position& position) {
  // simple heuristic - card count on the table (we want zero)
  std::size_t count = 0;
  for (const Heap& heap : position) {
    count += heap.size();
  }
  return count;
}

std::size_t InversionsCountSlowHeuristic(const Position& position) {
  // a bit more complex heuristic - sum of inversions in every heap (can only
  // decrease, less == better (informal, because we want 0 in the end))

  // TODO: O(n^2) implementation, can be O(n\log(n)), but n is quite small in
  // out task -> it is ok
  std::size_t inv_count = 0;
  for (std::size_t i = 0; i < position.size(); i++) {
    for (std::size_t j = i + 1; j < position.size(); j++) {
      if (position[i] > position[j]) {
        ++inv_count;
      }
    }
  }
  return inv_count;
}

template <SimpleHeuristicType... heuristics>
struct HeuristicContainer {
  std::size_t operator()(const Position& position) {
    return (heuristics(position) + ...);
  }
};

using DefaultHeuristic =
    HeuristicContainer<CardCountHeuristic, InversionsCountSlowHeuristic>;