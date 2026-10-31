#include "ffta.h"

/* Target [0x080B5920, 0x080B5A08), 232 bytes:
 * f0b557464e464546e0b483b0071c0c1c151c0b982406240e2d062d0e1b041b0c9a46
 * 0004000c8146802040016cf778ff8046386800906946388940090871b88940094871
 * 684651464181494601818471c5710079241a24062416684640792d1a2d062d16201c
 * 291ce7f798fe0006010e002800daf97f09060916684601224346fff73cf8061c002e
 * 22dd0025b5421ada4446381c80300068002161560122a256e3f72cfe011c002909d0
 * 386809684a465346fff75df90006000e012808d004340135b542e5db40466cf734ff
 * 002003e040466cf72fff012003b038bc9846a146aa46f0bc02bc0847
 */
typedef struct Unit Unit;

typedef struct {
    Unit *unit;
} UnitOwner;

typedef struct {
    void *context;
    u8 unknown_04[4];
    u16 x;
    u8 unknown_0a[2];
    u16 y;
    u8 unknown_0e[0x11];
    u8 direction;
    u8 unknown_20[0x60];
    void *lookup_context;
} SelectionObject;

typedef struct {
    s8 x;
    s8 y;
    u8 unknown_02[2];
} SelectionPoint;

typedef struct {
    void *context;
    u8 origin_x;
    u8 origin_y;
    u8 x;
    u8 y;
    u16 identifier;
    u16 value;
} SelectionRequest;

extern void *func_08022840(u32 size);
extern void func_08022854(u8 *object);
extern s32 func_0809D6BC(s8 x, s8 y);
extern s32 func_080B4A1C(SelectionRequest *request, s8 direction, u8 mode,
                        SelectionPoint *output);
extern UnitOwner *func_0809961C(void *context, s8 x, s8 y);
extern u32 func_080B4C90(void *context, void *object, u16 identifier, u16 value);

s32 func_080B5920(SelectionObject *object, u8 x, u8 y, u16 value,
                   u16 identifier)
{
    SelectionRequest request;
    SelectionPoint *points;
    UnitOwner *owner;
    u8 direction;
    s32 count;
    s32 i;

    points = func_08022840(4096);
    request.context = object->context;
    request.origin_x = object->x >> 5;
    request.origin_y = object->y >> 5;
    request.value = value;
    request.identifier = identifier;
    request.x = x;
    request.y = y;

    direction = (u8)func_0809D6BC((s8)(x - request.origin_x),
                                 (s8)(y - request.origin_y));
    if ((s8)direction < 0)
        direction = object->direction;

    count = func_080B4A1C(&request, (s8)direction, 1, points);
    if (count <= 0)
        goto done;

    for (i = 0; i < count; i++) {
        owner = func_0809961C(object->lookup_context, points[i].x, points[i].y);
        if (owner != 0 &&
            (u8)func_080B4C90(object->context, owner->unit,
                              identifier, value) == 1)
            goto done;
    }

    func_08022854((u8 *)points);
    return 0;

done:
    func_08022854((u8 *)points);
    return 1;
}
