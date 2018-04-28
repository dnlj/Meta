#pragma once

// Meta
#include <Meta/IndexOf.hpp>

namespace Meta::TypeSet {
	template<class Set, class Type>
	struct IndexOf;

	template<
		template<class...> class Set,
		class... Types,
		class Type
	> struct IndexOf<Set<Types...>, Type> : Meta::IndexOf<Type, Types...> {
	};
}
