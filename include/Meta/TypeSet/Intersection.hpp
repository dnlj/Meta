#pragma once

// STD
#include <type_traits>

// Meta
#include <Meta/TypeSet/Has.hpp>
#include <Meta/TypeSet/Union.hpp>

namespace Meta::TypeSet {
	/**
	 * Gets the common types form the type lists of @p Set1, @p Set2, and @p Sets.
	 * @tparam Set1 The first set.
	 * @tparam Set2 The second set.
	 * @tparam Sets Any additional sets.
	 */
	template<class Set1, class Set2, class... Sets>
	struct Intersection;

	/** @see Intersection */
	template<
		template<class...> class Set1,
		class... Types1,
		template<class...> class Set2,
		class... Types2
	> struct Intersection<Set1<Types1...>, Set2<Types2...>>
		: Union<
			Set1<>,
			typename std::conditional<
				Has<Set1<Types1...>, Types2>::value,
				Set1<Types2>,
				Set1<>
			>::type...
		> {
	};

	/** @see Intersection */
	template<class Set1, class Set2, class Set3, class... Sets>
	struct Intersection<Set1, Set2, Set3, Sets...>
		: Intersection<
			typename Intersection<Set1, Set2>::type,
			Set3,
			Sets...
		> {
	};
}
