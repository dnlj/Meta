#pragma once

// STD
#include <type_traits>

// Meta
#include <Meta/TypeSet/Has.hpp>
#include <Meta/TypeSet/Union.hpp>

namespace Meta::TypeSet {
	/**
	 * Removes all types in the type lists of @p Set2 and @p Sets from the type list of @p Set1.
	 * @tparam Set1 The first set.
	 * @tparam Set2 The second set.
	 * @tparam Sets Any additional sets.
	 */
	template<class Set1, class Set2, class... Sets>
	struct Difference;

	/** @see Difference */
	template<
		template<class...> class Set1,
		class... Types1,
		template<class...> class Set2,
		class... Types2
	> struct Difference<Set1<Types1...>, Set2<Types2...>>
		: Union<
			Set1<>,
			typename std::conditional<
				Has<Set2<Types2...>, Types1>::value,
				Set1<>,
				Set1<Types1>
			>::type...
		> {
	};

	/** @see Difference */
	template<class Set1, class Set2, class Set3, class... Sets>
	struct Difference<Set1, Set2, Set3, Sets...>
		: Difference<
			typename Difference<Set1, Set2>::type,
			Set3,
			Sets...
		> {
	};
}
