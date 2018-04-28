// STD
#include <tuple>

// Meta
#include <Meta/TypeSet/TypeSet.hpp>
#include <Meta/TypeSet/IndexOf.hpp>

// Google Test
#include <gtest/gtest.h>

// Test
#include <Test/Type.hpp>


namespace {
	template<template<class...> class Operation, template<class...> class SetType>
	void singleTest() {
		{ // Set size = 1
			constexpr auto value = Operation<SetType<Type<1>>, Type<1>>::value;

			ASSERT_EQ(value, 0);
		}

		{ // Set size = 2; First element
			constexpr auto value = Operation<SetType<Type<1>, Type<2>>, Type<1>>::value;
		
			ASSERT_EQ(value, 0);
		}

		{ // Set size = 2; Second element
			constexpr auto value = Operation<SetType<Type<2>, Type<1>>, Type<1>>::value;
		
			ASSERT_EQ(value, 1);
		}
		
		{ // Set size = 4; First element
			constexpr auto value = Operation<
				SetType<Type<1>, Type<2>, Type<3>, Type<4>>,
				Type<1>
			>::value;
		
			ASSERT_EQ(value, 0);
		}

		{ // Set size = 4; Second element
			constexpr auto value = Operation<
				SetType<Type<2>, Type<1>, Type<3>, Type<4>>,
				Type<1>
			>::value;
		
			ASSERT_EQ(value, 1);
		}

		{ // Set size = 4; Third element
			constexpr auto value = Operation<
				SetType<Type<2>, Type<3>, Type<1>, Type<4>>,
				Type<1>
			>::value;
		
			ASSERT_EQ(value, 2);
		}

		{ // Set size = 4; Fourth element
			constexpr auto value = Operation<
				SetType<Type<2>, Type<3>, Type<4>, Type<1>>,
				Type<1>
			>::value;
		
			ASSERT_EQ(value, 3);
		}
	}

	TEST(Meta_TypeSet_IndexOf, Single) {
		#define X(type) singleTest<Meta::TypeSet::IndexOf, type>();
		#include <Test/SetTypes.xmacro>
	}
}
