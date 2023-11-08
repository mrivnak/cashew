#pragma once

#include <string>

///
/// An exception thrown when a token is invalid
///
class InvalidTokenException : public std::exception
{
  private:
    std::string message;

  public:
    ///
    /// \brief Construct a new Invalid Token Exception object
    /// \param message The message to display
    ///
    explicit InvalidTokenException(std::string message) : message(std::move(message))
    {
    }

    [[nodiscard]] const char *what() const noexcept override
    {
        return message.c_str();
    }
};