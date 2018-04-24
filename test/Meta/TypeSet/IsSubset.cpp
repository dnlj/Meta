// STD
#include <tuple>
#include <type_traits>

// Meta
#include <Meta/TypeSet/TypeSet.hpp>
#include <Meta/TypeSet/IsSubset.hpp>

// Google Test
#include <gtest/gtest.h>

#define CREATE_TEST_TYPE(ClassName, Type)\
	struct ClassName {\
		/* A.size > B.size; same types, same order */\
		using Set11 = Type<int, float, bool, double>;\
		using Set12 = Type<float, double>;\
		constexpr static auto value1 = false;\
		\
		/* A.size > B.size; same types, different order */\
		using Set21 = Type<int, float, bool, double>;\
		using Set22 = Type<double, float>;\
		constexpr static auto value2 = false;\
		\
		/* A.size > B.size; different types */\
		using Set31 = Type<int, float, bool, double>;\
		using Set32 = Type<char, double>;\
		constexpr static auto value3 = false;\
		\
		\
		/* A.size == B.size; same types, same order */\
		using Set41 = Type<int, float, bool, double>;\
		using Set42 = Type<int, float, bool, double>;\
		constexpr static auto value4 = true;\
		\
		/* A.size == B.size; same types, different order */\
		using Set51 = Type<int, float, bool, double>;\
		using Set52 = Type<float, bool, int, double>;\
		constexpr static auto value5 = true;\
		\
		/* A.size == B.size; different types */\
		using Set61 = Type<int, float, bool, double>;\
		using Set62 = Type<int, float, long, double>;\
		constexpr static auto value6 = false;\
		\
		\
		/* A.size < B.size; same types */\
		using Set71 = Type<float, double>;\
		using Set72 = Type<int, float, bool, double>;\
		constexpr static auto value7 = true;\
		\
		/* A.size < B.size; same types, different order */\
		using Set81 = Type<float, double>;\
		using Set82 = Type<int, float, bool, double>;\
		constexpr static auto value8 = true;\
		\
		/* A.size < B.size; different types */\
		using Set91 = Type<char, double>;\
		using Set92 = Type<int, float, bool, double>;\
		constexpr static auto value9 = false;\
	};\

#define CREATE_TEST_ASSERT(N) {\
	constexpr auto value = Meta::TypeSet::IsSubset<TypeParam::Set##N##1, TypeParam::Set##N##2>::value;\
	ASSERT_EQ(value, TypeParam::value##N);\
}\

namespace {
	// Define the typed test fixture
	template<class T>
	class MetaTypeSetIsSubsetTest : public testing::Test {
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
TYPED_TEST_CASE(MetaTypeSetIsSubsetTest, Implementations);

TYPED_TEST(MetaTypeSetIsSubsetTest, IsSuperset) {
	CREATE_TEST_ASSERT(1);
	CREATE_TEST_ASSERT(2);
	CREATE_TEST_ASSERT(3);
	CREATE_TEST_ASSERT(4);
	CREATE_TEST_ASSERT(5);
	CREATE_TEST_ASSERT(6);
	CREATE_TEST_ASSERT(7);
	CREATE_TEST_ASSERT(8);
	CREATE_TEST_ASSERT(9);
}
