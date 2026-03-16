#include <utility>

// Small Objects Are Returned in Registers
int square(int x) {
    return x * x;
}

// Large Objects Are Returned via a Hidden Pointer
struct Big {
    long buffer[1024];
};

Big makeBig(int value) {
    Big b;
    for (int i = 0; i < 1024; ++i)
        b.buffer[i] = value + i;
    return b;
}

struct Big2 {
    long buffer[1024];
    Big2([[maybe_unused]] int value) { /* fill */ }
    Big2(const Big&) { /* copy */ }
};

// Return Value Optimization (Temporary Objects)
Big2 makeBigTemporary(int value) {
    return Big2{ value };
}

Big2 makeBigRVO(int value) {
    return Big2(value);
}

// NRVO – Named Return Value Optimization
Big2 makeBigNRVO(int value) {
    Big2 local(value);
    // maybe do some work
    return local;
}

// The `std::move` Pitfall
Big2 makeBigWithMove(int value) {
    Big2 local(value);
    return std::move(local);
}