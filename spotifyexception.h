#ifndef SPOTIFYEXCEPTION_H
#define SPOTIFYEXCEPTION_H

#include <exception>
#include <string>

using namespace std;

class SpotifyException : public exception
{
private:
    string message;

public:
    explicit SpotifyException(const string& message);

    const char* what() const noexcept override;
};

#endif // SPOTIFYEXCEPTION_H
