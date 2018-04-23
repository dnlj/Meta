#pragma once

// STD
#include <type_traits>

// Meta
#include <Meta/TypeSet/Has.hpp>

namespace Meta::TypeSet {
	// TODO: Doc
	template<class Set1, class Set2>
	struct IsSuperset;

	template<
		template<class...> class Set1,
		class... Types1,
		template<class...> class Set2,
		class... Types2
	> struct IsSuperset<Set1<Types1...>, Set2<Types2...>>
		: std::conjunction<
			Has<Set1<Types1...>, Types2>...
		> {
	};
}
