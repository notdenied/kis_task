#include <cstddef>
#include <functional>
#include <iostream>
#include <vector>

template <typename Vertex>
struct AStarNode {
  Vertex vertex;
  std::size_t distance;
  std::size_t previous;
  std::size_t number;
};

template <typename Vertex>
using ContainersValue = AStarNode<Vertex>;

// not an A-star actually (use only heurictic, no distances), but let it be
template <typename Vertex, typename QueueContainer, typename CheckedContainer>
class AStar {
  // Vertex need to have operator< implemented
 private:
  // we can choose appropriate heuristic function to get target finish vertex
  AStarNode<Vertex> finish_;  // not so good design?
  std::function<std::size_t(const Vertex&)> heuristic_;
  std::function<std::vector<Vertex>(const Vertex&)> turns_generator_;
  QueueContainer queue_;
  CheckedContainer checked_;
  std::size_t current_number_ = 0;

 public:
  template <typename Heuristic, typename TurnsGenerator>
  AStar(const Heuristic& heuristic, const TurnsGenerator& generator)
      : heuristic_(heuristic), turns_generator_(generator) {}

  bool FoundSolution(const Vertex& start) {
    // precondition: start is sorted vertex
    // return true if solution exists; reusable

    queue_.clear();
    checked_.clear();
    current_number_ = 0;

    queue_.insert(AStarNode(start, heuristic_(start), -1,
                            current_number_++));  // -1 is ok
    while (!queue_.empty()) {
      auto first = queue_.begin();

      if (checked_.contains(*first)) {
        queue_.erase(first);
        continue;
      }
      checked_.insert(*first);

      if (first->distance == 0) {
        finish_ = *first;
        return true;
      }

      std::vector<Vertex> possible_turns = turns_generator_(first->vertex);
      for (Vertex& vertex : possible_turns) {
        // can be better here - do not create -> insert new verts, put them
        // directly to the queue (but generator need to be able to count
        // heurictics - it is bad design)
        size_t distance = heuristic_(vertex);
        queue_.insert(AStarNode(std::move(vertex), distance, first->number,
                                current_number_++));
      }
      queue_.erase(first);
    }

    return false;
  }

  void PrintWay() {
    // precondition: FoundSolution called and returned `true`.

    // TODO: better indexation to remove logic below.
    std::vector<AStarNode<Vertex>> matching(current_number_);
    for (const auto& vertex : checked_) {
      matching[vertex.number] = vertex;
    }

    AStarNode<Vertex> cur_node = finish_;
    std::cout << "empty_position";

    while (cur_node.previous != static_cast<std::size_t>(-1)) {  // ok
      cur_node = matching[cur_node.previous];
      std::cout << '\n';
      PrintVertex(cur_node.vertex);
    }

    std::cout << std::endl;
  }

  void PrintVertex(const Vertex& vertex) {
    // TODO (!): vertex type-independent print (move to operator of Position)

    for (std::size_t i = 0; i < vertex.size(); ++i) {
      std::cout << '\n';
      if (vertex[i].empty()) {
        std::cout << "empty_heap";
        continue;
      }
      for (std::size_t j = 0; j < vertex[i].size(); ++j) {
        std::cout << vertex[i][j] << ' ';
      }
    }
  }
};

template <typename VertexType>
bool operator<(const AStarNode<VertexType>& lhs,
               const AStarNode<VertexType>& rhs) {
  return lhs.vertex < rhs.vertex;
}