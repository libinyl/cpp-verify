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
T &Stack<T>::pop()
{
    if (offset == -1) {

    }
    return buffer[offset--];
}

