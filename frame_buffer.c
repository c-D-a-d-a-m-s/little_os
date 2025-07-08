#include "io.h"
#include "frame_buffer.h"

/* The starting frame buffer MMIO address*/
char* FB_MMIO_ADDR = (char *) 0xb8000;

/* The frame buffer dimensions*/
#define FB_ROWS                 25
#define FB_COLUMNS              80

/* The I/O ports */
#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

/* The framebuffer color palette*/
enum FB_COLOR {FB_BLACK = 0, FB_BLUE, FB_GREEN, FB_CYAN, FB_RED, 
               FB_MAGENTA, FB_BROWN, FB_LT_GREY, FB_DK_GREY,
               FB_LT_BLUE, FB_LT_GREEN, FB_LT_CYAN, FB_LT_RED,
               FB_LT_MAGENTA, FB_LT_BROWN, FB_WHITE};

/* The default framebuffer foreground and background colors*/
#define FB_DEFAULT_FG FB_GREEN
#define FB_DEFAULT_BG FB_BLACK

void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg) {
    
    FB_MMIO_ADDR[i] = c;
    FB_MMIO_ADDR[i + 1] = ((bg & 0x0F) << 4) | (fg & 0x0F);
}

/**********************************************************************/

void fb_move_cursor(unsigned short pos) {
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT,    ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT,    pos & 0x00FF);
}

int fb_get_cursor_position(void)
{
    int pos = 0;
    outb(FB_COMMAND_PORT, 0x0F);
    pos |= inb(FB_DATA_PORT);
    outb(FB_COMMAND_PORT, 0x0E);
    pos |= ((int)inb(FB_DATA_PORT)) << 8;
    return pos;
}

int fb_clear(void) {
    for (unsigned int i = 0; i < FB_ROWS * FB_COLUMNS; i++) {
        fb_write_cell(2 * i, '\0', FB_DEFAULT_FG, FB_DEFAULT_BG);
        fb_move_cursor(0);
    }
    return 0;
}

void fb_write(char *buf, unsigned int len) {
    int pos = fb_get_cursor_position();
    for (unsigned int i = 0; i < len; i++) {
        if (buf[i] == '\n' && pos / FB_COLUMNS != FB_ROWS - 1) {
            pos = FB_COLUMNS * ( pos / FB_COLUMNS + 1);
            fb_move_cursor(pos);
            continue;
        }
        if (buf[i] == '\n') {
            for (unsigned int j = 0; j < FB_COLUMNS * (FB_ROWS - 1); j++) {
                fb_write_cell(2 * j, *(FB_MMIO_ADDR + 2 * (FB_COLUMNS + j)), FB_DEFAULT_FG, FB_DEFAULT_BG);
            }
            for (unsigned int j = FB_COLUMNS * (FB_ROWS - 1); j < FB_COLUMNS * FB_ROWS; j++) {
                fb_write_cell(2 * j, '\0', FB_DEFAULT_FG, FB_DEFAULT_BG);
            }
            pos = FB_COLUMNS * (FB_ROWS - 1);
            fb_move_cursor(pos);
            continue;
        }
        fb_write_cell(2 * pos, buf[i], FB_DEFAULT_FG, FB_DEFAULT_BG);
        pos++;
        fb_move_cursor(pos);
    }
    return 0;
}