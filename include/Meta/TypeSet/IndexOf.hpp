#pragma once

// Meta
#include <Meta/IndexOf.hpp>

namespace Meta::TypeSet {
	template<class Type, class Set>
	struct IndexOf;

	template<
		class Type,
		template<class...> class Set,
		class... Types
	> struct IndexOf<Type, Set<Types...>> : Meta::IndexOf<Type, Types...> {
	};
}
