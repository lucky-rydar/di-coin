#pragma once

#include <json.hpp>

using namespace nlohmann;

template <typename T>
concept Jsonifiable = requires(T t) {
    { t.jsonify() } -> std::convertible_to<json>;
};

template <Jsonifiable T>
json jsonify(const T& obj) {
    return obj.jsonify();
}
