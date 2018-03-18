#ifndef __BITMASK__
#define __BITMASK__

#include "Globals.h"
#include <cstdint>

class Bitmask
{
private:
    uint16_t mask;

    static const uint16_t zero = (uint16_t)0;
    static const uint16_t one = (uint16_t)1;
public:
    Bitmask() :mask(zero) {};
    ~Bitmask() {};

    void put_a_one(uint pos);
    void put_a_zero(uint pos);
    bool get(uint pos);

};

inline void Bitmask::put_a_one(uint pos)
{
    mask |= one << pos;
}

inline void Bitmask::put_a_zero(uint pos)
{
    mask &= ~(one << pos);
}

inline bool Bitmask::get(uint pos)
{
    return (mask >> pos) & 1u;
}

// All bitwise operations extracted from:
// https://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit
#endif
