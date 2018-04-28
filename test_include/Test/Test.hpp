#pragma once

// STD
#include <type_traits>

// Meta
#include <Meta/TypeSet/IsEqual.hpp>

// Google Test
#include <gtest/gtest.h>

namespace Test {
	/**
	 * Checks if the type Operator<Set1, Set2>::type is the same as @p Correct.
	 * @tparam Operator The operator class.
	 * @tparam Set1 The first set.
	 * @tparam Set2 The second set.
	 * @tparam Correct The expected result type.
	 * @return The value of the comparison.
	 */
	template<template<class...> class Operator, class Set1, class Set2, class Correct>
	constexpr bool checkBinaryTypeOperator() noexcept {
		return Meta::TypeSet::IsEqual<
			typename Operator<Set1, Set2>::type,
			Correct
		>::value;
	}

	/**
	 * Checks if an operator with multiple arguments has the expected result.
	 * The expected result is that the operator is applied as follows: `((Set1 op Set2) op Set3) op Set4`
	 * @tparam Operator The operator class.
	 * @tparam Set1 The first set.
	 * @tparam Set2 The second set.
	 * @tparam Set3 The third set.
	 * @tparam Set4 The fourth set.
	 * @return The value of the comparison.
	 */
	template<template<class...> class Operator, class Set1, class Set2, class Set3, class Set4>
	constexpr bool checkBinaryTypeOperatorMultiple() noexcept {
		return Meta::TypeSet::IsEqual<
			typename Operator<Set1, Set2, Set3, Set4>::type,
			typename Operator<
				typename Operator<
					typename Operator<Set1, Set2>::type,
					Set3
				>::type,
				Set4
			>::type
		>::value;
	}
}
