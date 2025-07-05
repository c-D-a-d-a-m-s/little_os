#include "frame_buffer.h"

int main(void) {
    char buf[13] = {'H','e','l','l','o',',',' ','w','o','r','l','d','!'};
    fb_clear();
    fb_write(buf, 13);

    return 0;
}