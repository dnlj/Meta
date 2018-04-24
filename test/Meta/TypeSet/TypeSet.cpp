// Meta
#include <Meta/TypeSet/TypeSet.hpp>

// Google Test
#include <gtest/gtest.h>

TEST(MetaTypeSetTypeSet, Size) {
	{
		constexpr auto size = Meta::TypeSet::TypeSet<int>::size;
		ASSERT_EQ(size, 1);
	}

	{
		constexpr auto size = Meta::TypeSet::TypeSet<int, float>::size;
		ASSERT_EQ(size, 2);
	}

	{
		constexpr auto size = Meta::TypeSet::TypeSet<int, float, char>::size;
		ASSERT_EQ(size, 3);
	}
}