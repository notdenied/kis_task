#include <array>
#include <cstddef>
#include <vector>

using CardType = short;
using HeapType = std::vector<CardType>;
static const std::size_t kHeapCount = 8;

using PositionType = std::array<HeapType, kHeapCount>;
using SimpleHeuristicType = std::size_t(const PositionType& heap);
