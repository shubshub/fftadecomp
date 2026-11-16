#include "ffta.h"

/* Complete target [0x08004E10, 0x08004EC8): 184 bytes, 71 instructions.
 * f0b5071c0e1c034c6078002804d0012830d038e0a02800031f4b1d78082084462840002826d0
 * 1d48017802200840002829d00520014001291cd161690638814218d1174ad1881748084040210843
 * d08015490880597841204042084058701349c0200880f6391248086060462070802028431870301c
 * 00f055f8381c00f01cf80c49012048700b48c17a0131c172c078f0bc02bc084700002801000434010004
 * a00e00037fff00000002000402020004fcb1c000a0280003
 */

typedef struct {
    u8 flags;
    u8 stage;
    u8 connected_flags;
    u8 recv_success_flags;
    u8 unknown_04[7];
    u8 send_frame_counter;
    u8 unknown_0C[8];
    s32 field_14;
} SerialState08004E10;

typedef struct {
    u8 unknown_00[6];
    u16 interrupt_mask;
} InterruptState08004E10;

/* SIOCNT (0x04000128) in multi-player mode, laid out as the hardware defines
 * it (the same fields as the SDK's SioMultiCnt).  Each single-bit store is a
 * read-modify-write of one byte with a sign-extended byte mask: irq_enable at
 * 0x08004E64..0x08004E6C is ldrb [r3, #1]; movs #0x41; rsbs; ands; strb, the
 * code agbcc emits for a byte-sized bit-field store, where a u8 pointer and
 * `&= ~0x40` give movs #0xBF instead.  start (0x08004E7E..0x08004E82) reuses
 * the byte read for the sd_terminal test at 0x08004E2A. */
typedef struct {
    u16 baud_rate : 2;
    u16 si_terminal : 1;
    u16 sd_terminal : 1;
    u16 id : 2;
    u16 error : 1;
    u16 start : 1;
    u16 unknown_08 : 4;
    u16 mode : 2;
    u16 irq_enable : 1;
    u16 unknown_0F : 1;
} SioControl08004E10;

extern SerialState08004E10 data_030028A0;
extern InterruptState08004E10 data_03000EA0;
extern u8 func_08004F34(void *destination);
extern void func_08004EC8(const void *source);

u32 func_08004E10(const void *send, void *receive)
{
    switch (data_030028A0.stage) {
    case 0:
        {
            SioControl08004E10 *serial = (SioControl08004E10 *)0x04000128;

            if (serial->sd_terminal) {
                u8 input = *(u16 *)0x04000134;

                if (!(input & 2))
                    break;
                if ((input & 5) == 1 && data_030028A0.field_14 == -1) {
                    data_03000EA0.interrupt_mask =
                        (data_03000EA0.interrupt_mask & 0xFF7F) | 0x40;
                    *(u16 *)0x04000200 = data_03000EA0.interrupt_mask;
                    serial->irq_enable = 0;
                    *(u16 *)0x04000202 = 0xC0;
                    *(u32 *)0x0400010C = 0x00C0B1FC;
                    data_030028A0.flags = 8;
                    serial->start = 1;
                }
            }
        }
        /* fall through */
    case 1:
        func_08004F34(receive);
        func_08004EC8(send);
        data_030028A0.stage = 1;
        break;
    }
    data_030028A0.send_frame_counter++;
    return data_030028A0.recv_success_flags;
}
