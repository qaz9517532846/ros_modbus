#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
 
#include <modbus.h>
 
#define MODBUS_SERIAL_DEV           "/dev/ttyUSB0"
#define MODBUS_SERIAL_BAUDRATE      9600    /* 9600, 38400, 115200, ... */
#define MODBUS_SERIAL_PARITY        'N'     /* 'N', 'E', or 'O' */
#define MODBUS_SERIAL_DATABITS      8       /* 5, 6, 7, or 8 */
#define MODBUS_SERIAL_STOPBITS      1       /* 1 or 2 */
#define MODBUS_DEVICE_ID            1
#define MODBUS_TIMEOUT_SEC          3
#define MODBUS_TIMEOUT_USEC         0
#define MODBUS_DEBUG                ON
#define MODBUS_RO_BITS              32
#define MODBUS_RW_BITS              32
#define MODBUS_RO_REGISTERS         64
#define MODBUS_RW_REGISTERS         64
 
int main(int argc, char *argv[])
{
    modbus_t            *ctx;
    modbus_mapping_t    *data_mapping;
    struct timeval      timeout;
    int                 ret, go = 1;
    uint8_t             query[MODBUS_TCP_MAX_ADU_LENGTH];
 
    ctx = modbus_new_rtu(MODBUS_SERIAL_DEV,
            MODBUS_SERIAL_BAUDRATE,
            MODBUS_SERIAL_PARITY,
            MODBUS_SERIAL_DATABITS,
            MODBUS_SERIAL_STOPBITS);
 
    if (ctx == NULL) {
        fprintf(stderr, "Unable to create the libmodbus context\n");
        exit(-1);
    }
 
    /* set slave device ID */
    modbus_set_slave(ctx, MODBUS_DEVICE_ID);
 
    /* Debug mode */
    modbus_set_debug(ctx, MODBUS_DEBUG);
 
    data_mapping = modbus_mapping_new(MODBUS_RO_BITS, MODBUS_RW_BITS,
                                    MODBUS_RO_REGISTERS, MODBUS_RW_REGISTERS);
 
    if (data_mapping == NULL) {
        fprintf(stderr, "Failed to allocate the mapping: %s\n",
                modbus_strerror(errno));
        modbus_free(ctx);
        return -1;
    }
 
    /* FIXME: initiate all data here */
 
    /* open serial interface */
    modbus_connect(ctx);
 
    while(go) {
 
        ret = modbus_receive(ctx, query);
        if (ret >= 0) {
            /* IF SOME ERROR OCCOR */
                /* modbus_reply_exception(ctx, query, MODBUS_EXCEPTION_XXXX); */
            /* ELSE */
                modbus_reply(ctx, query, ret, data_mapping);
        } else {
            /* Connection closed by the client or server */
            break;
        }
    }
 
    printf("Quit the loop: %s\n", modbus_strerror(errno));
 
    modbus_mapping_free(data_mapping);
 
    modbus_free(ctx);
 
    return 0;
}