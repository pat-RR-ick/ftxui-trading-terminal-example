#pragma once

#include <string>
#include <vector>
#include <chrono>
#include <random>
#include "ftxui/component/component.hpp"

class BarChartComponent {
public:
  BarChartComponent();
  ftxui::Element Render();
  void Update();

  struct Order {
    float price;
    float size;
    bool is_user_order;
  };

private:
  std::vector<Order> bids_;
  std::vector<Order> asks_;
  std::chrono::steady_clock::time_point last_update_time_;
  std::mt19937 random_engine_;
  std::uniform_real_distribution<float> size_distribution_;
  std::uniform_real_distribution<float> price_distribution_;
  int shift_;

  void InitializeData();
  void UpdateDataIfNeeded();
};
