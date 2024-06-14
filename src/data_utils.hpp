#pragma once

#include <string>
#include <vector>
#include <random>
#include <sstream>

template <typename T>
std::string FormatFloat(T value, int precision = 2) {
    std::ostringstream out;
    out.precision(precision);
    out << std::fixed << value;
    return out.str();
}

template <typename OrderType>
std::vector<OrderType> GenerateSimulatedOrders(bool is_bid, int count, float start_price, float step) {
    std::vector<OrderType> orders;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> size_dist(0.1, 5.0);
    std::uniform_int_distribution<> user_order_dist(0, 9); // 10% chance of being user order

    for (int i = 0; i < count; ++i) {
        orders.push_back(OrderType{
            start_price + i * step * (is_bid ? -1 : 1),
            static_cast<float>(size_dist(gen)),
            user_order_dist(gen) == 0
        });
    }
    return orders;
}
