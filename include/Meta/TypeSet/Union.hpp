#pragma once

// Meta
#include <Meta/TypeSet/MakeUnique.hpp>
#include <Meta/TypeSet/Concat.hpp>

namespace Meta::TypeSet {
	/**
	 * Make a union of the sets @p Sets.
	 * Duplicate types are removed.
	 * @tparam Sets The list of type sets to union.
	 */
	template<class... Sets>
	struct Union : MakeUnique<typename Concat<Sets...>::type> {
	};
}
