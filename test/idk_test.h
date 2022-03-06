#ifndef IDK_TEST_H
#define IDK_TEST_H

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

typedef int (*idk_test_function_t)(void);

static int assertions = 0;
static int fails = 0;
static char fileName[255];

int idk_assert(
    const char *file, const char *function, int line, const char *expression,
    int result);
int idk_runall(const idk_test_function_t tests[], int count);

#define IDK_SUCCESS 1
#define IDK_FAIL 0

#define IDK_NUMARGS(...)                                                      \
    (sizeof((idk_test_function_t[]){__VA_ARGS__}) /                           \
     sizeof(idk_test_function_t))

#define IDK_TEST(name) static int name(void)

#define IDK_ASSERT(expression)                                                \
    if (idk_assert(                                                           \
            __FILE__, __FUNCTION__, __LINE__, #expression, (expression)) !=   \
        0)                                                                    \
    return IDK_FAIL

#define IDK_MAIN(...)                                                         \
    int main()                                                                \
    {                                                                         \
        const idk_test_function_t all_tests[] = {__VA_ARGS__};                \
        int count = IDK_NUMARGS(__VA_ARGS__);                                 \
        return idk_runall(all_tests, count);                                  \
    }

int idk_runall(const idk_test_function_t tests[], int count)
{
    int errors = 0;

    for (int i = 0; i < count; ++i)
    {
        if (tests[i]() == IDK_FAIL)
        {
            errors++;
        }
    }

    printf(
        "%d/%d assertions were successfully!\n", assertions - fails,
        assertions);
    printf("%d/%d tests completed successfully!", count - errors, count);
    return errors;
}

int idk_assert(
    const char *file, const char *function, int line, const char *expression,
    int result)
{
    assertions++;
    const char *start = strchr(file, '.');
    strcpy_s(fileName, sizeof(fileName), start ? start + 2 : file);

    if (result == 0)
    {
        fails++;
        printf(
            "FAILED: %s:%d \"%s\": %s\n", fileName, line, function,
            expression);
        return 1;
    }

    printf("SUCCESS: %s:%d \"%s\"\n", fileName, line, function);
    return 0;
}

#endif
