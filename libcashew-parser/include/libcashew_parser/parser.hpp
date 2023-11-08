#pragma once

#include <string>
#include <variant>

namespace cashew::parser
{
///
/// A literal value
///
typedef std::variant<std::string, u_int8_t, u_int16_t, u_int32_t, u_int64_t, int8_t, int16_t, int32_t, ino64_t, float,
                     double, bool>
    literal;
} // namespace cashew::parser