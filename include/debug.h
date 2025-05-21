#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <stdlib.h>

// ----------- Configuration Macros -----------

// Define DEBUG before including this header to enable debug logging/asserts
// #define DEBUG

// ----------- Runtime Assert -----------

#define ASSERT(expr) \
    do { \
        if (!(expr)) { \
            fprintf(stderr, "[ASSERT] %s:%d: Assertion failed: %s\n", \
                    __FILE__, __LINE__, #expr); \
            abort(); \
        } \
    } while (0)

#define ASSERT_MSG(expr, msg, ...) \
    do { \
        if (!(expr)) { \
            fprintf(stderr, "[ASSERT] %s:%d: " msg "\n", \
                    __FILE__, __LINE__, ##__VA_ARGS__); \
            abort(); \
        } \
    } while (0)

// ----------- Compile-time Assert -----------

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
    #define STATIC_ASSERT(cond, msg) _Static_assert(cond, msg)
#else
    // Fallback for older compilers
    #define STATIC_ASSERT(cond, msg) typedef char static_assertion_##msg[(cond) ? 1 : -1]
#endif

// ----------- Debug Logging -----------

#ifdef DEBUG

    #define DEBUG_LOG(msg, ...) \
        fprintf(stderr, "[DEBUG] %s:%d: " msg "\n", __FILE__, __LINE__, ##__VA_ARGS__)

    #define TRACE() \
        fprintf(stderr, "[TRACE] %s:%d\n", __FILE__, __LINE__)

    #define LOG_VAR(var, fmt) \
        fprintf(stderr, "[DEBUG] %s:%d: %s = " fmt "\n", __FILE__, __LINE__, #var, var)

#else

    #define DEBUG_LOG(msg, ...)
    #define TRACE()
    #define LOG_VAR(var, fmt)

#endif // DEBUG

// ----------- Panic / Fatal Error -----------

#define PANIC(msg, ...) \
    do { \
        fprintf(stderr, "[PANIC] %s:%d: " msg "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
        exit(EXIT_FAILURE); \
    } while (0)

#endif // DEBUG_H

