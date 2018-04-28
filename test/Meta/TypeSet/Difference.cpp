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
	template<template<class...> class SetType>
	void twoTest() {
		// Empty
		Test::binaryAssert<
			Meta::TypeSet::Difference,
			
			SetType<>,
			SetType<>,

			SetType<>
		>();

		// All same types
		Test::binaryAssert<
			Meta::TypeSet::Difference,
			
			SetType<Type<1>, Type<2>, Type<3>, Type<4>>,
			SetType<Type<1>, Type<2>, Type<3>, Type<4>>,

			SetType<>
		>();

		// Some same types
		Test::binaryAssert<
			Meta::TypeSet::Difference,
			
			SetType<Type<1>, Type<2>, Type<3>, Type<4>>,
			SetType<Type<3>, Type<6>, Type<1>, Type<8>>,

			SetType<Type<2>, Type<4>>
		>();

		// None same types
		Test::binaryAssert<
			Meta::TypeSet::Difference,
			
			SetType<Type<1>, Type<2>, Type<3>, Type<4>>,
			SetType<Type<5>, Type<6>, Type<7>, Type<8>>,

			SetType<Type<1>, Type<2>, Type<3>, Type<4>>
		>();
	}

	template<template<class...> class SetType>
	void multipleTest() {
		// Empty
		Test::multipleBinaryAssert<
			Meta::TypeSet::Difference,
			
			SetType<>,
			SetType<>,
			SetType<>,
			SetType<>
		>();

		// All same types
		Test::multipleBinaryAssert<
			Meta::TypeSet::Difference,
			
			SetType<Type< 1>, Type< 2>, Type< 3>, Type< 4>>,
			SetType<Type< 1>, Type< 2>, Type< 3>, Type< 4>>,
			SetType<Type< 1>, Type< 2>, Type< 3>, Type< 4>>,
			SetType<Type< 1>, Type< 2>, Type< 3>, Type< 4>>
		>();

		// Some same types
		Test::multipleBinaryAssert<
			Meta::TypeSet::Difference,
			
			SetType<Type< 1>, Type< 2>, Type< 3>, Type< 4>>,
			SetType<Type< 3>, Type< 6>, Type< 7>, Type< 8>>,
			SetType<Type< 9>, Type< 1>, Type<11>, Type<12>>,
			SetType<Type<13>, Type<14>, Type< 2>, Type<16>>
		>();

		// Some same types all
		Test::multipleBinaryAssert<
			Meta::TypeSet::Intersection,
			
			SetType<Type< 1>, Type< 2>, Type< 3>, Type< 4>>,
			SetType<Type< 3>, Type< 6>, Type< 7>, Type< 8>>,
			SetType<Type< 9>, Type< 3>, Type<11>, Type<12>>,
			SetType<Type<13>, Type<14>, Type< 2>, Type< 3>>
		>();

		// None same types
		Test::multipleBinaryAssert<
			Meta::TypeSet::Difference,
			
			SetType<Type< 1>, Type< 2>, Type< 3>, Type< 4>>,
			SetType<Type< 5>, Type< 6>, Type< 7>, Type< 8>>,
			SetType<Type< 9>, Type<10>, Type<11>, Type<12>>,
			SetType<Type<13>, Type<14>, Type<15>, Type<16>>
		>();
	}

	TEST(Meta_TypeSet_Difference, Two_Differences) {
		#define X(type) twoTest<type>();
		#include <Test/SetTypes.xmacro>
	}

	TEST(Meta_TypeSet_Difference, Multiple_Differences) {
		#define X(type) multipleTest<type>();
		#include <Test/SetTypes.xmacro>
	}
}
