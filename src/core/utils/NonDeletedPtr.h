#ifndef NONDELETEDPTR_H
#define NONDELETEDPTR_H

#include <memory>
#include <iostream>
#include <type_traits>
/*
template<typename T>
struct nondeleted_ptr : std::shared_ptr<T>
{
  nondeleted_ptr(T* ptr)
    : std::shared_ptr<T>(ptr, [](T*){
    std::cout << "end of nondeleted_ptr<" << typeid(T).name() << ">" << std::endl;
  }) {}
};
*/

template<typename T, typename... Args>
static std::shared_ptr<T> create(Args... args)
{
  auto ptr = std::shared_ptr<T>(new T(args...));
  ptr->T::initialize();
  return ptr;
}

template<typename T>
class Creatable : public std::enable_shared_from_this<T>
{
public:
/*
  template<typename... Args>
  static std::shared_ptr<T> create(Args... args)
  {
    auto ptr = std::shared_ptr<T>(new T(args...));
    ptr->initialize();
    return ptr;
  }
  */
};


#endif // NONDELETEDPTR_H
