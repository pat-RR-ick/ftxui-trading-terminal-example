#pragma once

#include <string>
#include <vector>
#include <array>
#include "ftxui/component/component.hpp"

class FlagsComponent {
public:
  FlagsComponent();
  ftxui::Component GetRenderer();
  void Update();

private:
  int shift;
  int venue_selected;
  std::vector<std::string> venue_entries;
  std::array<std::string, 8> market_type_label;
  std::array<bool, 8> market_type_state;
  std::string left_asset_content_;
  std::string right_asset_content_;

  std::array<std::string, 3> order_type_label;
  std::array<bool, 3> order_type_state;

  ftxui::Component venue;
  ftxui::Component market_type;
  ftxui::Component left_asset_;
  ftxui::Component right_asset_;
  ftxui::Component order_type;
  ftxui::Component flags_component;

  ftxui::Element render_command();
};
