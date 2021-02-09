#ifndef __CTUNIT__H
#define __CTUNIT__H

typedef struct {
    const char *name;
    int (*func)(void);
} Test;

typedef struct Runner {
    Test *tests;
    unsigned int tests_amount;
    unsigned int capacity;
} Runner;

void run_tests(Runner *runner);
int add_test(Runner *runner, const char *name, int(*func)(void));
Runner *cunit_new(void);

#endif