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
			template<class...> class SetType,
			class... Types
		> struct Concat<SetType<Types...>> {
			using type = SetType<Types...>;
		};

		/** @see Concat */
		template<
			template<class...> class SetType,
			class... Types1,
			class... Types2
		> struct Concat<SetType<Types1...>, SetType<Types2...>> {
			using type = SetType<Types1..., Types2...>;
		};

		/** @see Concat */
		template<class Set1, class Set2, class Set3, class... Sets>
		struct Concat<Set1, Set2, Set3, Sets...> {
			using type = typename Concat<
				typename Concat<Set1, Set2>::type,
				Set3,
				Sets...
			>::type;
		};
}
