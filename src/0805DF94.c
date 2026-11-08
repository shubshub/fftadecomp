#include "ffta.h"

typedef struct { u8 id; u8 flags; u16 status; } RequiredEntry;
typedef struct { u16 identifier : 10; u16 unknown_0a : 6; u8 unknown_02[2]; u8 required[2]; } __attribute__((packed)) SelectedRecord;
typedef struct {
    u8 unknown_00[0x119D];
    u8 status;
    u8 unknown_119E[3];
    u8 initialized;
    u8 unknown_11A2[2];
    u16 cost;
    u8 unknown_11A6[2];
    u8 unit_count;
    u8 unknown_11A9;
    u8 entry_count;
    u8 unknown_11AB[0x41];
    void *units[23];
    RequiredEntry *entries[66];
    u8 unknown_1350[0x100];
    SelectedRecord *selected;
    u32 pending;
    u8 unknown_1458[0x44];
    u8 indices[24];
} MenuState;
typedef struct {
    u8 unknown_00[0x1F64];
    u32 resources;
    u8 unknown_1F68;
    u8 location;
    u8 unknown_1F6A[0x24A];
    u8 progression[256][2];
} RootState;
typedef void (*BufferInitializer)(void *, u32);
extern BufferInitializer const g_callbacks_0836D4B8[];
extern MenuState *data_0200F448;
extern RootState g_state_02000000;
extern Record g_state_020020D0;
extern u32 func_080CE4DC(u16 identifier, u8 selector);
extern u16 func_080CEC78(u16 identifier, u8 location, u8 count);
extern u8 func_08036350(u8 value);
extern u8 func_080CECF4(void);
extern u8 func_080611F0(u16 identifier, void **output, u8 *indices);
extern u8 func_080612C8(RequiredEntry **output);
extern RequiredEntry *func_0805DD0C(u16 identifier);
extern void func_08060DEC(u8 index, u8 value);
extern u32 func_0805D1C0(u8 option);

/* Target: complete [0x0805DF94, 0x0805E354), 960 bytes. */
u32 func_0805DF94(void)
{
    u32 result = 0;
    u16 identifier = data_0200F448->selected->identifier;
    u8 special = func_080CE4DC(identifier, 1);
    RequiredEntry *second;
    RequiredEntry *first;
    u16 required_first;
    u16 required_second;
    u8 progression;

    if (!data_0200F448->initialized) {
        u16 selected;
        u8 location;
        u8 count;
        data_0200F448->pending = 0;
        data_0200F448->unit_count = func_080611F0(0, data_0200F448->units,
                                               data_0200F448->indices);
        func_08060DEC(4, 0);
        if (!data_0200F448->unit_count && !special) {
            data_0200F448->status = 0x46;
            return 0;
        }
        selected = data_0200F448->selected->identifier;
        location = func_08036350(g_state_02000000.location);
        count = func_080CECF4();
        data_0200F448->cost = func_080CEC78(selected, location, count);
        if (data_0200F448->cost &&
            g_state_02000000.resources < data_0200F448->cost) {
            data_0200F448->status = 0x47;
            return result;
        }
        g_callbacks_0836D4B8[0](data_0200F448->selected->required, 2);
        data_0200F448->entry_count = func_080612C8(data_0200F448->entries);
        second = 0;
        first = 0;
        required_first = func_080CE4DC(identifier, 0x2A);
        if (required_first) {
            first = func_0805DD0C(required_first);
            if (first) {
                first->flags |= 1;
                first->status = data_0200F448->selected->identifier;
                data_0200F448->selected->required[0] = first->id;
                data_0200F448->entries[data_0200F448->entry_count] = first;
            }
        }
        required_second = func_080CE4DC(identifier, 0x2C);
        if (required_second) {
            second = func_0805DD0C(required_second);
            if (second) {
                second->flags |= 1;
                second->status = data_0200F448->selected->identifier;
                data_0200F448->selected->required[1] = second->id;
                data_0200F448->entries[data_0200F448->entry_count + 1] = second;
            }
        }
        if (required_first) {
            if (required_second) {
                if (!first) {
                    if (!second) {
                        data_0200F448->status = 0x57;
                        return result;
                    }
                    g_state_020020D0.field_0c = required_first;
                    data_0200F448->status = 0x49;
                    return result;
                }
                if (!second) {
                    g_state_020020D0.field_0c = required_second;
                    data_0200F448->status = 0x49;
                    return result;
                }
            } else if (!first) {
                g_state_020020D0.field_0c = required_first;
                data_0200F448->status = 0x48;
                return result;
            }
        } else if (required_second && !second) {
            g_state_020020D0.field_0c = required_second;
            data_0200F448->status = 0x48;
            return result;
        }
        progression = func_080CE4DC(identifier, 0x2E);
        if (progression) {
            u32 level = g_state_02000000.progression[progression][0];
            if (level < func_080CE4DC(identifier, 0x2F)) {
                data_0200F448->status = 0x4A;
                return result;
            }
        }
        if ((u8)func_080CE4DC(identifier, 0x30)) {
            data_0200F448->unit_count = func_080611F0(identifier,
                data_0200F448->units, data_0200F448->indices);
            if (!data_0200F448->unit_count) {
                data_0200F448->status = 0x4B;
                return result;
            }
        }
    }
    if (!special) {
        data_0200F448->initialized = 1;
        data_0200F448->status = 0x4C;
        result = 7;
    } else {
        data_0200F448->initialized = 1;
        data_0200F448->status = func_0805D1C0(1);
        result = 9;
    }
    return result;
}
