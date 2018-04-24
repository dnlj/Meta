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
	struct IsEqual
		: std::conjunction<
			IsSuperset<Set1, Set2>,
			IsSuperset<Set2, Set1>
		> {
	};
}
