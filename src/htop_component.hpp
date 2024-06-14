#pragma once

#include <cmath>
#include <vector>
#include <chrono>
#include <random>
#include "ftxui/dom/elements.hpp"

using namespace ftxui;

class HtopComponent {
public:
  HtopComponent();

  Element Render();
  void Update();

private:
  int shift;
  std::chrono::steady_clock::time_point last_update_time_;
  std::mt19937 random_engine_;
  std::uniform_real_distribution<float> volume_distribution_;
  std::vector<float> bid_volumes_;
  std::vector<float> ask_volumes_;

  void InitializeData();
  void UpdateDataIfNeeded();
  std::vector<int> graph_data(const std::vector<float>& data, int width, int height);
};
