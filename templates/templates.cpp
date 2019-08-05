#include "include/templates.h"

template<class T>
bool Stack<T>::push(const T &t)
{
    if (offset == sizeof buffer) {
        return false;
    }
    buffer[++offset] = t;
}
template<class T>
bool Stack<T>::pop(T &t)
{
    if (offset == -1) {
        return false;
    }
    t = buffer[offset--];
    return true;
}

