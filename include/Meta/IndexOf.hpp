#pragma once

// STD
#include <type_traits>

namespace Meta {
	/**
	 * Gets the index of the first occurrence of @p T in the type list @p Types.
	 * @tparam T The type to get the index of.
	 * @tparam Types The list of types.
	 */
	template<class T, class... Types>
	struct IndexOf;

	/** @see IndexOf */
	template<class T, class... Types>
	struct IndexOf<T, T, Types...>
		: std::integral_constant<size_t, 0> {
	};

	/** @see IndexOf */
	template<class T, class U, class... Types>
	struct IndexOf<T, U, Types...>
		: std::integral_constant<size_t, IndexOf<T, Types...>::value + 1> {
	};
}