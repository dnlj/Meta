// STD
#include <tuple>
#include <type_traits>

// Meta
#include <Meta/TypeSet/TypeSet.hpp>
#include <Meta/TypeSet/Union.hpp>

// Google Test
#include <gtest/gtest.h>


// Two Unions Test
namespace {
	template<class Set1, class Set2, class Correct>
	void TwoUnions_Assert() {
		constexpr auto value = std::is_same<
			typename Meta::TypeSet::Union<Set1, Set2>::type,
			Correct
		>::value;

		ASSERT_TRUE(value);
	}

	template<template<class...> class SetType>
	void TwoUnions_Test() {
		// All same types
		TwoUnions_Assert<
			SetType<int, float, bool, double>,
			SetType<int, float, bool, double>,
			SetType<int, float, bool, double>
		>();

		// Some same types
		TwoUnions_Assert<
			SetType<int, float, bool, double>,
			SetType<int, long, bool, char>,
			SetType<int, float, bool, double, long, char>
		>();

		// None same types
		TwoUnions_Assert<
			SetType<int, float, bool, double>,
			SetType<unsigned, long, long double, char>,
			SetType<int, float, bool, double, unsigned, long, long double, char>
		>();
	}
}

// Multiple Unions Test
namespace {
	template<class Set1, class Set2, class Set3, class Set4>
	void MultipleUnions_Assert() {
		constexpr auto value = std::is_same<
			typename Meta::TypeSet::Union<Set1, Set2, Set3, Set4>::type,
			typename Meta::TypeSet::Union<
				typename Meta::TypeSet::Union<
					typename Meta::TypeSet::Union<Set1, Set2>::type,
					Set3
				>::type,
				Set4
			>::type
		>::value;

		ASSERT_TRUE(value);
	}

	template<template<class...> class SetType>
	void MultipleUnions_Test() {
		// All same types
		MultipleUnions_Assert<
			SetType<int, float, bool, double>,
			SetType<int, float, bool, double>,
			SetType<int, float, bool, double>,
			SetType<int, float, bool, double>
		>();

		// Some same types
		MultipleUnions_Assert<
			SetType<int, float, bool, double>,
			SetType<int, long, bool, char>,
			SetType<char, double, bool, int>,
			SetType<unsigned, long, long double, char>
		>();

		// None same types
		MultipleUnions_Assert<
			SetType<int, float, bool, double>,
			SetType<unsigned, long, long double, char>,
			SetType<short, unsigned char, unsigned long, unsigned short>,
			SetType<long long, unsigned long long>
		>();
	}
}

TEST(MetaTypeSetUnionTest, TwoUnions) {
	TwoUnions_Test<Meta::TypeSet::TypeSet>();
	TwoUnions_Test<std::tuple>();
}

TEST(MetaTypeSetUnionTest, MultipleUnions) {
	MultipleUnions_Test<Meta::TypeSet::TypeSet>();
	MultipleUnions_Test<std::tuple>();
}
