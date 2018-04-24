#pragma once

// Meta
#include <Meta/TypeSet/IsEqual.hpp>

namespace Meta::TypeSet {
	/**
	 * Checks if type list of @p Set1 is a superset but not equal to the type list of @p Set2.
	 * The order of the types is not taken into consideration.
	 * @tparam Set1 The first set.
	 * @tparam Set2 The second set.
	 */
	template<class Set1, class Set2>
	struct IsStrictSuperset
		: std::conjunction<
			IsSuperset<Set1, Set2>,
			std::negation<IsEqual<Set1, Set2>>
		> {
	};
}
