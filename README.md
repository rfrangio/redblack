# redblack

Small C++ red-black tree implementation with inline value storage, a benchmark driver, and an assertion-based test program.

## Layout

- `redblack.h`: public template declarations
- `redblack.tpp`: template implementation included by `redblack.h`
- `main.cpp`: benchmark-style driver
- `tests.cpp`: basic functional tests
- `Makefile`: build and test targets

## API

`RedBlackTree<T, Compare>` stores values inline in each node and uses a comparator type, defaulting to `std::less<T>`:

```cpp
RedBlackTree<uint32_t> tree;
tree.Insert(10);
```

Public operations:

- `Insert(const T&)`
- `Lookup(const T&)`
- `Minimum()`
- `Maximum()`
- `Delete(const T&, T*)`
- `RemoveMaximum(T*)`
- `NodeCount()`
- `GetSubtreeDepths(int*, int*)`

## Build

Build the benchmark binary:

```sh
make
```

This produces `rb`.

## Test

Run the test suite:

```sh
make test
```

The test binary is written to `/tmp/rb_tests` because some environments may not allow writing additional binaries in the project directory.

## Notes

- `Minimum()` and `Maximum()` return `0` when the tree is empty.
- `Delete()` and `RemoveMaximum()` return `false` when no value is removed.
- `main.cpp` is a stress/benchmark program, not a lightweight example. It inserts `10,000,000` values by default.
