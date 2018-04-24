// STD
#include <tuple>
#include <type_traits>

// Meta
#include <Meta/TypeSet/TypeSet.hpp>
#include <Meta/TypeSet/Intersection.hpp>

// Google Test
#include <gtest/gtest.h>


// Two Intersections Test
namespace {
	template<class Set1, class Set2, class Correct>
	void TwoIntersections_Assert() {
		constexpr auto value = std::is_same<
			typename Meta::TypeSet::Intersection<Set1, Set2>::type,
			Correct
		>::value;

		ASSERT_TRUE(value);
	}

	template<template<class...> class SetType>
	void TwoIntersections_Test() {
		// All same types
		TwoIntersections_Assert<
			SetType<int, float, bool, double>,
			SetType<int, float, bool, double>,
			SetType<int, float, bool, double>
		>();

		// Some same types
		TwoIntersections_Assert<
			SetType<int, float, bool, double>,
			SetType<int, long, bool, char>,
			SetType<int, bool>
		>();
	}
}

// Multiple Intersections Test
namespace {
	template<class Set1, class Set2, class Set3, class Set4>
	void MultipleIntersections_Assert() {
		constexpr auto value = std::is_same<
			typename Meta::TypeSet::Intersection<Set1, Set2, Set3, Set4>::type,
			typename Meta::TypeSet::Intersection<
				typename Meta::TypeSet::Intersection<
					typename Meta::TypeSet::Intersection<Set1, Set2>::type,
					Set3
				>::type,
				Set4
			>::type
		>::value;

		ASSERT_TRUE(value);
	}

	template<template<class...> class SetType>
	void MultipleIntersections_Test() {
		// All same types
		MultipleIntersections_Assert<
			SetType<int, float, bool, double>,
			SetType<int, float, bool, double>,
			SetType<int, float, bool, double>,
			SetType<int, float, bool, double>
		>();

		// Some same types
		MultipleIntersections_Assert<
			SetType<int, float, bool, double>,
			SetType<int, long, bool, char>,
			SetType<char, double, bool, int>,
			SetType<char, double, float, int>
		>();
	}
}

TEST(MetaTypeSetIntersectionTest, TwoIntersections) {
	TwoIntersections_Test<Meta::TypeSet::TypeSet>();
	TwoIntersections_Test<std::tuple>();
}

TEST(MetaTypeSetIntersectionTest, MultipleIntersections) {
	MultipleIntersections_Test<Meta::TypeSet::TypeSet>();
	MultipleIntersections_Test<std::tuple>();
}
