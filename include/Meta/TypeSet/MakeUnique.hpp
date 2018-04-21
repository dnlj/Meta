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
		
		template<template<class...> class SetType, class... Types>
		struct MakeUnique<SetType<Types...>, void>
			: MakeUnique<SetType<Types...>, std::index_sequence_for<Types...>> {
		};

		template<template<class...> class SetType, class... Types, size_t... Indices>
		struct MakeUnique<SetType<Types...>, std::index_sequence<Indices...>> {
			using type = typename Concat<
				typename std::conditional<
					IndexOf<Types, Types...>::value == Indices,
					SetType<Types>,
					SetType<>
				>::type...
			>::type;
		};
}