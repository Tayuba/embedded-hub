#include "ring_buffer.h"                    

// To move an index forward by 1 
static inline size_t advance(ring_buffer_t *rb, size_t idx) { 
    idx++;                                      
    if (idx == rb->capacity) {                 
        idx = 0;                                
    }
    return idx;                                 
}

// Initialize a ring buffer to use caller provided storage
void rb_init(ring_buffer_t *rb, uint8_t *backing, size_t capacity) { 
    rb->buf      = backing;                     
    rb->capacity = capacity;                    
    rb->head     = 0;                           
    rb->tail     = 0;                           
    rb->full     = false;                       
}

// Check if the buffer currently has no data
bool rb_is_empty(const ring_buffer_t *rb) {     
    return (!rb->full) && (rb->head == rb->tail);
}

// Check if the buffer is full
bool rb_is_full(const ring_buffer_t *rb) {      
    return rb->full;                            
}

// Total number of bytes the buffer can hold
size_t rb_capacity(const ring_buffer_t *rb) {   
    return rb->capacity;                        
}

// How many bytes are currently stored (used size)
size_t rb_size(const ring_buffer_t *rb) {       
    if (rb->full){
        return rb->capacity;
    }           
    if (rb->head >= rb->tail) {
        return rb->head - rb->tail;
    }
    
    return rb->capacity - rb->tail + rb->head; 
}

// Add or Write one byte at the head 
bool rb_push(ring_buffer_t *rb, uint8_t b) {    
    if (rb->full) {                             
        return false;                           
    }

    rb->buf[rb->head] = b;                   
    rb->head = advance(rb, rb->head);
               
    if (rb->head == rb->tail) {                
        rb->full = true;                        
    }
    return true;                                
}

// Remove or Read one byte from the tail
bool rb_pop(ring_buffer_t *rb, uint8_t *out) {  
    if (rb_is_empty(rb)){
        return false;          
    } 

    *out = rb->buf[rb->tail];                   
    rb->tail = advance(rb, rb->tail);           
    rb->full = false;                           
    return true;                               
}

