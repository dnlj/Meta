#pragma once

// STD
#include <type_traits>

namespace Meta::TypeSet {
	/**
	 * Checks if the type list of @p Set contains the type @p Type.
	 * @tparam Set The set to check.
	 * @tparam Type The type to check for.
	 */
	template<class Set, class Type>
	struct Has;

	/** @see Has */
	template<
		template<class...> class Set,
		class... Types,
		class Type
	> struct Has<Set<Types...>, Type>
		: std::disjunction<
			std::is_same<
				Types,
				Type
			>...
		> {
	};
}
