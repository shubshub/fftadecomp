/* Target: 0x08000438-0x08000460, 40 complete bytes (32 bytes of code, 8-byte literal pool).
 * 80b5 6f46 0649 081c 0421 [bl func_080069F4] 0549 081c 0121 [bl func_080069F4]
 * 80bc 01bc 0047 0000; pool 0x03000880, 0x030027E0.
 * Runs the two runners that func_0800052C initialises. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef void (*Callback08000438)(u8, u8 *);
typedef struct {
    u16 value;
    u8 count;
    u8 current;
    u8 active_count;
    u8 state;
    u8 unknown_06[2];
    Callback08000438 *callbacks;
    u8 *states;
} Runner08000438;

extern Runner08000438 data_03000880;
extern Runner08000438 data_030027E0;
extern void func_080069F4(Runner08000438 *, u8);

void func_08000438(void)
{
    func_080069F4(&data_03000880, 4);
    func_080069F4(&data_030027E0, 1);
}
