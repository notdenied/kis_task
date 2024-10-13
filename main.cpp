#include <iostream>
#include <set>

#include "a_star.hpp"
#include "definitions.hpp"
#include "heuristics.hpp"
#include "turns_generator.hpp"
#include "utils.hpp"

int main() {
  Position start;
  for (std::size_t i = 0; i < kHeapCount; ++i) {
    start[i].resize(kStartCardCount);
    for (std::size_t j = 0; j < kStartCardCount; ++j) {
      std::cin >> start[i][j];
    }
  }
  ReducePositionIfNeeded(start);
  SortPosition(start);

  using Container = std::set<ContainersValue<Position>>;
  auto solver = AStar<Position, Container, Container>(DefaultHeuristic(),
                                                      PossibleTurnsGenerator);
  bool solvable = solver.FoundSolution(start);

  if (solvable) {
    std::cout << "Solution exists:" << std::endl;
    solver.PrintWay();
  } else {
    std::cout << "Solution does not exist!" << std::endl;
  }
}