/* buffer.h */

#include <stdint.h>

typedef struct buffer_item {
	uint8_t data[30]; // array of 30 numbers, each in range 0-255
	uint16_t cksum; // checksum
} BUFFER_ITEM;

#define BUFFER_SIZE 10
