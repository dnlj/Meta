// STD
#include <tuple>

// Meta
#include <Meta/TypeSet/TypeSet.hpp>
#include <Meta/TypeSet/Difference.hpp>

// Google Test
#include <gtest/gtest.h>

// Test
#include <Test/Type.hpp>
#include <Test/Test.hpp>


namespace {
	template<template<class...> class Operation, template<class...> class SetType>
	void twoTest() {
		{ // All empty
			constexpr auto value = Test::checkBinaryTypeOperator<
				Operation,
			
				SetType<>,
				SetType<>,

				SetType<>
			>();

			ASSERT_TRUE(value);
		}

		{ // One empty
			constexpr auto value = Test::checkBinaryTypeOperator<
				Operation,
			
				SetType<Type<1>, Type<2>, Type<3>, Type<4>>,
				SetType<>,

				SetType<Type<1>, Type<2>, Type<3>, Type<4>>
			>();

			ASSERT_TRUE(value);
		}

		{ // One empty (2)
			constexpr auto value = Test::checkBinaryTypeOperator<
				Operation,
			
				SetType<>,
				SetType<Type<1>, Type<2>, Type<3>, Type<4>>,

				SetType<>
			>();

			ASSERT_TRUE(value);
		}

		{ // All same types
			constexpr auto value = Test::checkBinaryTypeOperator<
				Operation,
			
				SetType<Type<1>, Type<2>, Type<3>, Type<4>>,
				SetType<Type<1>, Type<2>, Type<3>, Type<4>>,

				SetType<>
			>();

			ASSERT_TRUE(value);
		}

		{ // Some same types
			constexpr auto value = Test::checkBinaryTypeOperator<
				Operation,
			
				SetType<Type<1>, Type<2>, Type<3>, Type<4>>,
				SetType<Type<3>, Type<6>, Type<1>, Type<8>>,

				SetType<Type<2>, Type<4>>
			>();

			ASSERT_TRUE(value);
		}

		{ // None same types
			constexpr auto value = Test::checkBinaryTypeOperator<
				Operation,
			
				SetType<Type<1>, Type<2>, Type<3>, Type<4>>,
				SetType<Type<5>, Type<6>, Type<7>, Type<8>>,

				SetType<Type<1>, Type<2>, Type<3>, Type<4>>
			>();

			ASSERT_TRUE(value);
		}
	}

	template<template<class...> class Operation, template<class...> class SetType>
	void multipleTest() {
		{ // All empty
			constexpr auto value = Test::checkBinaryTypeOperatorMultiple<
				Operation,
			
				SetType<>,
				SetType<>,
				SetType<>,
				SetType<>
			>();

			ASSERT_TRUE(value);
		}

		{ // Some empty
			constexpr auto value = Test::checkBinaryTypeOperatorMultiple<
				Operation,
			
				SetType<Type< 1>, Type< 2>, Type< 3>, Type< 4>>,
				SetType<>,
				SetType<>,
				SetType<>
			>();

			ASSERT_TRUE(value);
		}

		{ // Some empty (2)
			constexpr auto value = Test::checkBinaryTypeOperatorMultiple<
				Operation,
			
				SetType<Type< 1>, Type< 2>, Type< 3>, Type< 4>>,
				SetType<>,
				SetType<>,
				SetType<Type< 1>, Type< 2>, Type< 3>, Type< 4>>
			>();

			ASSERT_TRUE(value);
		}

		{ // First empty
			constexpr auto value = Test::checkBinaryTypeOperatorMultiple<
				Operation,
			
				SetType<>,
				SetType<Type< 1>, Type< 2>, Type< 3>, Type< 4>>,
				SetType<>,
				SetType<Type< 1>, Type< 2>, Type< 3>, Type< 4>>
			>();

			ASSERT_TRUE(value);
		}

		{ // All same types
			constexpr auto value = Test::checkBinaryTypeOperatorMultiple<
				Operation,
			
				SetType<Type< 1>, Type< 2>, Type< 3>, Type< 4>>,
				SetType<Type< 1>, Type< 2>, Type< 3>, Type< 4>>,
				SetType<Type< 1>, Type< 2>, Type< 3>, Type< 4>>,
				SetType<Type< 1>, Type< 2>, Type< 3>, Type< 4>>
			>();
			
			ASSERT_TRUE(value);
		}

		{ // Some same types
			constexpr auto value = Test::checkBinaryTypeOperatorMultiple<
				Operation,
			
				SetType<Type< 1>, Type< 2>, Type< 3>, Type< 4>>,
				SetType<Type< 3>, Type< 6>, Type< 7>, Type< 8>>,
				SetType<Type< 9>, Type< 1>, Type<11>, Type<12>>,
				SetType<Type<13>, Type<14>, Type< 2>, Type<16>>
			>();

			ASSERT_TRUE(value);
		}

		{ // Some same types all
			constexpr auto value = Test::checkBinaryTypeOperatorMultiple<
				Operation,
			
				SetType<Type< 1>, Type< 2>, Type< 3>, Type< 4>>,
				SetType<Type< 3>, Type< 6>, Type< 7>, Type< 8>>,
				SetType<Type< 9>, Type< 3>, Type<11>, Type<12>>,
				SetType<Type<13>, Type<14>, Type< 2>, Type< 3>>
			>();

			ASSERT_TRUE(value);
		}

		{ // None same types
			constexpr auto value = Test::checkBinaryTypeOperatorMultiple<
				Operation,
			
				SetType<Type< 1>, Type< 2>, Type< 3>, Type< 4>>,
				SetType<Type< 5>, Type< 6>, Type< 7>, Type< 8>>,
				SetType<Type< 9>, Type<10>, Type<11>, Type<12>>,
				SetType<Type<13>, Type<14>, Type<15>, Type<16>>
			>();

			ASSERT_TRUE(value);
		}
	}

	TEST(Meta_TypeSet_Difference, Two) {
		#define X(type) twoTest<Meta::TypeSet::Difference, type>();
		#include <Test/SetTypes.xmacro>
	}

	TEST(Meta_TypeSet_Difference, Multiple) {
		#define X(type) multipleTest<Meta::TypeSet::Difference, type>();
		#include <Test/SetTypes.xmacro>
	}
}
