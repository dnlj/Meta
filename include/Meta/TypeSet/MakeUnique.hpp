#pragma once

// STD
#include <utility>

// Meta
#include <Meta/IndexOf.hpp>
#include <Meta/TypeSet/Concat.hpp>


namespace Meta::TypeSet {
	/**
	 * Removes duplicate types from the type list of @p Set.
	 * @tparam Set The type.
	 * @tparam I The index sequence used internally. This should be left empty.
	 */
	template<class Set, class I = void>
	struct MakeUnique;
		
	/** @see MakeUnique */
	template<template<class...> class Set, class... Types>
	struct MakeUnique<Set<Types...>, void>
		: MakeUnique<Set<Types...>, std::index_sequence_for<Types...>> {
	};

	/** @see MakeUnique */
	template<template<class...> class Set, class... Types, size_t... Indices>
	struct MakeUnique<Set<Types...>, std::index_sequence<Indices...>>
		: Concat<
			typename std::conditional<
				IndexOf<Types, Types...>::value == Indices,
				Set<Types>,
				Set<>
			>::type...
		> {;
	};
}