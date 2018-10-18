#include "allocator.h"
#include <gtest/gtest.h>

struct Foo
{
	Foo()
		: a(-1), b(-1)
	{
	}

	Foo(const Foo &rhs)
		: a(rhs.a), b(rhs.b)
	{
	}

	Foo(int x, int y)
		: a(x), b(y)
	{
	}

	~Foo()
	{
		a = -2;
		b = -2;
	}

	int a;
	int b;
};

TEST(TEST_ALLOCATOR, test_with_struct)
{
	xtl::Allocator<Foo> al;
	Foo *fo = al.allocate(1);
	al.construct(fo, 1, 2);
	EXPECT_EQ(fo->a, 1);
	EXPECT_EQ(fo->b, 2);

	al.construct(fo);
	EXPECT_EQ(fo->a, -1);
	EXPECT_EQ(fo->b, -1);

	al.destroy(fo);
	EXPECT_EQ(fo->a, -2);
	EXPECT_EQ(fo->b, -2);

	al.deallocate(fo);
}

TEST(TEST_ALLOCATOR, test_with_char)
{
	xtl::Allocator<char> al;
	char *pc = al.allocate(1);
	al.construct(pc, 'a');
	EXPECT_EQ(*pc, 'a');
	al.destroy(pc);
	al.deallocate(pc);
}

TEST(TEST_ALLOCATOR, test_with_void)
{
	EXPECT_EQ(typeid(void), typeid(xtl::Allocator<void>::value_type));
	EXPECT_EQ(typeid(void *), typeid(xtl::Allocator<void>::pointer));
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
