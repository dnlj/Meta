// STD
#include <tuple>
#include <type_traits>

// Meta
#include <Meta/TypeSet/TypeSet.hpp>
#include <Meta/TypeSet/IsSuperset.hpp>

// Google Test
#include <gtest/gtest.h>

#define CREATE_TEST_TYPE(ClassName, Type)\
	struct ClassName {\
		using Set11 = Type<int, float, bool, double>;\
		using Set12 = Type<int, float, bool, double>;\
		constexpr static auto value1 = true;\
		\
		using Set21 = Type<int, float, bool, double>;\
		using Set22 = Type<float, double>;\
		constexpr static auto value2 = true;\
		\
		using Set31 = Type<int, float, bool, double>;\
		using Set32 = Type<char>;\
		constexpr static auto value3 = false;\
		\
		using Set41 = Type<int, float, double>;\
		using Set42 = Type<int, float, bool, double>;\
		constexpr static auto value4 = false;\
		\
		using Set51 = Type<int, float, bool, double>;\
		using Set52 = Type<int, float, bool, double, char>;\
		constexpr static auto value5 = false;\
	};\

#define CREATE_TEST_ASSERT(N) {\
	constexpr auto value = Meta::TypeSet::IsSuperset<TypeParam::Set##N##1, TypeParam::Set##N##2>::value;\
	ASSERT_EQ(value, TypeParam::value##N);\
}\

namespace {
	// Define the typed test fixture
	template<class T>
	class MetaTypeSetIsSupersetTest : public testing::Test {
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
TYPED_TEST_CASE(MetaTypeSetIsSupersetTest, Implementations);

TYPED_TEST(MetaTypeSetIsSupersetTest, IsSuperset) {
	CREATE_TEST_ASSERT(1);
	CREATE_TEST_ASSERT(2);
	CREATE_TEST_ASSERT(3);
	CREATE_TEST_ASSERT(4);
	CREATE_TEST_ASSERT(5);
}
