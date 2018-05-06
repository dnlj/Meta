# Meta

Meta is a header only C++ library that provides type manipulation utilities.

## Getting Started

Since Meta is header only, all that you need to do is make the `./include/` directory visible to your project.

## Running the Tests

Before we begin it should be noted that, currently, building the tests is only configured for Windows with Visual Studio (see `./build/vs_build.lua` for version details). We will also need [premake.](https://github.com/premake/premake-core)

First download and build the needed dependencies:

```Batchfile
premake5 download-deps
premake5 build-deps
```

Next generate the project files and build them:

```Batchfile
premake5 vs2017
premake5 build
```

Finally to run the tests:

```Batchfile
premake5 test
```

## Examples

`Meta::TypeSet` works for any type (or combination of types) with a parameter pack, such as `std::tuple`. In this example we will use `Meta::TypeSet::TypeSet` to represent our sets.

```C++
// Define some types
using Set1 = Meta::TypeSet::TypeSet<int, float, bool>;
using Set2 = Meta::TypeSet::TypeSet<bool, double, char>;
using Set3 = Meta::TypeSet::TypeSet<double>;
using Set4 = Meta::TypeSet::TypeSet<int, float, int, bool, int>;
using Set5 = Meta::TypeSet::TypeSet<bool, int, float>;

// Check if a set has a type
Meta::TypeSet::Has<Set1, float>::value; // true
Meta::TypeSet::Has<Set1, double>::value; // false

// Get the index of a type
Meta::TypeSet::IndexOf<Set1, int>::value; // 0
Meta::TypeSet::IndexOf<Set1, float>::value; // 1
Meta::TypeSet::IndexOf<Set1, bool>::value; // 2

// Union of two sets
Meta::TypeSet::Union<Set1, Set2>::type; // <int, float, bool, double, char>

// Difference of two sets
Meta::TypeSet::Difference<Set1, Set2>::type; // <int, float>

// Intersection of two sets
Meta::TypeSet::Intersection<Set1, Set2>::type; // <bool>

// Symmetric Difference of two sets
Meta::TypeSet::SymmetricDifference<Set1, Set2>::type; // <int, float, double, char>

// Make a set unique
Meta::TypeSet::MakeUnique<Set4>::type; // <int, float, bool>

// Check if a set is a superset of another
Meta::TypeSet::IsSuperset<Set2, Set3>::value; // true

// Check if a set is a subset of another
Meta::TypeSet::IsSubset<Set3, Set2>::value; // true

// Check if two sets are equal
Meta::TypeSet::IsEqual<Set1, Set5>::value; // true
```
