// STD
#include <tuple>
#include <type_traits>

// Meta
#include <Meta/TypeSet/Concat.hpp>
#include <Meta/TypeSet/TypeSet.hpp>

// Google Test
#include <gtest/gtest.h>

#define CREATE_TEST_TYPE(ClassName, Type)\
	struct ClassName {\
		using Set11 = Type<int, float, bool, double>;\
		using Set12 = Type<char, float, double, long>;\
		using Concat1 = Type<int, float, bool, double, char, float, double, long>;\
		\
		using Set21 = Type<int, int, int, int>;\
		using Set22 = Type<int, int>;\
		using Concat2 = Type<int, int, int, int, int, int>;\
	};\

namespace {
	// Define the typed test fixture
	template<class T>
	class MetaTypeSetConcatTest : public testing::Test {
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
TYPED_TEST_CASE(MetaTypeSetConcatTest, Implementations);

TYPED_TEST(MetaTypeSetConcatTest, Concat) {
	{
		constexpr auto condition = std::is_same<
			Meta::TypeSet::Concat<TypeParam::Set11, TypeParam::Set12>::type,
			TypeParam::Concat1
		>::value;

		ASSERT_TRUE(condition);
	}

	{
		constexpr auto condition = std::is_same<
			Meta::TypeSet::Concat<TypeParam::Set21, TypeParam::Set22>::type,
			TypeParam::Concat2
		>::value;

		ASSERT_TRUE(condition);
	}
}
