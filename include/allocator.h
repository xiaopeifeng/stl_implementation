#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_

#include <cstddef> /* for std::size_t */
#include <limits>  /* for numeric_limits */

namespace xtl
{

template <class T>
inline T *__allocate(size_t n, T *)
{
	return (T *)operator new(n * sizeof(T));
}

template <class T>
inline void __deallocate(T *p)
{
	operator delete(p);
}

/* T is allocator type */
template <class Alloc>
struct AllocatorTrait
{
	using allocator_type = Alloc;
	using value_type = typename allocator_type::value_type;
	using pointer = value_type *;
	using const_pointer = const value_type *;
	using difference_type = typename Alloc::difference_type;
	using size_type = typename Alloc::size_type;

  public:
	static pointer allocate(Alloc &a, size_type n);
	static void deallocate(Alloc &a, pointer p, size_type n);

	template <class T, class... Args>
	static void construct(Alloc &a, T *p, Args &&... args);

	template <class T>
	static void destroy(Alloc &a, T *p);

	static size_type max_size(const Alloc &a);
};

template <class T>
class Allocator
{
  public:
	using value_type = T;
	using pointer = T *;
	using const_pointer = const T *;
	using reference = T &;
	using const_reference = const T &;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;

	Allocator() = default;
	Allocator(const Allocator &other) = default;

	/* TODO */
	template <class U>
	Allocator(const Allocator<U> &other);

	~Allocator()
	{
	}

	pointer address(reference x) const
	{
		return &x;
	}

	const_pointer address(const_reference x) const
	{
		return &x;
	}

	pointer allocate(size_type n, const void *hint = 0)
	{
		return __allocate(n, (pointer)0);
	}

	void deallocate(T *p)
	{
		__deallocate(p);
	}

	void construct(pointer p, const_reference val)
	{
		new ((void *)p) T(val);
	}

	template <class U, class... Args>
	void construct(U *p, Args &&... args)
	{
		new ((void *)p) T(args...);
	}

	void destroy(pointer p)
	{
		p->~T();
	}

	size_type max_size() const
	{
		return std::numeric_limits<size_type>::max() / sizeof(value_type);
	}
};

template <>
class Allocator<void>
{
  public:
	using value_type = void;
	using pointer = void *;
	using const_pointer = const void *;

	Allocator() = default;
	Allocator(const Allocator &other) = default;
	~Allocator() = default;
};

} /* namespace xtl */

#endif
