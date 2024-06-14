#include "bar_chart_component.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/dom/elements.hpp"
#include "data_utils.hpp"
#include <sstream>
#include <random>

using namespace ftxui;

BarChartComponent::BarChartComponent()
  : last_update_time_(std::chrono::steady_clock::now()),
    random_engine_(std::random_device{}()),
    price_distribution_(45000, 55000),
    size_distribution_(0.1f, 5.0f),
    shift_(0) {

  InitializeData();
}

void BarChartComponent::InitializeData() {
  bids_ = GenerateSimulatedOrders<Order>(true, 50, 50000, 100);
  asks_ = GenerateSimulatedOrders<Order>(false, 50, 50500, 100);
}

void BarChartComponent::Update() {
  shift_++;
  UpdateDataIfNeeded();
}

void BarChartComponent::UpdateDataIfNeeded() {
  auto now = std::chrono::steady_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - last_update_time_).count();
  if (elapsed >= 5) {
    bids_ = GenerateSimulatedOrders<Order>(true, 50, 50000, 100);
    asks_ = GenerateSimulatedOrders<Order>(false, 50, 50500, 100);
    last_update_time_ = now; // Reset the timestamp
  }
}

ftxui::Element BarChartComponent::Render() {
  ftxui::Elements rows;

  for (size_t i = 0; i < bids_.size(); ++i) {
    float bid_ratio = bids_[i].size / 5.0f;
    float ask_ratio = asks_[i].size / 5.0f;

    auto bid_bar = gaugeLeft(bid_ratio) | color(Color::Green) | size(WIDTH, LESS_THAN, 20) | flex;
    auto ask_bar = gaugeRight(ask_ratio) | color(Color::Red) | size(WIDTH, LESS_THAN, 20) | flex;

    if (bids_[i].is_user_order) {
      bid_bar = bid_bar | bold | bgcolor(Color::BlueLight);
    }

    if (asks_[i].is_user_order) {
      ask_bar = ask_bar | bold | bgcolor(Color::BlueLight);
    }

    rows.push_back(
      hbox({
        text(FormatFloat(bids_[i].size, 1)) | size(WIDTH, EQUAL, 5),
        bid_bar,
        filler(),
        ask_bar,
        text(FormatFloat(asks_[i].size, 1)) | size(WIDTH, EQUAL, 5)
      })
    );
  }

  return vbox({
    text("Bar Chart") | bold | hcenter | size(HEIGHT, LESS_THAN, 1),
    separator(),
    vbox(rows) | vscroll_indicator | frame | flex
  });
}
