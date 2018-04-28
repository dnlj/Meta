// STD
#include <tuple>

// Meta
#include <Meta/TypeSet/TypeSet.hpp>
#include <Meta/TypeSet/Intersection.hpp>

// Google Test
#include <gtest/gtest.h>

// Test
#include <Test/Type.hpp>
#include <Test/Test.hpp>


namespace {
	template<template<class...> class SetType>
	void twoTest() {
		{ // Empty
			constexpr auto value = Test::checkBinaryTypeOperator<
				Meta::TypeSet::Intersection,
			
				SetType<>,
				SetType<>,

				SetType<>
			>();

			ASSERT_TRUE(value);
		}

		{ // All same types
			constexpr auto value = Test::checkBinaryTypeOperator<
				Meta::TypeSet::Intersection,
			
				SetType<Type<1>, Type<2>, Type<3>, Type<4>>,
				SetType<Type<1>, Type<2>, Type<3>, Type<4>>,

				SetType<Type<1>, Type<2>, Type<3>, Type<4>>
			>();

			ASSERT_TRUE(value);
		}

		{ // Some same types
			constexpr auto value = Test::checkBinaryTypeOperator<
				Meta::TypeSet::Intersection,
			
				SetType<Type<1>, Type<2>, Type<3>, Type<4>>,
				SetType<Type<3>, Type<6>, Type<1>, Type<8>>,

				SetType<Type<1>, Type<3>>
			>();

			ASSERT_TRUE(value);
		}

		{ // None same types
			constexpr auto value = Test::checkBinaryTypeOperator<
				Meta::TypeSet::Intersection,
			
				SetType<Type<1>, Type<2>, Type<3>, Type<4>>,
				SetType<Type<5>, Type<6>, Type<7>, Type<8>>,

				SetType<>
			>();

			ASSERT_TRUE(value);
		}
	}

	template<template<class...> class SetType>
	void multipleTest() {
		{ // Empty
			constexpr auto value = Test::checkBinaryTypeOperatorMultiple<
				Meta::TypeSet::Intersection,
			
				SetType<>,
				SetType<>,
				SetType<>,
				SetType<>
			>();

			ASSERT_TRUE(value);
		}

		{ // All same types
			constexpr auto value = Test::checkBinaryTypeOperatorMultiple<
				Meta::TypeSet::Intersection,
			
				SetType<Type< 1>, Type< 2>, Type< 3>, Type< 4>>,
				SetType<Type< 1>, Type< 2>, Type< 3>, Type< 4>>,
				SetType<Type< 1>, Type< 2>, Type< 3>, Type< 4>>,
				SetType<Type< 1>, Type< 2>, Type< 3>, Type< 4>>
			>();
			
			ASSERT_TRUE(value);
		}

		{ // Some same types
			constexpr auto value = Test::checkBinaryTypeOperatorMultiple<
				Meta::TypeSet::Intersection,
			
				SetType<Type< 1>, Type< 2>, Type< 3>, Type< 4>>,
				SetType<Type< 3>, Type< 6>, Type< 7>, Type< 8>>,
				SetType<Type< 9>, Type< 1>, Type<11>, Type<12>>,
				SetType<Type<13>, Type<14>, Type< 2>, Type<16>>
			>();

			ASSERT_TRUE(value);
		}

		{ // Some same types all
			constexpr auto value = Test::checkBinaryTypeOperatorMultiple<
				Meta::TypeSet::Intersection,
			
				SetType<Type< 1>, Type< 2>, Type< 3>, Type< 4>>,
				SetType<Type< 3>, Type< 6>, Type< 7>, Type< 8>>,
				SetType<Type< 9>, Type< 3>, Type<11>, Type<12>>,
				SetType<Type<13>, Type<14>, Type< 2>, Type< 3>>
			>();

			ASSERT_TRUE(value);
		}

		{ // None same types
			constexpr auto value = Test::checkBinaryTypeOperatorMultiple<
				Meta::TypeSet::Intersection,
			
				SetType<Type< 1>, Type< 2>, Type< 3>, Type< 4>>,
				SetType<Type< 5>, Type< 6>, Type< 7>, Type< 8>>,
				SetType<Type< 9>, Type<10>, Type<11>, Type<12>>,
				SetType<Type<13>, Type<14>, Type<15>, Type<16>>
			>();

			ASSERT_TRUE(value);
		}
	}

	TEST(Meta_TypeSet_Intersection, Two) {
		#define X(type) twoTest<type>();
		#include <Test/SetTypes.xmacro>
	}

	TEST(Meta_TypeSet_Intersection, Multiple) {
		#define X(type) multipleTest<type>();
		#include <Test/SetTypes.xmacro>
	}
}
