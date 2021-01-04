#include <stdio.h>
#ifndef _MSC_VER
#include <unistd.h>
#endif
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include <modbus.h>

/* The goal of this program is to check all major functions of
   libmodbus:
   - write_coil
   - read_bits
   - write_coils
   - write_register
   - read_registers
   - write_registers
   - read_registers
   All these functions are called with random values on a address
   range defined by the following defines.
*/

int main(void)
{
    modbus_t *ctx;
    uint16_t tab_reg[64];
    uint16_t tab_running[10];
    uint8_t tab_rp_bits[64];
    int rc;
    int i;

    ctx = modbus_new_tcp("192.168.1.2", 502);

    /* set timeout */
    uint32_t old_response_to_sec;
    uint32_t old_response_to_usec;
    modbus_get_byte_timeout(ctx, &old_response_to_sec, &old_response_to_usec);

    uint32_t set_response_to_sec = 0;
    uint32_t set_response_to_usec = 3000000;
    modbus_set_response_timeout(ctx, set_response_to_sec, set_response_to_usec);

    if (modbus_connect(ctx) == -1)
    {
        fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
        modbus_free(ctx);
        return -1;
    }

    rc = modbus_write_bit(ctx, 0, 0);

    rc = modbus_read_bits(ctx, 0, 1, tab_rp_bits);
    if (rc == -1) 
    {
        fprintf(stderr, "%s\n", modbus_strerror(errno));
        return -1;
    }

    printf("DO1 = %d\n", tab_rp_bits[0]);
    
    rc = modbus_read_input_registers(ctx, 7001, 12, tab_reg);
    if (rc == -1) 
    {
        fprintf(stderr, "%s\n", modbus_strerror(errno));
        return -1;
    }
    
    for (i=0; i < rc; i += 2)
    {
        printf("Robot_arm_position[%d]=%f\n", i, modbus_get_float_dcba(&tab_reg[i]));
    }
    
    rc = modbus_read_registers(ctx, 9000, 1, tab_running);
    if (rc == -1) 
    {
        fprintf(stderr, "%s\n", modbus_strerror(errno));
        return -1;
    }
    
    printf("running=%d\n", tab_running[0]);
    
    //free(tab_reg);
    modbus_close(ctx);
    modbus_free(ctx);
}
