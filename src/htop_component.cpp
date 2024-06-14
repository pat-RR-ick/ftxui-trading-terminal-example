#include "htop_component.hpp"
#include "data_utils.hpp"  // Ensure this utility is used for generating data
#include "ftxui/component/component.hpp"
#include "ftxui/dom/elements.hpp"

using namespace ftxui;

HtopComponent::HtopComponent()
  : shift(0),
    last_update_time_(std::chrono::steady_clock::now()),
    random_engine_(std::random_device{}()),
    volume_distribution_(0.1f, 5.0f) {

  InitializeData();
}

void HtopComponent::InitializeData() {
  bid_volumes_ = std::vector<float>(50);
  ask_volumes_ = std::vector<float>(50);
  
  for (int i = 0; i < 50; ++i) {
    bid_volumes_[i] = volume_distribution_(random_engine_);
    ask_volumes_[i] = volume_distribution_(random_engine_);
  }
}

void HtopComponent::Update() {
  shift++;
  UpdateDataIfNeeded();
}

void HtopComponent::UpdateDataIfNeeded() {
  auto now = std::chrono::steady_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - last_update_time_).count();
  if (elapsed >= 5) {
    for (int i = 0; i < 50; ++i) {
      bid_volumes_[i] = volume_distribution_(random_engine_);
      ask_volumes_[i] = volume_distribution_(random_engine_);
    }
    last_update_time_ = now; // Reset the timestamp
  }
}

std::vector<int> HtopComponent::graph_data(const std::vector<float>& data, int width, int height) {
  std::vector<int> output(width);
  int data_size = static_cast<int>(data.size());
  for (int i = 0; i < width; ++i) {
    float value = data[(i + shift) % data_size];
    output[i] = static_cast<int>(value / 5.0f * height);  // Adjust scaling
  }
  return output;
}

Element HtopComponent::Render() {
  auto bid_volume_graph = vbox({
      text("Bid Volume") | hcenter,
      hbox({
          vbox({
              text("5 "),
              filler(),
              text("0 "),
          }),
          graph(std::bind(&HtopComponent::graph_data, this, std::ref(bid_volumes_), std::placeholders::_1, std::placeholders::_2)) | color(Color::GreenLight) | flex,
      }) | flex,
  });

  auto ask_volume_graph = vbox({
      text("Ask Volume") | hcenter,
      hbox({
          vbox({
              text("5 "),
              filler(),
              text("0 "),
          }),
          graph(std::bind(&HtopComponent::graph_data, this, std::ref(ask_volumes_), std::placeholders::_1, std::placeholders::_2)) | color(Color::RedLight) | flex,
      }) | flex,
  });

  return hbox({
             bid_volume_graph | flex,
             separator(),
             ask_volume_graph | flex,
         }) |
         flex;
}
