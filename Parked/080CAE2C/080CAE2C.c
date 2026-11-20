#include "ffta.h"

typedef struct {
    u8 marker;
    u8 value;
} __attribute__((packed)) EffectPair;

typedef struct EffectRecord {
    u8 count;
    u8 unknown01;
    EffectPair pairs[9];
} EffectRecord;

typedef struct {
    u8 unknown_00[6];
    u8 selected[3];
    u8 default_value;
    u8 unknown_0A[2];
    u8 levels[0];
} ActionState;

typedef struct {
    u8 unknown_00[6];
    u8 category;
    u8 group;
    u8 unknown_08[0x22];
    u16 entries[5];
    ActionState actions;
} EntryObject;

extern const EffectRecord g_table_08520080[];

s32 func_080CA7A4(u16 entry, u8 selector);
const u8 *func_080CD480(u8 first, u8 second);
u8 func_080CD1FC(const void *object, u8 index);
typedef void (*EquipmentCopy)(void *destination, const void *source, u32 size);
extern EquipmentCopy const data_0836D4BC;
extern u8 func_080CABA8(const void *object, const u16 *entries, s8 slot, u8 flags);

/* Complete [0x080CAE2C, 0x080CAF76), 330 bytes and 155 reached instructions.
 * f0b557464e464546e0b48ab080460904090c03911206120e04921b061b0e0593002609484546
 * 2a3503686846291c0a2277f0f8f9049844006a4611190888002804d193890b8066e0bcd43608
 * 1221fff793fc8100091889001f480f18342040448246281901880691068008950794039a9142
 * 45d000223b789e4241da5100b81c40180078002837d04446e479a04233d1f81c40180578a946
 * 40464030401900787f24044041468879291c099202f0d2fa099ac07984421fd24046291c02f0
 * 88f90006099a002817d15346187aa84205d10820064310e00000800052085446e079a84201d1
 * 042004e051468879484503d1022006433006060e01323b789a42bddb089c079960186a46128b
 * 0280081c68446b469b8903806946059c002c03d0049a1006021601e0012252424046331cfff7
 * 25fe06433006060e301c0ab038bc9846a146aa46f0bc02bc0847
 */
u8 func_080CAE2C(EntryObject *data, u16 entry, u8 slot, u8 mode)
{
    u16 entries[5];
    u8 flags = 0;
    u16 current;

    data_0836D4BC(entries, data->entries, sizeof(entries));
    current = entries[slot];
    if (current == 0) {
        entries[slot] = entry;
    } else {
        const EffectRecord *effects = &g_table_08520080[func_080CA7A4(current, 0x12)];
        ActionState *actions = &data->actions;
        u16 old = data->entries[slot];
        s32 index;

        data->entries[slot] = 0;
        if (old != entry) {
            for (index = 0; index < effects->count; index++) {
                u8 marker = effects->pairs[index].marker;
                if (marker != 0 && marker == data->group) {
                    u8 value = effects->pairs[index].value;
                    u8 level = data->actions.levels[value] & 0x7F;

                    if (level < func_080CD480(data->category, value)[7] &&
                        !func_080CD1FC(data, value)) {
                        if (actions->selected[2] == value)
                            flags |= 8;
                        else if (actions->selected[1] == value)
                            flags |= 4;
                        else if (actions->selected[0] == value)
                            flags |= 2;
                    }
                }
            }
        }
        data->entries[slot] = old;
        entries[slot] = entry;
    }
    flags |= func_080CABA8(data, entries, mode ? (s8)slot : -1, flags);
    return flags;
}
