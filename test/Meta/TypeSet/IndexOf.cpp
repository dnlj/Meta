// STD
#include <tuple>
#include <type_traits>

// Meta
#include <Meta/TypeSet/TypeSet.hpp>
#include <Meta/TypeSet/IndexOf.hpp>

// Google Test
#include <gtest/gtest.h>

#define CREATE_TEST_TYPE(ClassName, Type)\
	struct ClassName {\
		using Set1 = Type<int, float, bool, double>;\
		using Type1 = int;\
		constexpr static auto value1 = 0;\
		\
		using Set2 = Type<int, float, bool, double>;\
		using Type2 = float;\
		constexpr static auto value2 = 1;\
		\
		using Set3 = Type<int, float, bool, double>;\
		using Type3 = bool;\
		constexpr static auto value3 = 2;\
		\
		using Set4 = Type<int, float, bool, double>;\
		using Type4 = double;\
		constexpr static auto value4 = 3;\
	};\

#define CREATE_TEST_ASSERT(N) {\
	constexpr auto value = Meta::TypeSet::IndexOf<TypeParam::Type##N, TypeParam::Set##N>::value;\
	ASSERT_EQ(value, TypeParam::value##N);\
}\

namespace {
	// Define the typed test fixture
	template<class T>
	class MetaTypeSetIndexOfTest : public testing::Test {
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
TYPED_TEST_CASE(MetaTypeSetIndexOfTest, Implementations);

TYPED_TEST(MetaTypeSetIndexOfTest, IndexOf) {
	CREATE_TEST_ASSERT(1);
	CREATE_TEST_ASSERT(2);
	CREATE_TEST_ASSERT(3);
	CREATE_TEST_ASSERT(4);
}
