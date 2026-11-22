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
#endif // !BLOCK_H
