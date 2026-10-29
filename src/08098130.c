#include "ffta.h"

typedef struct {
    u8 unknown_00[0x18];
    u16 hit_points;
} Unit;

typedef struct {
    Unit *unit;
    u8 unknown_04[0x1A];
    u8 status_icon;
    u8 unknown_1F[0x11];
    u32 flags;
} UnitDisplay;

extern u8 func_080CD944(const void *unit);
extern u8 func_080CD9A4(const void *unit);
extern u32 func_080CD974(const void *unit);
extern u8 func_080CD95C(const void *unit);
extern s32 func_080C7EA4(const void *unit, u32 selector);
extern u8 func_080CDA04(const void *unit);
extern u8 func_080CDA7C(const void *unit);
extern u8 func_080CD9BC(const void *unit);
extern u8 func_080CD92C(const void *unit);
extern u8 func_080CDCBC(const void *unit);
extern u8 func_080CDADC(const void *unit);
extern u8 func_080CDB24(const void *unit);
extern u8 func_080CDAAC(const void *unit);
extern u8 func_080CDAC4(const void *unit);
extern u8 func_080CD9EC(const void *unit);
extern u8 func_080CD9D4(const void *unit);
extern u8 func_080CDA4C(const void *unit);
extern void func_0809801C(UnitDisplay *display);

/* Complete [0x08098130, 0x0809836C): 572 bytes, 248 instructions. */
void func_08098130(UnitDisplay *display)
{
    if (func_080CD944(display->unit))
        display->flags |= 0x2000;
    else
        display->flags &= ~0x2000;

    if (func_080CD9A4(display->unit))
        display->flags |= 0x1000;
    else
        display->flags &= ~0x1000;

    if ((u8)func_080CD974(display->unit))
        display->flags |= 0x4000;
    else
        display->flags &= ~0x4000;

    if (func_080CD95C(display->unit))
        display->flags |= 0x20;
    else
        display->flags &= ~0x20;

    if ((u32)func_080C7EA4(display->unit, 0x13) <=
            ((u32)func_080C7EA4(display->unit, 0x14) >> 2) ||
        func_080CDA04(display->unit))
        display->flags |= 8;
    else
        display->flags &= ~8;

    if (func_080CDA7C(display->unit))
        display->flags |= 0x400;
    else
        display->flags &= ~0x400;

    if (func_080CD9BC(display->unit))
        display->flags |= 0x20000;
    else
        display->flags &= ~0x20000;

    if (display->unit->hit_points == 0)
        display->flags |= 0x10;
    else
        display->flags &= ~0x10;

    if (func_080CD92C(display->unit)) {
        display->flags |= 0x40;
        if (func_080CDCBC(display->unit))
            display->flags |= 8;
        else
            display->flags &= ~8;
    } else {
        display->flags &= ~0x40;
    }

    if (func_080CDADC(display->unit) || func_080CDB24(display->unit))
        display->flags |= 0x80;
    else
        display->flags &= ~0x80;

    if (func_080CDAAC(display->unit))
        display->flags |= 0x100;
    else
        display->flags &= ~0x100;

    if (func_080CDAC4(display->unit))
        display->flags |= 0x200;
    else
        display->flags &= ~0x200;

    if (func_080CD9EC(display->unit) || func_080CD9D4(display->unit) ||
        func_080CDA4C(display->unit))
        display->flags |= 0x800;
    else
        display->flags &= ~0x800;

    func_0809801C(display);
    if (display->flags & 0x2000)
        display->status_icon = 14;
    if (display->flags & 0x1000)
        display->status_icon = 5;
    if (display->flags & 0x40)
        display->status_icon = 15;
}
