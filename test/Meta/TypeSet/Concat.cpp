// STD
#include <tuple>
#include <type_traits>

// Meta
#include <Meta/TypeSet/Concat.hpp>

// Google Test
#include <gtest/gtest.h>

#define CREATE_TEST_TYPE(ClassName, Type)\
	struct ClassName {\
		using Set1 = Type<int, float, bool, double>;\
		using Set2 = Type<char, float, double, long>;\
		using Concat = Type<int, float, bool, double, char, float, double, long>;\
	};\

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

// Define the tests
TYPED_TEST_CASE(MetaTypeSetConcatTest, Implementations);

TYPED_TEST(MetaTypeSetConcatTest, Concat) {
	constexpr auto condition = std::is_same<
		Meta::TypeSet::Concat<TypeParam::Set1, TypeParam::Set2>::type,
		TypeParam::Concat
	>::value;

	ASSERT_TRUE(condition);
}
