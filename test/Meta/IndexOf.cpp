// Metae
#include <Meta/IndexOf.hpp>

// Google Test
#include <gtest/gtest.h>

TEST(MetaIndexOf, IndexOf) {
	{ // First in list
		constexpr auto idx = Meta::IndexOf<int, int, int, int, int>::value;
		ASSERT_EQ(idx, 0);
	}

	{ // Not first in list
		constexpr auto idx = Meta::IndexOf<int, float, int, double, int, int>::value;
		ASSERT_EQ(idx, 1);
	}

	{ // Last in list
		constexpr auto idx = Meta::IndexOf<int, float, char, double, int>::value;
		ASSERT_EQ(idx, 3);
	}
}
