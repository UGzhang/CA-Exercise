#define _POSIX_C_SOURCE 199309L
#include "draw.h"
#include <stdio.h>

// If you want you can use the provided struct and static function

typedef struct COLOR_s {
    unsigned char r; // red channel
    unsigned char g; // green channel
    unsigned char b; // blue channel
} COLOR;

static COLOR color_converter(double value) {
    COLOR c;
    c.r = 0;
    c.g = 0;
    c.b = 0;

    //color mapping

    if (value < 0.25) {
        c.r = 0;
        c.g = (unsigned char)(value / 0.25 * 255);
        c.b = 255;
    } else if (value < 0.5) {
        c.r = 0;
        c.g = 255;
        c.b = (unsigned char)((0.5 - value) / 0.25 * 255);
    } else if (value < 0.75) {
        c.r = (unsigned char)((value - 0.5) / 0.25 * 255);
        c.g = 255;
        c.b = 0;
    } else {
        c.r = 255;
        c.g = (unsigned char)(( 1 - value) / 0.25 * 255);
        c.b = 0;
    }

    return c;
}



void draw_grid(const double* grid, uint32_t x, uint32_t y, const char* filepath) {
    // TODO mandatory
    // Open or create file
    // Write header with meta information
    // Write RGB data
    // Close file

    FILE *file = fopen(filepath, "w");
    if (!file) {
        perror("Error opening file");
        return;
    }

    // Write the header
    fprintf(file, "P3\n%d %d\n255\n", x, y);

    // Write pixel data
    for (uint32_t i = 0; i < y; i++) {
        for (uint32_t j = 0; j < x; j++) {
            COLOR c = color_converter(grid[i * x + j]);
            fprintf(file, "%d %d %d ", c.r, c.g, c.b);
        }
        fprintf(file, "\n");
    }

    fclose(file);




}
