#include <stdio.h>

// X-Macros: Data-Driven Code Generation
#define COLOR_LIST                                                             \
  X(Red)                                                                       \
  X(Green)                                                                     \
  X(Blue)

// Generate enum
#define X(name) name,
enum Color { COLOR_LIST };
#undef X

// Generate string array
#define X(name) #name,
const char *color_names[] = {COLOR_LIST};
#undef X

// Token Pasting: Fake Generics

#define GENERIC_MAX(type)                                                      \
  type max_##type(type a, type b) { return (a > b) ? a : b; }

GENERIC_MAX(int) // expands to int max_int(int a, int b) { ... }
GENERIC_MAX(double)

// ASSERT Macro: Context Capture

#define ASSERT(cond)                                                           \
  do {                                                                         \
    if (!(cond))                                                               \
      printf("Assertion failed: %s at %s:%d\n", #cond, __FILE__, __LINE__);    \
  } while (0)

  
// Variadic Macros and VA_OPT

#define LOG(format, ...) printf("Log: " format, __VA_ARGS__)

#define LOG_SAFE(format, ...) printf("Log: " format __VA_OPT__(, ) __VA_ARGS__)


// Macro Recursional: The REPEAT Trick
#define REPEAT_1(X) X(1)
#define REPEAT_2(X) REPEAT_1(X) X(2)
#define REPEAT_3(X) REPEAT_2(X) X(3)
#define REPEAT(N, X) REPEAT_##N(X)

// Example usage: generate array indices
#define DECLARE_ELEM(i) int elem##i;
REPEAT(3, DECLARE_ELEM)   // expands to int elem1; int elem2; int elem3;

// Conditional Arithmetic

#define VERSION 203

#if VERSION >= 200 && (VERSION % 100) < 50
#define FEATURE_NEW 1
#else
#define FEATURE_NEW 0
#endif
// Add:
#if FEATURE_NEW
#warning "New feature enabled"
#endif

// _Pragma: Injecting Compiler Instructions

#define SUPPRESS_WARNING(w) _Pragma(#w)
#define NO_UNUSED_VAR SUPPRESS_WARNING(GCC diagnostic ignored "-Wunused-variable")
NO_UNUSED_VAR
int unused;

int main() {
  ASSERT(1 == 0);
  LOG("Hello\n");
}
