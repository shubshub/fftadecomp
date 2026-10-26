#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x1199];
    u8 mode;
    u8 timer;
    u8 unknown_119B;
    u8 active;
    u8 unknown_119D[6];
    u8 selection;
    u8 unknown_11A4[6];
    u8 first;
    u8 unknown_11AB[0x9D];
    void *entries[0];
} MenuState;

extern MenuState *data_0200F448;
extern u8 func_08060DD4(void);
extern u16 func_08060DC4(void);
extern void func_0805DE30(u16 identifier);
extern void func_0805F540(void **entries, u32 index);
extern void func_0805F59C(u32 index, u8 selection);
extern u8 func_0805D1C0(u32 index);
extern void func_08061028(MenuState *state, u8 value);
extern void func_080133B0(u32 mask);
extern u8 func_08060E0C(u32 index);
extern void func_080613D0(void *entry);
extern void func_0805F4D8(u32 index, u32 value);

/* Complete target: [0x0805E5C0, 0x0805E798), 472 bytes. */
u8 func_0805E5C0(void)
{
    u8 index;
    void *entry;

    switch (func_08060DD4()) {
    case 1:
    case 2:
        if (data_0200F448->active == 0) {
            func_08061028(data_0200F448, func_0805D1C0(1));
            func_080133B0(0x1000);
            data_0200F448->active = 1;
            data_0200F448->timer = 10;
            data_0200F448->mode = 3;
        } else {
            func_0805F4D8(5, 0);
            index = func_08060E0C(5);
            if (index != 2) {
                entry = data_0200F448->entries[data_0200F448->first + index];
                if (entry != 0)
                    func_080613D0(entry);
            }
            data_0200F448->active = 0;
            data_0200F448->timer = 10;
            data_0200F448->mode = 1;
        }
        return 1;
    case 3:
    case 4:
        if (data_0200F448->active == 0) {
            func_0805DE30(func_08060DC4());
            func_0805F540(data_0200F448->entries, data_0200F448->first + 2);
            func_0805F59C(5, data_0200F448->selection);
            func_08061028(data_0200F448, func_0805D1C0(1));
            func_080133B0(0x1000);
            index = func_08060E0C(5);
            if (index != 2) {
                entry = data_0200F448->entries[data_0200F448->first + index];
                if (entry != 0)
                    func_080613D0(entry);
            }
            data_0200F448->active = 1;
            data_0200F448->timer = 10;
            data_0200F448->mode = 3;
        } else {
            func_0805F4D8(5, 0);
            data_0200F448->active = 0;
            data_0200F448->timer = 10;
            data_0200F448->mode = 1;
        }
        return 1;
    }
    return 0;
}
