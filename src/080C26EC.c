#include "ffta.h"

struct Actor080C2618 {
    u8 unknown00[0xF8];
    u8 state;
};

struct Unit080C2618 {
    struct Actor080C2618 *actor;
};

struct Result080C2618 {
    u16 action;
    u16 parameter;
    s32 value;
    u8 unknown08[2];
    u16 success;
    s16 value0C;
    s16 value0E;
    u8 value10;
    u8 flags;
};

struct Entry080C26EC {
    struct Unit080C2618 *owner;
    struct Result080C2618 results[40];
    u16 result_count;
};

struct Group080C26EC {
    struct Entry080C26EC entries[13];
    u16 count;
};

struct Selection080C26EC {
    struct Unit080C2618 *owner;
    u16 actions[40];
    u16 unknown_54;
    u16 unknown_56;
};

typedef struct {
    u16 identifier;
    u8 quantity;
    u8 unknown_03;
} InventoryRecord;

extern s32 func_080C7EA4(const void *object, u32 selector);
extern u16 func_080D2F78(u8 value);
extern u8 func_080C8240(void *object);
extern InventoryRecord *func_080CB210(u32 identifier, s32 *count);
extern void func_080C2618(struct Result080C2618 *result,
                          struct Unit080C2618 *source,
                          struct Unit080C2618 *target, u16 action,
                          u16 parameter, u16 argument5);

/* Complete [0x080C26EC, 0x080C286A): 382 bytes, 183 instructions.
 * Target bytes:
 * f0b557464e464546e0b48bb003908846139814991204120c04921b041b0c05930004000c069009060d0e414608680068
 * 062105f0c1fb0004000c089040465630008807900027039a034bd0180088854204d3ff208be0000008290000049cca20
 * 80002a1c424303988218c92189005018018888004018800004301618079a510042460432501800880a910992942805d0
 * 6b1c9946791c8a46d32836d1089a1006000e10f0f3fb0004040c43461868006805f050fd0006000e691c89460137ba46
 * 002822d10290201c02a908f02bfd011c00220298824216da0888a04205d18878c978401a00280edc39e0013204310298
 * 824208da0888a042f7d18878c978401a002800dc0024002c29d042461168ca2080006843039b1d182a68099f0a9bf818
 * 03880094069f0197301cfff7fffe7089002814d0059908040114002903dd0c22b05e00280bdb002903da0c23f05e0028
 * 05dac927bf00e91908880130088049460806050e5746002f00dc6ce7281c0bb038bc9846a146aa46f0bc02bc0847
 */
u8 func_080C26EC(struct Group080C26EC *group,
                 struct Selection080C26EC *selection, u16 default_parameter,
                 s16 filter, u16 argument4, u8 index)
{
    u16 selection_index;
    u16 source_value;
    s32 processed;

    source_value = func_080C7EA4(selection->owner->actor, 6);
    selection_index = selection->unknown_56;

    /* The ROM keeps this one-pass loop: counter r7 = 0 at 0x080C2730,
     * incremented at 0x080C2780 and 0x080C27A8, tested by cmp r7, #0; bgt
     * at 0x080C2852 with the back branch to 0x080C2732 at 0x080C2856. */
    for (processed = 0; processed < 1; index++, processed++) {
        struct Result080C2618 *result;
        u16 parameter;

        if (index >= group->count)
            return 0xFF;
        parameter = default_parameter;
        result = &group->entries[index].results[group->entries[index].result_count];
        if (selection->actions[selection_index] == 0x94 ||
            selection->actions[selection_index] == 0xD3) {
            parameter = func_080D2F78(source_value);
            if (!func_080C8240(selection->owner->actor)) {
                s32 count = 0;
                InventoryRecord *record = func_080CB210(parameter, &count);
                s32 i;

                for (i = 0; i < count; i++, record++) {
                    if (record->identifier == parameter) {
                        if (record->quantity - record->unknown_03 <= 0)
                            parameter = 0;
                        break;
                    }
                }
                if (parameter == 0)
                    continue;
            }
        }
        func_080C2618(result, selection->owner, group->entries[index].owner,
                      selection->actions[selection_index], parameter,
                      argument4);
        if (result->success == 0)
            continue;
        if (filter > 0 && result->value0C < 0)
            continue;
        if (filter < 0 && result->value0C >= 0)
            continue;
        group->entries[index].result_count++;
    }
    return index;
}
