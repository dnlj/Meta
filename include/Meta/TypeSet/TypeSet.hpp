#pragma once

namespace Meta::TypeSet {
	/**
	 * Represents a set of the types.
	 * @tparam Types the list of types.
	 */
	template<class... Types>
	struct TypeSet {
		/** The number of types in the type list @p Types */
		constexpr static auto size = sizeof...(Types);
	};
}