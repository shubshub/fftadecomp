typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct SelectionState {
    u8 unknown_00[0x58];
    u32 selection;
    u32 value;
    u32 previous;
};

struct ItemEntry {
    u16 id;
    u8 quantity;
    u8 flags;
};

extern struct SelectionState *data_0200F450;
extern struct ItemEntry g_state_02001940[];
extern struct ItemEntry data_02001EE4[];
extern int func_080CAA74(void);
extern u8 func_080CCA80(void);

int func_08061DD0(void)
{
    int category = data_0200F450->selection >> 16;

    if ((data_0200F450->previous >> 16) == category && category != 0)
        return 0;

    switch (category) {
    case 0: {
        u16 id = data_0200F450->value;
        struct ItemEntry *entry = g_state_02001940;
        int index;

        for (index = 0; index < 361; index++, entry++) {
            if (entry->id == id)
                return entry->quantity == 99;
        }
        entry = data_02001EE4;
        for (index = 0; index < 14; index++, entry++) {
            if (entry->id == id)
                return entry->quantity == 99;
        }
        break;
    }
    case 1:
        return func_080CAA74() == 64;
    case 2:
        return func_080CCA80() == 20;
    }
    return 0;
}
