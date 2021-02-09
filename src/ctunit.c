#include <stdlib.h>
#include <stdio.h>
#include "ctunit.h"

static void _print_success(const char *name) {
    #ifdef _WIN32
        printf("%s... ok\n", name);
    #else
        printf("%s... \033[0;32mok\033[0m\n", name);
    #endif
}

static void _print_failed(const char *name) {
    #ifdef _WIN32
        printf("%s... failed\n", name);
    #else
        printf("%s... \033[0;31mfailed\033[0m\n", name);
    #endif
}

static void _global_status(unsigned int failed, unsigned int total) {
    if (failed == 0) {
        #ifdef _WIN32
            printf("\ntest result: ok. %u passed; 0 failed.\n", total);
        #else
            printf("\ntest result: \033[0;32mfailed\033[0m. %u passed; 0 failed.\n", total);
        #endif
    } else {
        #ifdef _WIN32
            printf("\ntest result: failed; %u passed. %u failed.\n", total - failed, failed);
        #else
            printf("\ntest result: \033[0;31mfailed\033[0m. %u passed; %u failed.\n", total - failed, failed);
        #endif
    }
}

void run_tests(Runner *runner) {
    unsigned int failed = 0;
    unsigned int total = runner->tests_amount;
    printf("running %u tests\n", total);

    for (unsigned int i = 0; i < runner->tests_amount; i++) {
        Test current = runner->tests[i];
        
        int res = current.func();

        if (res == 0) {
            _print_success(current.name);
        } else {
            _print_failed(current.name);
            failed++;
        }

    }
    
    _global_status(failed, total);

}



int add_test(Runner *runner, const char *name, int(*func)(void)) {
    Test *to_add = malloc(sizeof(Test));
    if (to_add == NULL) {
        return -2;
    }
    to_add->name = name;
    to_add->func = func;

    if (runner->tests_amount + 1 >= runner->capacity) {
        Test *new_tests = malloc(sizeof(Test) * (runner->capacity * 2));

        if (new_tests == NULL) {
            free(to_add);
            return -1;
        }

        runner->capacity *= 2;

        for (unsigned int i = 0; i < runner->tests_amount;i++) {
            new_tests[i] = runner->tests[i];
        }
        free(runner->tests);
        runner->tests = new_tests;
    }

    runner->tests[runner->tests_amount] = *to_add;
    runner->tests_amount++;

    return 0;
}

Runner *cunit_new(void) {
    Runner *runner = malloc(sizeof(Runner));
    if (runner == NULL) {
        return NULL;
    }
    runner->tests_amount = 0;
    runner->tests = NULL;    
    runner->capacity = 1;
    return runner;
}