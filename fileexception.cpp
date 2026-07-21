#include "fileexception.h"

FileException::FileException(const std::string& message)
    : SpotifyException(message)
{
}