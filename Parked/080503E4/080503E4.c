#include "ffta.h"

typedef struct {
    u8 unknown_000[0x560];
    u8 field_560;
    u8 field_561;
    u8 field_562;
    u8 field_563;
} Root080503E4;

typedef struct {
    u8 unknown_00[8];
    u16 *destination;
} Menu080503E4;

typedef struct {
    u32 value;
    u16 first;
    u16 second;
} ValuePair080503E4;

typedef struct {
    ValuePair080503E4 pair;
    u8 unknown_08[8];
} Record080503E4;

typedef struct {
    Root080503E4 *root;
    u8 unknown_04[7];
    u8 active;
    u8 unknown_0C[0x3C];
    Menu080503E4 menu;
    u8 unknown_54[0x48];
    Record080503E4 first;
    Record080503E4 second;
    Record080503E4 third;
} State080503E4;

extern const u8 data_0851BA52[];
extern const u8 data_083937BE[];
extern const u8 data_083937C6[];
extern void func_0805005C(State080503E4 *);
extern void func_080500B0(State080503E4 *);
extern void func_0804FD60(Menu080503E4 *);
extern void func_080501CC(State080503E4 *);
extern u16 func_080161A0(u8, u8, u8);
extern void func_0804FD24(u16 *, u16);
extern void func_08017FA8(ValuePair080503E4 *, u32, u16, u16);

/* Complete [0x080503E4, 0x080504BC): 216 bytes.
 * 70b5051c2e1c4836fff736fe281cfff75dfe301cfff7b2fc281cfff7e5feb068
 * 041c2a3425492e30018001390238a042fada142001212022c5f7c0fe0004c00b
 * b1680c182868ac21c900401801780131201cfff775fc04341949081c20800234
 * 2868184940180178201cfff769fc281c9c3015492b68154c1a19127852011032
 * 01341b191b785b058824e4031b191b14c7f798fd281cac300d49d4221823c7f7
 * 91fd281cbc300b491c221823c7f78afd0120e87270bc01bc0047000087c0ffff
 * 88c000006105000052ba510862050000be373908c6373908
 */
void func_080503E4(State080503E4 *state)
{
    Menu080503E4 *menu = &state->menu;
    u16 *destination;
    u16 *limit;
    s32 value;

    func_0805005C(state);
    func_080500B0(state);
    func_0804FD60(menu);
    func_080501CC(state);

    limit = menu->destination + 21;
    value = (s16)0xC087;
    destination = menu->destination + 23;
    do {
        *destination = value--;
        destination--;
    } while (destination >= limit);

    destination = menu->destination + func_080161A0(20, 1, 32);
    func_0804FD24(destination, state->root->field_560 + 1);
    destination += 2;
    *destination++ = 0xC088;
    func_0804FD24(destination, state->root->field_561);

    func_08017FA8(&state->first.pair, (u32)data_0851BA52,
                  state->root->field_562 * 32 + 16,
                  state->root->field_563 * 32 + 68);
    func_08017FA8(&state->second.pair, (u32)data_083937BE, 212, 24);
    func_08017FA8(&state->third.pair, (u32)data_083937C6, 28, 24);
    state->active = 1;
}
