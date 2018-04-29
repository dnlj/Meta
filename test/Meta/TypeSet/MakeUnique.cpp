// STD
#include <tuple>
#include <type_traits>

// Meta
#include <Meta/TypeSet/TypeSet.hpp>
#include <Meta/TypeSet/MakeUnique.hpp>

// Google Test
#include <gtest/gtest.h>

// Test
#include <Test/Type.hpp>


namespace {
	template<template<class...> class Operation, template<class...> class SetType>
	void singleTest() {
		{ // Empty
			constexpr auto value = std::is_same<
				Operation<
					SetType<>
				>::type,
				SetType<>
			>::value;

			ASSERT_TRUE(value);
		}

		{ // No duplicates
			constexpr auto value = std::is_same<
				Operation<
					SetType<Type<1>, Type<2>, Type<3>, Type<4>>
				>::type,
				SetType<Type<1>, Type<2>, Type<3>, Type<4>>
			>::value;

			ASSERT_TRUE(value);
		}

		{ // One duplicate (1)
			constexpr auto value = std::is_same<
				Operation<
					SetType<Type<1>, Type<1>, Type<2>, Type<3>, Type<4>>
				>::type,
				SetType<Type<1>, Type<2>, Type<3>, Type<4>>
			>::value;

			ASSERT_TRUE(value);
		}

		{ // One duplicate (2)
			constexpr auto value = std::is_same<
				Operation<
					SetType<Type<1>, Type<2>, Type<1>, Type<3>, Type<4>>
				>::type,
				SetType<Type<1>, Type<2>, Type<3>, Type<4>>
			>::value;

			ASSERT_TRUE(value);
		}

		{ // One duplicate (3)
			constexpr auto value = std::is_same<
				Operation<
					SetType<Type<1>, Type<2>, Type<3>, Type<1>, Type<4>>
				>::type,
				SetType<Type<1>, Type<2>, Type<3>, Type<4>>
			>::value;

			ASSERT_TRUE(value);
		}

		{ // One duplicate (4)
			constexpr auto value = std::is_same<
				Operation<
					SetType<Type<1>, Type<2>, Type<3>, Type<4>, Type<1>>
				>::type,
				SetType<Type<1>, Type<2>, Type<3>, Type<4>>
			>::value;

			ASSERT_TRUE(value);
		}

		{ // One duplicate (5)
			constexpr auto value = std::is_same<
				Operation<
					SetType<Type<1>, Type<1>, Type<2>, Type<1>, Type<3>, Type<1>, Type<4>, Type<1>>
				>::type,
				SetType<Type<1>, Type<2>, Type<3>, Type<4>>
			>::value;

			ASSERT_TRUE(value);
		}

		{ // Multiple duplicate (1)
			constexpr auto value = std::is_same<
				Operation<
					SetType<Type<1>, Type<1>, Type<2>, Type<2>, Type<3>, Type<3>, Type<4>, Type<4>>
				>::type,
				SetType<Type<1>, Type<2>, Type<3>, Type<4>>
			>::value;

			ASSERT_TRUE(value);
		}

		{ // Multiple duplicate (2)
			constexpr auto value = std::is_same<
				Operation<
					SetType<Type<4>, Type<1>, Type<3>, Type<2>, Type<2>, Type<3>, Type<1>, Type<4>>
				>::type,
				SetType<Type<4>, Type<1>, Type<3>, Type<2>>
			>::value;

			ASSERT_TRUE(value);
		}
	}

	TEST(Meta_TypeSet_MakeUnique, Single) {
		#define X(type) singleTest<Meta::TypeSet::MakeUnique, type>();
		#include <Test/SetTypes.xmacro>
	}
}
