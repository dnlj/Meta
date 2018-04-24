#pragma once

// STD
#include <type_traits>

// Meta
#include <Meta/TypeSet/Has.hpp>
#include <Meta/TypeSet/MakeUnique.hpp>
#include <Meta/TypeSet/Concat.hpp>

namespace Meta::TypeSet {
	// TODO: Doc
	template<class Set1, class Set2, class... Sets>
	struct Intersection;

	/** @see Intersection */
	template<
		template<class...> class Set1,
		class... Types1,
		template<class...> class Set2,
		class... Types2
	> struct Intersection<Set1<Types1...>, Set2<Types2...>>
		: MakeUnique<typename Concat<
			typename std::conditional<
				Has<Set1<Types1...>, Types2>::value,
				Set1<Types2>,
				Set1<>
			>::type...
		>::type> {
	};

	// TODO: Intersection of more than two sets
	template<class Set1, class Set2, class Set3, class... Sets>
	struct Intersection<Set1, Set2, Set3, Sets...>
		: Intersection<
			typename Intersection<Set1, Set2>::type,
			Set3,
			Sets...
		>{
	};
}
