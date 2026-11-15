#include "ffta.h"

/* Complete target [0x08004EC8, 0x08004F34): 108 bytes, 47 instructions.
 * Pool: 0x030028A0 0x04000004 0x0400010E
 */

/* The four header bytes come from the stores below and the sixteen payload
 * bytes from the copy count, which makes the ten halfwords the checksum loop
 * sums.  The buffers themselves are 0x18 bytes apart (func_08004AC0).
 */
typedef struct {
    u8 frame_counter;
    u8 recv_error_flags;
    u16 checksum;
    u8 payload[16];
} SerialPacket;

/* func_08004E10 adds one to +0x0B on every call and returns +0x03;
 * func_08004F34 clears +0x03, sets one bit of it for each buffer whose
 * checksum holds, and ORs the result into +0x02.
 */
typedef struct {
    u8 flags;
    u8 unknown_01;
    u8 connected_flags;
    u8 recv_success_flags;
    u8 unknown_04[6];
    s8 selected;
    u8 send_frame_counter;
    u8 unknown_0C[8];
    s32 field_14;
    u8 unknown_18[0x10];
    u16 *next_send;
} SerialState;

extern SerialState data_030028A0;
extern void func_0814186C(const void *source, void *destination, u32 control);

void func_08004EC8(const void *source)
{
    s32 checksum = 0;
    s32 i;

    ((SerialPacket *)data_030028A0.next_send)->frame_counter = data_030028A0.send_frame_counter;
    ((SerialPacket *)data_030028A0.next_send)->recv_error_flags =
        data_030028A0.connected_flags ^ data_030028A0.recv_success_flags;
    ((SerialPacket *)data_030028A0.next_send)->checksum = 0;
    func_0814186C(source, &data_030028A0.next_send[2], 0x04000004);
    for (i = 0; i < sizeof(SerialPacket) / 2; i++)
        checksum += data_030028A0.next_send[i];
    ((SerialPacket *)data_030028A0.next_send)->checksum = ~checksum;
    if (data_030028A0.flags)
        *(u16 *)0x0400010E = 0;
    data_030028A0.field_14 = data_030028A0.selected;
    if (data_030028A0.flags)
        *(u16 *)0x0400010E = 0xC0;
}
