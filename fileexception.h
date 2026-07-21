#ifndef FILEEXCEPTION_H
#define FILEEXCEPTION_H

#include "SpotifyException.h"

class FileException : public SpotifyException
{
public:
    explicit FileException(const string& message);
};

#endif // FILEEXCEPTION_H
