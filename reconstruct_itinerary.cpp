#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using ::testing::ElementsAre;
using ::testing::IsEmpty;

std::vector<std::string> findItinerary(const std::vector<std::vector<std::string>>& tickets) {
  const std::string startNode = "JFK";

  std::unordered_map<std::string, std::multiset<std::string>> graph;
  std::unordered_map<std::string, int> degrees;
  for (const auto& ticket : tickets) {
    const auto& from = ticket[0];
    const auto& to = ticket[1];
    graph[from].insert(to);
    degrees[from]++;
    degrees[to]--;
  }

  std::string endNode;
  for (const auto& entry : degrees) {
    if (entry.second == -1) {
      endNode = entry.first;
      break;
    }
  }

  std::list<std::string> path{startNode};
  std::list<std::list<std::string>::iterator> leftovers{path.begin()};
  while (!leftovers.empty()) {
    auto leftoverIter = --leftovers.end();
    auto leftover = leftovers.back();
    const auto& subpathStart = *leftover;

    std::list<std::string> subpath{};

    std::string current = subpathStart;
    while (true) {
      auto& outgoingEdges = graph[current];

      if (outgoingEdges.empty()) {
        break;
      }

      auto lowestOutgoing = *outgoingEdges.begin();
      outgoingEdges.erase(outgoingEdges.begin());

      subpath.push_back(lowestOutgoing);

      if (graph[lowestOutgoing].size() > 1) {
        auto end = subpath.end();
        --end;
        leftovers.push_back(end);
      }

      current = lowestOutgoing;
    }

    path.splice(++leftover, subpath);

    auto& outgoingEdges = graph[subpathStart];
    if (outgoingEdges.empty()) {
      leftovers.erase(leftoverIter);
    }
  }

  return std::vector<std::string>{path.begin(), path.end()};
}

TEST(ReconstructItinerary, test) {
  ASSERT_THAT(
      findItinerary(
          std::vector<std::vector<std::string>>{{"JFK", "KUL"}, {"JFK", "NRT"}, {"NRT", "JFK"}}),
      ElementsAre("JFK", "NRT", "JFK", "KUL"));
  ASSERT_THAT(
      findItinerary(std::vector<std::vector<std::string>>{{"JFK", "ATL"}, {"ATL", "JFK"}}),
      ElementsAre("JFK", "ATL", "JFK"));
  ASSERT_THAT(
      findItinerary(std::vector<std::vector<std::string>>{
          {"MUC", "LHR"}, {"JFK", "MUC"}, {"SFO", "SJC"}, {"LHR", "SFO"}}),
      ElementsAre("JFK", "MUC", "LHR", "SFO", "SJC"));
  ASSERT_THAT(
      findItinerary(std::vector<std::vector<std::string>>{
          {"JFK", "SFO"}, {"JFK", "ATL"}, {"SFO", "ATL"}, {"ATL", "JFK"}, {"ATL", "SFO"}}),
      ElementsAre("JFK", "ATL", "JFK", "SFO", "ATL", "SFO"));
  ASSERT_THAT(
      findItinerary(std::vector<std::vector<std::string>>{
          {"EZE", "TIA"}, {"EZE", "HBA"}, {"AXA", "TIA"}, {"JFK", "AXA"}, {"ANU", "JFK"},
          {"ADL", "ANU"}, {"TIA", "AUA"}, {"ANU", "AUA"}, {"ADL", "EZE"}, {"ADL", "EZE"},
          {"EZE", "ADL"}, {"AXA", "EZE"}, {"AUA", "AXA"}, {"JFK", "AXA"}, {"AXA", "AUA"},
          {"AUA", "ADL"}, {"ANU", "EZE"}, {"TIA", "ADL"}, {"EZE", "ANU"}, {"AUA", "ANU"}}),
      ElementsAre(
          "JFK",
          "AXA",
          "AUA",
          "ADL",
          "ANU",
          "AUA",
          "ANU",
          "EZE",
          "ADL",
          "EZE",
          "ANU",
          "JFK",
          "AXA",
          "EZE",
          "TIA",
          "AUA",
          "AXA",
          "TIA",
          "ADL",
          "EZE",
          "HBA"));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
