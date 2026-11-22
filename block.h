#ifndef BLOCK_H
#define BLOCK_H

#include <stddef.h>
typedef struct Block {
  unsigned char *bytes;
  size_t block_size;
  size_t bytes_held;
} Block;

Block *block_new(size_t block_size);
Block *block_from_bytes(unsigned char *bytes, size_t bytes_length,
                        size_t block_size);
void block_print(Block *block);
Block *block_apply(const Block *block1, const Block *block2,
                   unsigned char binary_byte_op(unsigned char byte1,
                                                unsigned char byte2));
#endif // !BLOCK_H
