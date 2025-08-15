#ifndef RING_BUFFER_H                      
#define RING_BUFFER_H

#include <stdint.h>                           
#include <stdbool.h>                          
#include <stddef.h>                           

/* A single-producer or single-consumer byte ring buffer (circular or Queue).
    - No dynamic allocation (caller provides storage).
*/
typedef struct {
    uint8_t *buf;                             
    size_t   capacity;                       
    size_t   head;                            
    size_t   tail;                            
    bool     full;                            
} ring_buffer_t;

/* Initialize a ring buffer with external storage.
    rb       : pointer to the ring buffer control block
    backing  : pointer to the byte array used as storage
    capacity : number of elements in 'backing' (array length)
*/
void   rb_init(ring_buffer_t *rb, uint8_t *backing, size_t capacity);

/* Query whether the buffer has no readable data.
    Returns true  → empty
            false → has at least one byte to read
*/
bool   rb_is_empty(const ring_buffer_t *rb);

/* Query whether the buffer cannot accept more data.
    Returns true  → full
            false → has at least one free slot
*/
bool   rb_is_full(const ring_buffer_t *rb);

// Return the fixed capacity (maximum storable bytes).
size_t rb_capacity(const ring_buffer_t *rb);

// Return the current number of stored bytes (used size).
size_t rb_size(const ring_buffer_t *rb);

/* Push (enqueue or add or write) one byte into the buffer.
    Returns true  → success
            false → failed because buffer was full
*/
bool   rb_push(ring_buffer_t *rb, uint8_t b);

/* Pop (dequeue, or remove or read) one byte from the buffer into *out.
    Returns true  → success; *out contains the byte
            false → failed because buffer was empty
*/
bool   rb_pop(ring_buffer_t *rb, uint8_t *out);

#endif // RING_BUFFER_H               
