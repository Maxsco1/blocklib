#include "block.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char *pad(unsigned char *bytes, size_t bytes_length,
                   size_t bytes_to_pad) {
  if (bytes == NULL) {
    return bytes;
  }

  unsigned char *new_bytes = malloc(sizeof(unsigned char *) * bytes_to_pad);

  if (new_bytes == NULL) {
    fprintf(stderr, "Failed to allocate memory while padding block\n");
    return NULL;
  }

  memset(new_bytes, 0x55, bytes_length + bytes_to_pad);
  memcpy(new_bytes + bytes_to_pad, bytes, bytes_length);

  if (new_bytes == NULL) {
    fprintf(stderr, "Failed to copy existing bytes to padded bytes\n");
    return NULL;
  }

  return new_bytes;
}

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

Block *block_from_bytes(unsigned char *bytes, size_t bytes_length,
                        size_t block_size) {
  if (bytes == NULL) {
    return NULL;
  }

  Block *block = block_new(block_size);

  if (block == NULL) {
    return block;
  }

  if (bytes_length < block_size) {
    bytes = pad(bytes, bytes_length, block_size - bytes_length);

    if (bytes == NULL) {
      return block;
    }
  }

  int i = 0;
  while (block->bytes_held < block_size && bytes) {
    block->bytes[i] = *(bytes++);
    block->bytes_held++;
    i++;
  }

  return block;
}

void block_print(Block *block) {
  printf("[ ");

  for (size_t i = 0; i < block->block_size; i++) {
    printf("%02x ", block->bytes[i]);
  }

  printf("]\n");
}

Block *block_apply(const Block *block1, const Block *block2,
                   unsigned char binary_byte_op(unsigned char byte1,
                                                unsigned char byte2)) {
  if (block1 == NULL || block2 == NULL) {
    return NULL;
  }

  if (block1->block_size != block2->block_size) {
    fprintf(stderr, "To apply a function to two blocks, they must have the "
                    "same block_size\n");
    return NULL;
  }

  if (block1->bytes_held != block2->bytes_held) {
    fprintf(stderr, "To apply a function to two blocks, they must hold the "
                    "same number of bytes\n");
    return NULL;
  }

  Block *result_block = block_new(block1->block_size);
  if (result_block == NULL) {
    fprintf(stderr, "Failed to create new block\n");
    return NULL;
  }

  for (size_t i = 0; i < block1->block_size; i++) {
    result_block->bytes[i] = binary_byte_op(block1->bytes[i], block2->bytes[i]);
  }

  return result_block;
}
