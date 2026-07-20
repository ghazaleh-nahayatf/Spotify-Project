#ifndef LISTENERFILEMANGER_H
#define LISTENERFILEMANGER_H

#include "listener.h"
#include <vector>

using namespace std;

class ListenerFileManager
{
public:
    static void save(const vector<Listener>& listeners);

    static vector<Listener> load();
};


#endif // LISTENERFILEMANGER_H
