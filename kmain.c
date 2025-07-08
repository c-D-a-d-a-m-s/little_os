#include "frame_buffer.h"
#include "serial.h"

int main(void) {
    serial_init_port(SERIAL_COM1_BASE, 12); /* The 12 divides initial baud rate 115200 / 12 = 9600*/
    
    char buf[13] = {'H','e','l','l','o',',',' ','w','o','r','l','d','!'};
    fb_clear();
    fb_write(buf, 13);

    serial_write(SERIAL_COM1_BASE, buf, 13);

    return 0;
}