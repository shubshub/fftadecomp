#include "ffta.h"

typedef struct MenuState0805D784 {
    u8 unknown_0000[0x1199];
    u8 phase;
    u8 unknown_119A[0x11];
    u8 count;
    u8 unknown_11AC[0x1A4];
    const u8 *entries[64];
    u8 unknown_1450[8];
    const u8 *selected;
} MenuState0805D784;

extern MenuState0805D784 *data_0200F448;
extern u8 g_state_02000000[];
extern u8 data_030008B0[];
extern u8 data_03000990[];

extern void func_0802A2C0(u8, u8, u8, u8);
extern void func_08029E48(void *, void *, const u16 *, s16, s16, u8);
extern u8 func_08036350(u8);
extern u32 func_080D1B80(const u8 **, u32, u32);
extern void func_08060DEC(u8, u8);
extern void func_0805F44C(u8);
extern void func_0805F540(void *const *, s32);
extern s16 func_0805F4AC(void);
extern u8 func_08060DD4(void);
extern u32 func_0805D4EC(void);
extern s16 func_08060DC4(void);
extern void func_0801174C(void *, u8, u16, void *, void *, u16, u16,
                          u8, u8, u16);
extern u16 func_08011860(void);
extern void func_0806130C(const u8 *);

/* Complete [0x0805D784, 0x0805D91C): 408 bytes, 163 instructions.
 * Target bytes:
 * f0b557464e464546e0b486b006488046006806498a4650440678012e5cd0012e
 * 06dc002e08d0ace048f4000299110000022e00d194e0a4e00020002100220023
 * ccf77cfd1e48112100910196002100221423ccf737fb424614681a4fe0190578
 * 194b99464c441948194940180078d8f7adfd021c1206120e201c402174f0bef9
 * 42461168c91908701068c0190078854203d00220002103f0e7fa022001f014fe
 * 434619684a468818c919097801f086fe43461868074a81180e60504401215fe0
 * b0080003ab1100005013000000000002691f00005814000001f026fe00040028
 * 4fd003f0b5fa0006000e012849db022804dcfff739fe0006000e43e0042840dc
 * 03f09efa000443461c6811496218800b104be1180918086810600278013a1204
 * 120c0d4b0d4800900225019502961820039010200490e02040000590201c0821
 * b3f742ff414608685044057019e000005814000050130000b008000390090003
 * b3f7bcff000400280bd042461068094bc018006803f008fd4146086850440021
 * 0170032006b038bc9846a146aa46f0bc02bc084758140000
 */
u32 func_0805D784(void)
{
    switch (data_0200F448->phase) {
    case 0: {
        u8 old_count;
        const u8 **entries;
        u8 filter;

        func_0802A2C0(0, 0, 0, 0);
        func_08029E48(data_030008B0, 0, 0, 20, 17, 0);
        old_count = data_0200F448->count;
        entries = data_0200F448->entries;
        filter = func_08036350(g_state_02000000[0x1F69]);
        data_0200F448->count = func_080D1B80(entries, 64, filter);
        if (old_count != data_0200F448->count)
            func_08060DEC(2, 0);
        func_0805F44C(2);
        func_0805F540((void *const *)data_0200F448->entries,
                      data_0200F448->count);
        data_0200F448->selected = 0;
        data_0200F448->phase = 1;
        break;
    }
    case 1:
        if (func_0805F4AC() != 0) {
            u8 mode = func_08060DD4();

            if (mode < 1)
                break;
            if (mode <= 2)
                return (u8)func_0805D4EC();
            if (mode <= 4) {
                u16 index = (u16)func_08060DC4();
                MenuState0805D784 *state = data_0200F448;

                state->selected = state->entries[index];
                func_0801174C(state, 8, (u16)(state->selected[0] - 1),
                              data_030008B0, data_03000990, 2, 1,
                              24, 16, 448);
                data_0200F448->phase = 2;
            }
        }
        break;
    case 2:
        if (func_08011860() != 0) {
            func_0806130C(data_0200F448->selected);
            data_0200F448->phase = 0;
        }
        break;
    }
    return 3;
}
