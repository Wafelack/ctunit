# ctunit

`ctunit` is a tiny test framework for C.

## How to use it in a project

- Run `wng dependencies add https://github.com/wafelack/ctunit`.

## Documentation

### Creating a test runner

The function to create a new test unit is defined as follows:
`Runner *cunit_new(void);`

It can return `NULL` in the following cases:

- Allocating the structure fails.

Example:

```c
int main(void) {
    Runner *runner = cunit_new();
    return 0;
}
```

### Adding tests to the runner

The function to add a test to the test unit is defined as follows:
`int add_test(Runner *runner, const char *name, int(*func)(void));`

Error codes:

-  0: Success.
- -1: Failed to allocate space for the new tests array.
- -2: Failed to allocate space for the new test.

Example:

```c

int a_random_test(void) {
    return 1 - 1;
}

int main(void) {
    Runner *runner = cunit_new();
    int status = add_test(runner, "a_random_test", &a_random_test);
    if (status != 0) {
        printf("Failed to add test.\n");
        return -1;
    }
    return 0;
}
```

### Running tests

The function to run tests is defined as follows:
`void run_tests(Runner *runner);`

Example:

```c

int a_random_test(void) {
    return 1 - 1;
}

int a_failing_test(void) {
    return 1;
}

int main(void) {
    Runner *runner = cunit_new();
    int status = add_test(runner, "a_random_test", &a_random_test);
    if (status != 0) {
        printf("Failed to add test.\n");
        return -1;
    }
    status = add_test(runner, "a_failing_test", &a_failing_test);
    run_tests(runner);
    return 0;
}
```
