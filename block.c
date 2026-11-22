#include "block.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

Block *block_new(size_t block_size) {
  Block *block = (Block *)malloc(block_size);
  block->block_size = block_size;
  block->bytes_held = 0;
  block->bytes = (unsigned char *)malloc(sizeof(unsigned char) * block_size);

  if (block->bytes == NULL) {
    fprintf(stderr, "Failed to allocate memory for new block");
    return NULL;
  }

  return block;
}

