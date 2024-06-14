#include <thread>
#include <atomic>
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

#include "htop_component.hpp"
#include "flags_component.hpp"
#include "order_book_component.hpp"
#include "bar_chart_component.hpp"

using namespace ftxui;

int main() {
  auto screen = ScreenInteractive::Fullscreen();

  // Flags
  FlagsComponent flags_component;
  auto flags_renderer = flags_component.GetRenderer();

  // Htop
  HtopComponent htop_component;

  // Order Book
  OrderBookComponent order_book_component;
  auto order_book_renderer = order_book_component.GetRenderer();

  // Bar Chart Component
  BarChartComponent bar_chart_component;

  int tab_index = 0;
  std::vector<std::string> tab_entries = {
      "flags", "orderbook", "barchart", "chart 2"
  };
  auto tab_selection =
      Menu(&tab_entries, &tab_index, MenuOption::HorizontalAnimated());
  auto tab_content = Container::Tab(
      {
          flags_renderer,
          order_book_renderer,
          Renderer([&] { return bar_chart_component.Render(); }),
          Renderer([&] { return htop_component.Render(); }),
      },
      &tab_index);

  auto exit_button = Button(
      "Exit", [&] { screen.Exit(); }, ButtonOption::Animated());

  auto main_container = Container::Vertical({
      Container::Horizontal({
          tab_selection,
          exit_button,
      }),
      tab_content,
  });

  auto main_renderer = Renderer(main_container, [&] {
    return vbox({
        text("FTXUI Terminal TUI Demo") | bold | hcenter,
        hbox({
            tab_selection->Render() | flex,
            exit_button->Render(),
        }),
        tab_content->Render() | flex,
    });
  });

  std::atomic<bool> refresh_ui_continue = true;
  std::thread refresh_ui([&] {
    while (refresh_ui_continue) {
      using namespace std::chrono_literals;
      std::this_thread::sleep_for(0.05s);
      screen.Post([&] {
        flags_component.Update();
        order_book_component.Update();
        bar_chart_component.Update();
        htop_component.Update();
      });
      screen.Post(Event::Custom);
    }
  });

  screen.Loop(main_renderer);
  refresh_ui_continue = false;
  refresh_ui.join();

  return 0;
}
