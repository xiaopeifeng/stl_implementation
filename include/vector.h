#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <memory>  // for std::alocator
#include <cstdlib> // for std::size_t
#include "iterator.h"

namespace xtl
{
template <class T, class Allocator = std::allocator<T>>
class vector
{
  public:
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = typename Allocator::reference;
    using const_reference = typename Allocator::const_reference;
    using pointer = typename Allocator::pointer;
    using const_pointer = typename Allocator::const_pointer;
    using iterator = xtl::random_access_iterator;
    using const_iterator = const xtl::random_access_iterator;

    vector()
        : alloc(Allocator()), base(alloc.allocate(4)), cap_size(4), cur_hold_size(0)
    {
    }

    vector(size_type n)
        : alloc(Allocator()), base(alloc.allocate(n)), cap_size(), cur_hold_size(n)
    {
        for (auto i = 0; i < n; ++i)
        {
            alloc.construct(alloc[i]);
        }
    }

    ~vector()
    {
        for (auto i = 0; i < cur_hold_size; ++i)
        {
            alloc.destroy(base + i * sizeof(T));
        }

        for (auto i = 0; i < cap_size; ++i)
        {
            alloc.deallocate(base + i * sizeof(T));
        }
    }

  private:
    Allocator alloc;
    pointer base;
    size_type cap_size;
    size_type cur_hold_size;
};

} // namespace xtl

#endif