/*
 * Some research/insight into a compiler's auto-vectorization.
 * An ADDPS instruction should be generated for the addition of four consecutive floats.
 * Inspired by "Going SIMD", https://fabiensanglard.net/revisiting_the_pathtracer/index.html
 *
 * Compilation:
 *  GCC: -O2 -Ofast
 * MSVC: /O2
 */

#include <cstdlib>

#define BLOCK_SIZE  4
#define SIZE        8

// Eins ////////////////////////////////////////////////

struct Vector {
    float data[SIZE];

    Vector operator+(const Vector& other) const;
};

Vector Vector::operator+(const Vector& other) const
{
    Vector result;
    for(int i = 0; i < SIZE; i++) {
        result.data[i] = data[i] + other.data[i];
    }
    return result;
}

// Zwei /////////////////////////////////////////////////////

template<int COUNT>
struct AddBlock {
    inline static void run(float *x, const float *a, const float *b)
    {
        constexpr int base = (SIZE/BLOCK_SIZE - COUNT)*BLOCK_SIZE;
#if 1
        for(int i = 0; i < BLOCK_SIZE; i++) {
            x[base + i] = a[base + i] + b[base + i];
        }
#else
        x[base + 0] = a[base + 0] + b[base + 0];
        x[base + 1] = a[base + 1] + b[base + 1];
        x[base + 2] = a[base + 2] + b[base + 2];
        x[base + 3] = a[base + 3] + b[base + 3];
#endif
        AddBlock<COUNT-1>::run(x, a, b);
    }
};

template<>
struct AddBlock<0> {
    inline static void run(float *, const float *, const float *)
    {
    }
};

template<int COUNT>
struct AddImpl {
    inline static void run(Vector& x, const Vector& a, const Vector& b)
    {
        constexpr int i = SIZE - COUNT;
        x.data[i] = a.data[i] + b.data[i];
        AddImpl<COUNT-1>::run(x, a, b);
    }
};

template<>
struct AddImpl<0> {
    inline static void run(Vector&, const Vector&, const Vector&)
    {
    }
};

Vector add(const Vector& a, const Vector& b)
{
    Vector c;
#if 1
    AddBlock<SIZE/BLOCK_SIZE>::run(c.data, a.data, b.data);
    AddImpl<SIZE%BLOCK_SIZE>::run(c, a, b);
#else
    AddImpl<SIZE>::run(c, a, b);
#endif
    return c;
}

// Main ////////////////////////////////////////////////////

int main(int argc, char **argv)
{
    return EXIT_SUCCESS;
}
