#include <cstddef>
#include <functional>
#include <vector>

#include "definitions.hpp"

template <typename VertexType, template <typename T> typename QueueContainer,
          template <typename T> typename CheckedContainer>
class AStar {
 private:
  struct AStarNode {
    VertexType vertex;
    std::size_t previous;
    std::size_t number;
  };

  std::function<std::size_t(const VertexType&)> heurictic_;
  std::function<std::vector<VertexType>(const VertexType&)> turns_generator_;
  QueueContainer<AStarNode> queue_;
  CheckedContainer<AStarNode> checked_;

 public:
  template <typename Heuristic, typename TurnsGenerator>
  AStar(const Heuristic& heuristic, const TurnsGenerator& generator)
      : heurictic_(heuristic), turns_generator_(generator) {}

  bool FoundSolution(const VertexType& start, const VertexType& finish) {
    // return true if solution exists; reusable
    queue_.clear();
    checked_.clear();
    queue_.insert(AStarNode(start, -1, 0));  // -1 is ok
    while (!queue_.empty()) {
      auto first = queue_.begin();

      if (checked_.exists(*first)) {
        continue;
      }
      checked_.insert(*first);

      if (first == finish) {
        return true;
      }

      std::vector<VertexType> possible_turns = turns_generator_(*first);
      for (VertexType&& vertex : possible_turns) {
        queue_.insert(
            AStarNode(std::move(vertex), first->number, checked_.size()));
      }
    }
    return false;
  }

  void PrintWay() {
    // TODO
  }
};