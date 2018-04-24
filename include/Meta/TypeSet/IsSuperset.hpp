#pragma once

// STD
#include <type_traits>

// Meta
#include <Meta/TypeSet/Has.hpp>

namespace Meta::TypeSet {
	/**
	 * Checks if all the types in the type list of @p Set2 are in the type list of @p Set1.
	 * The order of the types is not taken into consideration.
	 * @tparam Set1 The first set.
	 * @tparam Set2 The second set.
	 */
	template<class Set1, class Set2>
	struct IsSuperset;

	/** @see IsSuperset */
	template<
		template<class...> class Set1,
		class... Types1,
		template<class...> class Set2,
		class... Types2
	> struct IsSuperset<Set1<Types1...>, Set2<Types2...>>
		: std::conjunction<
			Has<Set1<Types1...>, Types2>...
		> {
	};
}
