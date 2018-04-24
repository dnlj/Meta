#pragma once

// STD
#include <type_traits>

// Meta
#include <Meta/TypeSet/IsSuperset.hpp>

namespace Meta::TypeSet {
	/**
	 * Checks if the type lists of @p Set1 and @p Set2 contain the same types.
	 * The order of the types is not taken into consideration.
	 * @tparam Set1 The first set.
	 * @tparam Set2 The second set.
	 */
	template<class Set1, class Set2>
	struct IsEqual;

	/** @see Equals */
	template<
		template<class...> class Set1,
		class... Types1,
		template<class...> class Set2,
		class... Types2
	> struct IsEqual<Set1<Types1...>, Set2<Types2...>>
		: std::conjunction<
			IsSuperset<Set1<Types1...>, Set2<Types2...>>,
			IsSuperset<Set2<Types2...>, Set1<Types1...>>
		> {
	};
}
