#ifndef INCLUDE_FRAME_BUFFER
#define INCLUDE_FRAME_BUFFER

/** fb_write_cell:
 *  Writes a character with the given foreground and background to position i
 *  in the framebuffer.
 *
 *  @param i  The location in the framebuffer
 *  @param c  The character
 *  @param fg The foreground color
 *  @param bg The background color
 */
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);

/** fb_move_cursor:
 *  Moves the cursor of the framebuffer to the given position
 *
 *  @param pos The new position of the cursor
 */
void fb_move_cursor(unsigned short pos);

/** fb_clear
 *  "Clears" framebuffer by writing space characters to all
 *  cells and setting cursor position to first cell.
 */
int fb_clear(void);

/** fb_get_cursor_position:
 *  Gets the current position of the cursor.
 */
int fb_get_cursor_position(void);

/** fb_write:
 *  Writes to the display.
 * 
 *  @param buf The character buffer
 *  @param len The size of the buffer
 */
void fb_write(char *buf, unsigned int len);

#endif /* INCLUDE_FRAME_BUFFER */