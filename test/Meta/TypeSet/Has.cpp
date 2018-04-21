// STD
#include <tuple>
#include <type_traits>

// Meta
#include <Meta/TypeSet/TypeSet.hpp>
#include <Meta/TypeSet/Has.hpp>

// Google Test
#include <gtest/gtest.h>

#define CREATE_TEST_TYPE(ClassName, Type)\
	struct ClassName {\
		using Set1 = Type<int, float, bool, double>;\
		using Type1 = int;\
		constexpr static auto value1 = true;\
		\
		using Set2 = Type<int, float, bool, double>;\
		using Type2 = float;\
		constexpr static auto value2 = true;\
		\
		using Set3 = Type<int, float, bool, double>;\
		using Type3 = bool;\
		constexpr static auto value3 = true;\
		\
		using Set4 = Type<int, float, bool, double>;\
		using Type4 = double;\
		constexpr static auto value4 = true;\
		\
		\
		using Set5 = Type<int, float, bool, double>;\
		using Type5 = char;\
		constexpr static auto value5 = false;\
		\
		using Set6 = Type<int, float, bool, double>;\
		using Type6 = long;\
		constexpr static auto value6 = false;\
		\
		using Set7 = Type<int, float, bool, double>;\
		using Type7 = long double;\
		constexpr static auto value7 = false;\
	};\

// Define the typed test fixture
template<class T>
class MetaTypeSetHasTest : public testing::Test {
};

// Defined the classes for the tests.
CREATE_TEST_TYPE(TypeSetTest, Meta::TypeSet::TypeSet);
CREATE_TEST_TYPE(TupleTest, std::tuple);

// Define the types to use with our typed test
using Implementations = testing::Types<
	TypeSetTest,
	TupleTest
>;

// Define the tests
TYPED_TEST_CASE(MetaTypeSetHasTest, Implementations);

TYPED_TEST(MetaTypeSetHasTest, Has) {
	// True
	{
		constexpr auto value = Meta::TypeSet::Has<TypeParam::Set1, TypeParam::Type1>::value;
		ASSERT_EQ(value, TypeParam::value1);
	}

	{
		constexpr auto value = Meta::TypeSet::Has<TypeParam::Set2, TypeParam::Type2>::value;
		ASSERT_EQ(value, TypeParam::value2);
	}

	{
		constexpr auto value = Meta::TypeSet::Has<TypeParam::Set3, TypeParam::Type3>::value;
		ASSERT_EQ(value, TypeParam::value3);
	}

	{
		constexpr auto value = Meta::TypeSet::Has<TypeParam::Set4, TypeParam::Type4>::value;
		ASSERT_EQ(value, TypeParam::value4);
	}

	// False
	{
		constexpr auto value = Meta::TypeSet::Has<TypeParam::Set5, TypeParam::Type5>::value;
		ASSERT_EQ(value, TypeParam::value5);
	}

	{
		constexpr auto value = Meta::TypeSet::Has<TypeParam::Set6, TypeParam::Type6>::value;
		ASSERT_EQ(value, TypeParam::value6);
	}

	{
		constexpr auto value = Meta::TypeSet::Has<TypeParam::Set7, TypeParam::Type7>::value;
		ASSERT_EQ(value, TypeParam::value7);
	}
}
