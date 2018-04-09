#pragma once

// STD
#include <type_traits>

namespace Meta {
	/**
	* @brief 
	*/
	template<class T, class... Types>
	struct IndexOf;

	template<class T, class... Types>
	struct IndexOf<T, T, Types...>
		: std::integral_constant<size_t, 0> {
	};

	template<class T1, class T2, class... Types2>
	struct IndexOf<T1, T2, Types2...>
		: std::integral_constant<size_t, IndexOf<T1, Types2...>::value + 1> {
	};
}