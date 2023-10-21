#ifndef NONDELETEDPTR_H
#define NONDELETEDPTR_H

#include <memory>
#include <iostream>
#include <type_traits>

template<typename T, typename... Args>
static std::shared_ptr<T> create(Args... args)
{
  auto ptr = std::shared_ptr<T>(new T(args...));
  ptr->T::initialize();
  return ptr;
}

#endif // NONDELETEDPTR_H
