#include <cstdio>
#include <string>
#include <utility>
#include <vector>

struct Resource {
  Resource() { std::puts("Constructed"); }
  Resource(const Resource &) { std::puts("Copied"); }
  Resource(Resource &&) noexcept { std::puts("Moved"); }
};

void observe() {
  Resource r1;
  Resource r2 = r1;            // r1 is an lvalue
  Resource r3 = std::move(r1); // std::move makes r1 an xvalue
}

void example() {
  std::vector<int> v1(1000, 42); // A vector with 1000 elements

  std::vector<int> v2 = v1;            // Copy v1 into v2
  std::vector<int> v3 = std::move(v1); // "Move" v1 into v3
}

void use(std::string &&s);

// Version A
void with_cast(std::string &s) { use(static_cast<std::string &&>(s)); }

// Version B
void with_move(std::string &s) { use(std::move(s)); }