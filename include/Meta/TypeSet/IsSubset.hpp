#pragma once

// Meta
#include <Meta/TypeSet/IsSuperset.hpp>

namespace Meta::TypeSet {
	/**
	 * Checks if all the types in the type list of @p Set1 are in the type list of @p Set2.
	 * The order of the types is not taken into consideration.
	 * @tparam Set1 The first set.
	 * @tparam Set2 The second set.
	 */
	template<class Set1, class Set2>
	struct IsSubset : IsSuperset<Set2, Set1> {
	};
}
