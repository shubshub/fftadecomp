#include "ffta.h"

typedef struct {
    u8 unknown_00[6];
    u8 race;
    u8 unknown_07[0x35];
    u8 ability;
    u8 unknown_3D[0xAB];
    u8 requirements[6];
} Unit0812E130;

typedef struct {
    u8 unknown_00[4];
    u16 requirement;
    u8 unknown_06[2];
} Ability0812E130;

typedef struct {
    u8 unknown_00[3];
    u8 chance;
} Requirement0812E130;

extern u8 func_080C8298(const void *object);
extern const Ability0812E130 *func_080CD480(u8 race, u8 ability);
extern u8 func_08133B3C(const u8 *requirements, u16 requirement);
extern u32 func_08002804(void);
extern const Requirement0812E130 data_0852736C[];

/* 0x0812E130..0x0812E1A8: 120 bytes, 53 instructions. */
s32 func_0812E130(const Unit0812E130 *unit, const void *unused, u8 options)
{
    const Ability0812E130 *ability;
    s32 result;
    u32 flags = options;

    if (!func_080C8298(unit)) {
        ability = func_080CD480(unit->race, unit->ability);
        if (ability->requirement != 0) {
            if (func_08133B3C(unit->requirements, ability->requirement)) {
                const Requirement0812E130 *requirement;

                requirement = data_0852736C + ability->requirement;
                result = requirement->chance;
                flags &= 4;
                if (flags) {
                    s16 adjustment = (s16)func_08002804() % 15;
                    result += adjustment;
                }
                if (result < 0)
                    result = 0;
                if (result > 100)
                    result = 100;
                return result;
            }
        }
    }
    return 0;
}
