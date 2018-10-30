#ifndef _ITERATOR_H_
#define _ITERATOR_H_

#include <cstddef> // for std::ptrdiff_t
#include <iostream>

namespace xtl
{
struct input_iterator_tag
{
};

struct output_iterator_tag
{
};

struct forward_iterator_tag
{
};

struct bidirectional_iterator_tag
{
};

struct random_access_iterator_tag
{
};

/* template param is iterator type */
template <class Iter>
struct iterator_traits
{
    using difference_type = typename Iter::difference_type;
    using value_type = typename Iter::value_type;
    using pointer = typename Iter::pointer;
    using reference = typename Iter::reference;
    using iterator_category = typename Iter::iterator_category;
};

template <class T, class Distance>
class input_iterator
{
    /*
    using difference_type = typename Container::difference_type;
    using value_type = typename Container::value_type;
    using pointer = typename Container::pointer;
    using reference = typename Container::reference;
    using iterator_category = input_iterator_tag;

    reference operator*()
    {
        return val;
    }

    reference operator->()
    {
        return val;
    }

    reference operator++()
    {
        return ptr++;
    }

    reference operator++(int)
    {
        return ++ptr;
    }

  private:
    pointer ptr;
    */
};

class output_iterator
{
};

template <class T, class Distance = std::ptrdiff_t>
class forward_iterator
{
};

template <class T, class Distance = std::ptrdiff_t>
class bidirectional_iterator
{
};

template <class T, class Distance = std::ptrdiff_t>
class random_access_iterator
{
};

template <class T, class Distance = std::ptrdiff_t>
class istream_iterator : public input_iterator<T, Distance>
{
    template <class TT, class DD>
    friend bool operator==(const istream_iterator<TT, DD> &x, const istream_iterator<TT, DD> &y);

    template <class TT, class DD>
    friend bool operator!=(const istream_iterator<TT, DD> &x, const istream_iterator<TT, DD> &y);

  public:
    using difference_type = Distance;
    using value_type = T;
    using pointer = T *;
    using reference = T &;
    using iterator_category = input_iterator_tag;

  protected:
    std::istream *is;
    T val;
    bool having_slot;

    void readfromstream()
    {
        if (*is)
        {
            having_slot = true;
        }
        else
        {
            having_slot = false;
        }

        if (having_slot)
        {
            *is >> val;
        }

        if (*is)
        {
            having_slot = true;
        }
        else
        {
            having_slot = false;
        }
    }

  public:
    istream_iterator() : is(&std::cin), val(T()), having_slot(false)
    {
    }

    istream_iterator(std::istream &i)
        : is(&i), having_slot(false)
    {
        readfromstream();
    }

    const T &operator*()
    {
        return val;
    }

    istream_iterator<T, Distance> operator++()
    {
        readfromstream();
        return *this;
    }

    istream_iterator<T, Distance> operator++(int)
    {
        istream_iterator<T, Distance> tmp = *this;
        readfromstream();

        return tmp;
    }
};

template <class T, class Distance>
inline bool operator==(const xtl::istream_iterator<T, Distance> &x, const xtl::istream_iterator<T, Distance> &y)
{
    return x.is == y.is && x.having_slot == y.having_slot;
}

template <class T, class Distance>
inline bool operator!=(const xtl::istream_iterator<T, Distance> &x, const xtl::istream_iterator<T, Distance> &y)
{
    return !(x == y);
}

template <class T>
class ostream_iterator : public output_iterator
{
    using value_type = void;
    using difference_type = void;
    using pointer = void;
    using reference = void;
    using iterator_category = output_iterator_tag;

  public:
    ostream_iterator()
        : os(&std::cout)
    {
    }

    ostream_iterator(std::ostream &stream)
        : os(&stream)
    {
    }

    ostream_iterator(std::ostream &stream, const char *delim)
        : os(&stream), delim_internal(delim)
    {
    }

    ostream_iterator &operator=(const T &val)
    {
        *os << val;
        if (!delim_internal.empty())
        {
            *os << delim_internal;
        }

        return *this;
    }

    ostream_iterator &operator*()
    {
        return *this;
    }

    ostream_iterator &operator++()
    {
        return *this;
    }

    ostream_iterator &operator++(int)
    {
        return *this;
    }

  protected:
    std::ostream *os;
    std::string delim_internal;
};

template <class Container>
class back_inserter_iterator : output_iterator
{
  public:
    explicit back_inserter_iterator(Container &c)
        : ptr(&c)
    {
    }

    using value_type = void;
    using difference_type = void;
    using pointer = void;
    using reference = void;
    using iterator_category = xtl::output_iterator_tag;

    back_inserter_iterator<Container> &operator=(typename Container::const_reference value)
    {
        ptr->push_back(value);
        return *this;
    }

    back_inserter_iterator<Container> &operator*()
    {
        return *this;
    }

    back_inserter_iterator<Container> &operator++()
    {
        return *this;
    }

    back_inserter_iterator<Container> &operator++(int)
    {
        return *this;
    }

  protected:
    Container *ptr;
};

template <class Container>
class front_inserter_iterator : output_iterator
{
  public:
    explicit front_inserter_iterator(Container &c)
        : ptr(&c)
    {
    }

    using value_type = void;
    using difference_type = void;
    using pointer = void;
    using reference = void;
    using iterator_category = xtl::output_iterator_tag;

    front_inserter_iterator<Container> &operator=(typename Container::const_reference value)
    {
        ptr->push_front(value);
        return *this;
    }

    front_inserter_iterator<Container> &operator*()
    {
        return *this;
    }

    front_inserter_iterator<Container> &operator++()
    {
        return *this;
    }

    front_inserter_iterator<Container> &operator++(int)
    {
        return *this;
    }

  protected:
    Container *ptr;
};

template <class Container>
class inserter_iterator : output_iterator
{
  public:
    inserter_iterator(Container &c, typename Container::iterator i)
        : ptr(&c), iter(i)
    {
    }

    using value_type = void;
    using difference_type = void;
    using pointer = void;
    using reference = void;
    using iterator_category = xtl::output_iterator_tag;

    inserter_iterator<Container> &operator=(typename Container::const_reference value)
    {
        iter = ptr->insert(iter, value);
        iter++;
        return *this;
    }

    inserter_iterator<Container> &operator*()
    {
        return *this;
    }

    inserter_iterator<Container> &operator++()
    {
        return *this;
    }

    inserter_iterator<Container> &operator++(int)
    {
        return *this;
    }

  protected:
    Container *ptr;
    typename Container::iterator iter;
};

} // namespace xtl

#endif