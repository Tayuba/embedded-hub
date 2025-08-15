#ifndef BIT_OPS_H
#define BIT_OPS_H

#include <stdint.h>
#include <stdbool.h>

// Macro for a single bit mask
#define BIT(n) (1u << (n))

// Set specific bits in a register
static inline void set_bits_u32(volatile uint32_t *reg, uint32_t mask) {
    *reg |= mask;
}

// Clear specific bits in a register
static inline void clear_bits_u32(volatile uint32_t *reg, uint32_t mask) {
    *reg &= ~mask;
}

// Toggle specific bits in a register
static inline void toggle_bits_u32(volatile uint32_t *reg, uint32_t mask) {
    *reg ^= mask;
}

// Read a specific bit position
static inline bool read_bit_u32(uint32_t value, uint8_t pos) {
    return (value & BIT(pos)) != 0u;
}

// Write to a bitfield
static inline uint32_t write_field_u32(uint32_t value,
                                       uint32_t mask,
                                       uint8_t shift,
                                       uint32_t field_val) {
    value &= ~mask;                          // clear field
    value |= ((field_val << shift) & mask);  // set field
    return value;
}

// Read from a bitfield
static inline uint32_t read_field_u32(uint32_t value,
                                      uint32_t mask,
                                      uint8_t shift) {
    return (value & mask) >> shift;
}

#endif // BIT_OPS_H
