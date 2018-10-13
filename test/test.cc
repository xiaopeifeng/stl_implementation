#include "allocator.h"
#include <iostream>

struct Foo {
	Foo(const Foo &rhs)
		: a(rhs.a)
		, b(rhs.b)
	{
		std::cout << "copy ctor\n";
	}

	Foo(int x, int y)
		: a(x)
		, b(y)
	{
		std::cout << "ctor(" << x << "," << y << ")\n";
	}

	~Foo()
	{
		std::cout << "dtor\n";
	}

	int a;
	int b;
};

int main()
{
	xtl::Allocator<Foo> al;
	Foo* fo = al.allocate(1);
	al.construct(fo, 1, 2);
	al.destroy(fo);
	al.deallocate(fo);
}