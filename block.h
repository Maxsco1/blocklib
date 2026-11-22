#ifndef BLOCK_H
#define BLOCK_H

#include <stddef.h>
typedef struct Block {
  unsigned char *bytes;
  size_t block_size;
  size_t bytes_held;
} Block;

Block *block_new(size_t block_size);
#endif // !BLOCK_H
