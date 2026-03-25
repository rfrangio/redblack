# redblack

Small C++ red-black tree implementation with a simple benchmark driver and an assertion-based test program.

## Layout

- `redblack.h`: public template declarations
- `redblack.tpp`: template implementation included by `redblack.h`
- `main.cpp`: benchmark-style driver
- `tests.cpp`: basic functional tests
- `Makefile`: build and test targets

## API

`RedBlackTree<T>` stores raw `T*` values and uses a caller-supplied comparator:

```cpp
template<typename T>
int cmp(T *a, T *b)
{
    if (*a == *b)
        return 0;
    return *a < *b ? -1 : 1;
}

RedBlackTree<uint32_t> tree(cmp);
```

Public operations:

- `Insert(T*)`
- `Lookup(T*)`
- `Minimum()`
- `Maximum()`
- `Delete(T*)`
- `RemoveMaximum()`
- `NodeCount()`
- `GetSubtreeDepths(int*, int*)`

## Ownership

The tree stores pointers, not values.

- If an insert succeeds, the tree owns the inserted pointer.
- `Delete()` and `RemoveMaximum()` return ownership of the removed pointer to the caller.
- If `Insert()` returns `0` for a duplicate key, the caller still owns that pointer and must free it.
- The destructor deletes any payloads still held by the tree.

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
- `main.cpp` is a stress/benchmark program, not a lightweight example. It inserts `10,000,000` values by default.
