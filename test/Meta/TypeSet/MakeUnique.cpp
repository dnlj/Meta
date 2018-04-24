// STD
#include <tuple>
#include <type_traits>

// Meta
#include <Meta/TypeSet/MakeUnique.hpp>
#include <Meta/TypeSet/TypeSet.hpp>

// Google Test
#include <gtest/gtest.h>

#define CREATE_TEST_TYPE(ClassName, Type)\
	struct ClassName {\
		using Set1 = Type<int, float, int, bool, int, int, bool, float, int, double, int, int>;\
		using Unique1 = Type<int, float, bool, double>;\
		\
		using Set2 = Type<int, int, int, int>;\
		using Unique2 = Type<int>;\
	};\

namespace {
	// Define the typed test fixture
	template<class T>
	class MetaTypeSetMakeUniqueTest : public testing::Test {
	};

	// Defined the classes for the tests.
	CREATE_TEST_TYPE(TypeSetTest, Meta::TypeSet::TypeSet);
	CREATE_TEST_TYPE(TupleTest, std::tuple);

	// Define the types to use with our typed test
	using Implementations = testing::Types<
		TypeSetTest,
		TupleTest
	>;
}

// Define the tests
TYPED_TEST_CASE(MetaTypeSetMakeUniqueTest, Implementations);

TYPED_TEST(MetaTypeSetMakeUniqueTest, MakeUnique) {
	{
		constexpr auto condition = std::is_same<
			Meta::TypeSet::MakeUnique<TypeParam::Set1>::type,
			TypeParam::Unique1
		>::value;

		ASSERT_TRUE(condition);
	}
	{
		constexpr auto condition = std::is_same<
			Meta::TypeSet::MakeUnique<TypeParam::Set2>::type,
			TypeParam::Unique2
		>::value;

		ASSERT_TRUE(condition);
	}
}
