#pragma once

// STD
#include <type_traits>

// Google Test
#include <gtest/gtest.h>

namespace Test {
	/**
	 * Asserts that the type Operator<Set1, Set2>::type is the same as @p Correct.
	 * @tparam Operator The operator class.
	 * @tparam Set1 The first set.
	 * @tparam Set2 The second set.
	 * @tparam Correct The expected result type.
	 */
	template<template<class...> class Operator, class Set1, class Set2, class Correct>
	void binaryAssert() {
		constexpr auto value = std::is_same<
			typename Operator<Set1, Set2>::type,
			Correct
		>::value;

		ASSERT_TRUE(value);
	}

	/**
	 * Asserts that using an operator with multiple arguments has the expected result.
	 * The expected result is that the operator is applied as follows: `((Set1 op Set2) op Set3) op Set4`
	 * @tparam Operator The operator class.
	 * @tparam Set1 The first set.
	 * @tparam Set2 The second set.
	 * @tparam Set3 The third set.
	 * @tparam Set4 The fourth set.
	 */
	template<template<class...> class Operator, class Set1, class Set2, class Set3, class Set4>
	void multipleBinaryAssert() {
		constexpr auto value = std::is_same<
			typename Operator<Set1, Set2, Set3, Set4>::type,
			typename Operator<
				typename Operator<
					typename Operator<Set1, Set2>::type,
					Set3
				>::type,
				Set4
			>::type
		>::value;

		ASSERT_TRUE(value);
	}
}
