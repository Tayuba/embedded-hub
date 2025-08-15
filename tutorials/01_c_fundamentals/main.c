#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include "bit_ops.h"
#include "ring_buffer.h"

int main(void) {
    // --- bit ops tests ---
    {
        uint32_t reg = 0;
        set_bits_u32(&reg, BIT(3) | BIT(7));
        assert(read_bit_u32(reg, 3) == 1);
        assert(read_bit_u32(reg, 7) == 1);

        clear_bits_u32(&reg, BIT(3));
        assert(read_bit_u32(reg, 3) == 0);

        toggle_bits_u32(&reg, BIT(7));
        assert(read_bit_u32(reg, 7) == 0);

        const uint32_t MASK = 0x000000F0u;                                     
        reg = write_field_u32(reg, MASK, 4, 0xA); 
        assert(read_field_u32(reg, MASK, 4) == 0xA);
    }

    // --- ring buffer tests ---
    {
        uint8_t storage[8];
        ring_buffer_t rb;
        rb_init(&rb, storage, sizeof(storage));

        assert(rb_is_empty(&rb));
        for (uint8_t i = 0; i < 8; ++i) {
            assert(rb_push(&rb, i) == true);
        }
        assert(rb_is_full(&rb));
        // cannot push when full
        assert(rb_push(&rb, 99) == false);

        // pop all items
        for (uint8_t i = 0; i < 8; ++i) {
            uint8_t out = 0xFF;
            assert(rb_pop(&rb, &out) == true);
            assert(out == i);
        }
        assert(rb_is_empty(&rb));

        // wrap-around behavior
        assert(rb_push(&rb, 42));
        assert(rb_push(&rb, 43));
        uint8_t out;
        assert(rb_pop(&rb, &out) && out == 42);
        assert(rb_pop(&rb, &out) && out == 43);
    }

    printf("Lesson 01 tests passed.\\n");
    return 0;
}
