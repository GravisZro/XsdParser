#ifndef NONDELETEDPTR_H
#define NONDELETEDPTR_H

#include <memory>

template<typename T>
struct nondeleted_ptr : std::shared_ptr<T>
{
  nondeleted_ptr(T* ptr)
    : std::shared_ptr<T>(ptr, [](T*){}) {}
};

#endif // NONDELETEDPTR_H
