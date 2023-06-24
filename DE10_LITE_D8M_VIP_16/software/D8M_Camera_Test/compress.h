#ifndef IMAGE_COMPRESSION_H
#define IMAGE_COMPRESSION_H

#include <stdint.h>

// Constants for image dimensions
#define WIDTH  640
#define HEIGHT 480

// Function declaration for image compression
uint8_t* compress_image(uint8_t* image);

#endif /* IMAGE_COMPRESSION_H */
