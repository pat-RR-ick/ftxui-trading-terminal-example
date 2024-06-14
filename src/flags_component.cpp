#include "flags_component.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/dom/elements.hpp"

using namespace ftxui;

FlagsComponent::FlagsComponent()
    : shift(0),
      venue_selected(0),
      venue_entries{
          "Binance", "Upbit", "Bithumb", "Bitkub", "Huobi", "XXChange", "Backpack"
      },
      market_type_label{
          "PERP", "SPOT",
      },
      market_type_state{false, false, false, false, false, false, false, false},
      order_type_label{
          "Kline", "Open Interest", "Funding Rate",
      },
      order_type_state{false, false, false} {

  venue = Radiobox(&venue_entries, &venue_selected);
  left_asset_ = Input(&left_asset_content_, "left asset");
  right_asset_ = Input(&right_asset_content_, "right asset");

  market_type = Container::Vertical({
      Checkbox(&market_type_label[0], &market_type_state[0]),
      Checkbox(&market_type_label[1], &market_type_state[1]),
  });

  order_type = Container::Vertical({
      Checkbox(&order_type_label[0], &order_type_state[0]),
      Checkbox(&order_type_label[1], &order_type_state[1]),
      Checkbox(&order_type_label[2], &order_type_state[2]),
  });

  flags_component = Container::Horizontal({
      venue,
      market_type,
      order_type,
      Container::Vertical({
          Container::Horizontal({
              left_asset_ | size(WIDTH, EQUAL, 20),
              right_asset_ | size(WIDTH, EQUAL, 20),
          }),
      }),
  });
}

Component FlagsComponent::GetRenderer() {
  return Renderer(flags_component, [&] {
    auto venue_win = window(text("Venues"), 
                            venue->Render() | vscroll_indicator | frame);
    auto market_type_win =
        window(text("Market Type"), market_type->Render() | vscroll_indicator | frame);
    auto order_type_win =
        window(text("Order Type"), order_type->Render() | vscroll_indicator | frame);
    auto left_asset_win = window(text("LEFT ASSET"), left_asset_->Render());
    auto right_asset_win = window(text("RIGHT ASSET"), right_asset_->Render());

    return vbox({
               hbox({
                   venue_win,
                   market_type_win,
                   order_type_win,
                   vbox({
                       left_asset_win,
                       right_asset_win,
                   }),
                   filler(),
               }) | size(HEIGHT, LESS_THAN, 8),
               hflow(render_command()) | flex_grow,
           }) |
           flex_grow;
  });
}

void FlagsComponent::Update() {
  shift++;
  // Update logic if necessary
}

Element FlagsComponent::render_command() {
  Elements line;
  line.push_back(text(venue_entries[venue_selected]) | bold);
  for (int i = 0; i < 2; ++i) {
    if (market_type_state[i]) {
      line.push_back(text(" "));
      line.push_back(text(market_type_label[i]) | dim);
    }
  }
  for (int i = 0; i < 3; ++i) {
    if (order_type_state[i]) {
      line.push_back(text(" "));
      line.push_back(text(order_type_label[i]) | dim);
    }
  }
  if (!left_asset_content_.empty()) {
    line.push_back(text(" ") | bold);
    line.push_back(text(left_asset_content_) | color(Color::BlueLight) | bold);
  }
  if (!right_asset_content_.empty()) {
    line.push_back(text("-") | bold);
    line.push_back(text(right_asset_content_) | color(Color::GreenLight) | bold);
  }
  return hflow(line);
}
