#pragma once

// Meta
#include <Meta/TypeSet/Union.hpp>
#include <Meta/TypeSet/Difference.hpp>

namespace Meta::TypeSet {
	/**
	 * Makes a type set of all the types in @p Set1 and @p Set2 but not in both.
	 * @tparam Set1 The first set.
	 * @tparam Set2 The second set.
	 * @tparam Sets Any additional sets.
	 */
	template<class Set1, class Set2, class... Sets>
	struct SymmetricDifference;

	/** @see SymmetricDifference */
	template<
		template<class...> class Set1,
		class... Types1,
		template<class...> class Set2,
		class... Types2
	> struct SymmetricDifference<Set1<Types1...>, Set2<Types2...>>
		: Union<
			typename Difference<Set1<Types1...>, Set2<Types2...>>::type,
			typename Difference<Set2<Types2...>, Set1<Types1...>>::type
		> {
	};

	/** @see SymmetricDifference */
	template<class Set1, class Set2, class Set3, class... Sets>
	struct SymmetricDifference<Set1, Set2, Set3, Sets...>
		: SymmetricDifference<
			typename SymmetricDifference<Set1, Set2>::type,
			Set3,
			Sets...
		> {
	};
}
