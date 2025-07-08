#ifndef INCLUDE_SERIAL
#define INCLUDE_SERIAL

/* The I/O ports */

/* All the I/O ports are calculated relative to the data port. This is because
    * all serial ports (COM1, COM2, COM3, COM4) have their ports in the same
    * order, but they start at different values.
    */

#define SERIAL_COM1_BASE                0x3F8      /* COM1 base port */

#define SERIAL_DATA_PORT(base)          (base)
#define SERIAL_FIFO_COMMAND_PORT(base)  (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base)  (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base)   (base + 5)

/* The I/O port commands */

/* SERIAL_LINE_ENABLE_DLAB:
    * Tells the serial port to expect first the highest 8 bits on the data port,
    * then the lowest 8 bits will follow
    */
#define SERIAL_LINE_ENABLE_DLAB         0x80

/** serial_configure_baud_rate:
 *  Sets the speed of the data being sent. The default speed of a serial
 *  port is 115200 bits/s. The argument is a divisor of that number, hence
 *  the resulting speed becomes (115200 / divisor) bits/s.
 *
 *  @param com      The COM port to configure
 *  @param divisor  The divisor
 */
void serial_configure_baud_rate(unsigned short com, unsigned short divisor);

/** serial_configure_line:
 *  Configures the line of the given serial port. The port is set to have a
 *  data length of 8 bits, no parity bits, one stop bit and break control
 *  disabled.
 *
 *  @param com  The serial port to configure
 */
void serial_configure_line(unsigned short com);

/** serial_configure_fifo
 *  Configures the buffers (FIFO queues) of the given serial port. The port
 *  is set to enable FIFO, clear both Tx and Rx FIFO queues, and use 14 bytes
 *  as the size of the queue.
 * 
 *  @param com The serial port to configure 
 */
void serial_configure_fifo(unsigned int com);

/** serial_configure_modem
 *  Configures the hardware control flow of the given serial port.
 *  The Ready to Send (RTS) and Data Terminal Ready (DTR) pins are set
 *  which means "ready to send".
 * 
 *  @param com The serial port to configure 
 */
void serial_configure_modem(unsigned int com);

/** serial_init_port
 *  Configures the given serial port.
 *
 *  @param com The serial port to configure
 *  @param divisor  The divisor for baud rate
 */
void serial_init_port(unsigned short com, unsigned short divisor);

/** serial_is_transmit_fifo_empty:
 *  Checks whether the transmit FIFO queue is empty or not for the given COM
 *  port.
 *
 *  @param  com The COM port
 *  @return 0 if the transmit FIFO queue is not empty
 *          1 if the transmit FIFO queue is empty
 */
int serial_is_transmit_fifo_empty(unsigned int com);

/** serial_write
 *  Writes to serial port.
 * 
 *  @param com The target serial port
 *  @param buf The buffer writing to the serial port
 *  @param len The length of the buffer
 */
void serial_write(unsigned int com, char* buf, unsigned int len);

#endif /* INCLUDE_SERIAL */