#pragma once

#include <array>
#include <cstddef>
#include <vector>

static const std::size_t kHeapCount = 8;
static const std::size_t kStartCardCount = 9;

using Card = short;              // any type which can hold 9 or more values
using Heap = std::vector<Card>;  // need to be changeable
using Position = std::array<Heap, kHeapCount>;  // can be constant sized
// TODO: better (faster) ordering (vector -> num)?

// function type for atomic heuristics for further combinations
using SimpleHeuristicType = std::size_t(const Position& heap);
