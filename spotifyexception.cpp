#include "spotifyexception.h"

SpotifyException::SpotifyException(const std::string& message)
    : message(message)
{
}

const char* SpotifyException::what() const noexcept
{
    return message.c_str();
}