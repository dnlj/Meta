// STD
#include <tuple>

// Meta
#include <Meta/TypeSet/TypeSet.hpp>
#include <Meta/TypeSet/Has.hpp>

// Google Test
#include <gtest/gtest.h>

// Test
#include <Test/Type.hpp>


namespace {
	template<template<class...> class Operation, template<class...> class SetType>
	void singleTest() {
		{ // Empty set
			constexpr auto value = Meta::TypeSet::Has<SetType<>, Type<1>>::value;

			ASSERT_FALSE(value);
		}

		{ // Set size = 1; Has type
			constexpr auto value = Meta::TypeSet::Has<SetType<Type<1>>, Type<1>>::value;

			ASSERT_TRUE(value);
		}

		{ // Set size = 1; Does not have type
			constexpr auto value = Meta::TypeSet::Has<SetType<Type<2>>, Type<1>>::value;

			ASSERT_FALSE(value);
		}

		{ // Set size = 2; Has type
			constexpr auto value = Meta::TypeSet::Has<SetType<Type<1>, Type<2>>, Type<1>>::value;

			ASSERT_TRUE(value);
		}

		{ // Set size = 2; Does not have type
			constexpr auto value = Meta::TypeSet::Has<SetType<Type<2>, Type<3>>, Type<1>>::value;

			ASSERT_FALSE(value);
		}

		{ // Set size = 4; Has type
			constexpr auto value = Meta::TypeSet::Has<
				SetType<Type<2>, Type<1>, Type<3>, Type<4>>,
				Type<1>
			>::value;

			ASSERT_TRUE(value);
		}

		{ // Set size = 4; Does not have type
			constexpr auto value = Meta::TypeSet::Has<
				SetType<Type<2>, Type<3>, Type<4>, Type<5>>,
				Type<1>
			>::value;

			ASSERT_FALSE(value);
		}
	}

	TEST(Meta_TypeSet_Has, Single) {
		#define X(type) singleTest<Meta::TypeSet::Has, type>();
		#include <Test/SetTypes.xmacro>
	}
}
