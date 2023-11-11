/*!
 * @file libcashew_parser/exceptions.hpp
 */
#pragma once

#include <string>

namespace cashew::parser
{
/*!
 * @class InvalidTokenException
 * @brief An exception thrown when a token is invalid
 */
class InvalidTokenException final : public std::exception
{
    std::string message;

  public:
    /*!
     * @fn InvalidTokenException(std::string message)
     * @brief Construct a new Invalid Token Exception object
     * @param message The message to display
     */
    explicit InvalidTokenException(std::string message) : message(std::move(message))
    {
    }

    [[nodiscard]] const char *what() const noexcept override
    {
        return message.c_str();
    }
};
} // namespace cashew::parser