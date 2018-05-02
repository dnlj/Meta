// STD
#include <tuple>

// Meta
#include <Meta/TypeSet/TypeSet.hpp>
#include <Meta/TypeSet/IsStrictSubset.hpp>

// Google Test
#include <gtest/gtest.h>

// Test
#include <Test/Type.hpp>
#include <Test/Test.hpp>


namespace {
	template<template<class...> class Operation, template<class...> class SetType>
	void twoTest() {
		{ // A.size > B.size; one empty
			constexpr auto value = Operation<
				SetType<Type<1>, Type<2>, Type<3>, Type<4>>,
				SetType<>
			>::value;

			ASSERT_FALSE(value);
		}

		{ // A.size > B.size; same types, same order
			constexpr auto value = Operation<
				SetType<Type<1>, Type<2>, Type<3>, Type<4>>,
				SetType<Type<1>, Type<2>>
			>::value;

			ASSERT_FALSE(value);
		}

		{ // A.size > B.size; same types, different order
			constexpr auto value = Operation<
				SetType<Type<1>, Type<2>, Type<3>, Type<4>>,
				SetType<Type<2>, Type<1>>
			>::value;

			ASSERT_FALSE(value);
		}

		{ // A.size > B.size; different types
			constexpr auto value = Operation<
				SetType<Type<1>, Type<2>, Type<3>, Type<4>>,
				SetType<Type<5>, Type<6>>
			>::value;

			ASSERT_FALSE(value);
		}

		{ // A.size > B.size; some types
			constexpr auto value = Operation<
				SetType<Type<1>, Type<2>, Type<3>, Type<4>>,
				SetType<Type<5>, Type<3>>
			>::value;

			ASSERT_FALSE(value);
		}



		{ // A.size == B.size; both empty
			constexpr auto value = Operation<
				SetType<>,
				SetType<>
			>::value;

			ASSERT_FALSE(value);
		}

		{ // A.size == B.size; same types, same order
			constexpr auto value = Operation<
				SetType<Type<1>, Type<2>, Type<3>, Type<4>>,
				SetType<Type<1>, Type<2>, Type<3>, Type<4>>
			>::value;

			ASSERT_FALSE(value);
		}

		{ // A.size == B.size; same types, different order
			constexpr auto value = Operation<
				SetType<Type<1>, Type<2>, Type<3>, Type<4>>,
				SetType<Type<4>, Type<3>, Type<2>, Type<1>>
			>::value;

			ASSERT_FALSE(value);
		}

		{ // A.size == B.size; different types
			constexpr auto value = Operation<
				SetType<Type<1>, Type<2>, Type<3>, Type<4>>,
				SetType<Type<5>, Type<6>, Type<7>, Type<8>>
			>::value;

			ASSERT_FALSE(value);
		}

		{ // A.size == B.size; some types
			constexpr auto value = Operation<
				SetType<Type<1>, Type<2>, Type<3>, Type<4>>,
				SetType<Type<5>, Type<3>, Type<2>, Type<8>>
			>::value;

			ASSERT_FALSE(value);
		}



		{ // A.size < B.size; one empty
			constexpr auto value = Operation<
				SetType<>,
				SetType<Type<1>, Type<2>, Type<3>, Type<4>>
			>::value;

			ASSERT_TRUE(value);
		}

		{ // A.size < B.size; same types, same order
			constexpr auto value = Operation<
				SetType<Type<1>, Type<2>>,
				SetType<Type<1>, Type<2>, Type<3>, Type<4>>
			>::value;

			ASSERT_TRUE(value);
		}

		{ // A.size < B.size; same types, different order
			constexpr auto value = Operation<
				SetType<Type<2>, Type<1>>,
				SetType<Type<1>, Type<2>, Type<3>, Type<4>>
			>::value;

			ASSERT_TRUE(value);
		}

		{ // A.size < B.size; different types
			constexpr auto value = Operation<
				SetType<Type<5>, Type<6>>,
				SetType<Type<1>, Type<2>, Type<3>, Type<4>>
			>::value;

			ASSERT_FALSE(value);
		}

		{ // A.size < B.size; some types
			constexpr auto value = Operation<
				SetType<Type<5>, Type<6>, Type<2>, Type<3>>,
				SetType<Type<1>, Type<2>, Type<3>, Type<4>>
			>::value;

			ASSERT_FALSE(value);
		}
	}

	TEST(Meta_TypeSet_IsStrictSubset, Two) {
		#define X(type) twoTest<Meta::TypeSet::IsStrictSubset, type>();
		#include <Test/SetTypes.xmacro>
	}
}
