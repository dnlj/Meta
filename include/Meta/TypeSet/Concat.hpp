#pragma once

namespace Meta::TypeSet {
	/**
	 * Concatenates the type lists of the types in @p Types.
	 * @tparam Types The list of types.
	 */
	template<class... Types>
	struct Concat;

	/** @see Concat */
	template<
		template<class...> class Set,
		class... Types
	> struct Concat<Set<Types...>> {
		using type = Set<Types...>;
	};

	/** @see Concat */
	template<
		template<class...> class Set1,
		class... Types1,
		template<class...> class Set2,
		class... Types2
	> struct Concat<Set1<Types1...>, Set2<Types2...>> {
		using type = Set1<Types1..., Types2...>;
	};

	/** @see Concat */
	template<class Set1, class Set2, class Set3, class... Sets>
	struct Concat<Set1, Set2, Set3, Sets...>
		: Concat<
			typename Concat<Set1, Set2>::type,
			Set3,
			Sets...
		> {
	};
}
