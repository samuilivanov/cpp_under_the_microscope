void func1() {
  int x = 10;
  int &lref = x;   // lvalue reference – binds to x
  int &&rref = 20; // rvalue reference – binds to temporary
}

void func2() {

  int x = 10;
  auto &&r1 = x;  // what is this?
  auto &&r2 = 20; // and this?
}

#include <iostream>
struct Widget {
  Widget() = default;
  Widget(const Widget &) { std::cout << "Copy\n"; }
  Widget(Widget &&) { std::cout << "Move\n"; }
};

template <typename T> void relay(T &&arg) {
  Widget local(std::forward<T>(arg));
}

int main() {
  Widget w;

  Widget &&rref = std::move(w); // rref is widget&&

  Widget a = rref;            // copy, because rref is an lvalue here
  Widget b = std::move(rref); // move, now we actually move
}