#include "ffta.h"

typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
} FlaggedObject;

typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
} ScriptObject;

typedef struct {
    u8 unknown_00[0x1C];
} Entry0802BA08;

typedef struct TransferRecord TransferRecord;
typedef struct RequestNode RequestNode;

extern u8 *data_0200F440;
extern u8 func_080C82B8(const FlaggedObject *object);
extern u8 func_080C832C(const ScriptObject *object);
extern Entry0802BA08 *func_0802BA08(void);
extern void func_08000ADC(TransferRecord *entry, const void *source,
                          void *destination, u16 words);
extern void func_08000B68(RequestNode *entry, u32 first, u32 second, u16 count);

/* Complete [0x0802BE40, 0x0802BEB0): 112 bytes.
 * 10b5041c9cf038fa0006002809d0fff7dbfd0c4909680c4a89180c4a1023d4f73dfe201c9cf062fa0006002814d0fff7cbfd04490968064a8918064a0823d4f72dfe10e040f40002fc0e0000c03801063c0f0000603d0106fff7b6fd034a00210823d4f761fe10bc01bc0047603d0106
 */
void func_0802BE40(const void *object)
{
    if (func_080C82B8((const FlaggedObject *)object)) {
        Entry0802BA08 *entry = func_0802BA08();

        func_08000ADC((TransferRecord *)entry, data_0200F440 + 0xEFC,
                      (void *)0x060138C0, 0x10);
    }

    if (func_080C832C((const ScriptObject *)object)) {
        Entry0802BA08 *entry = func_0802BA08();

        func_08000ADC((TransferRecord *)entry, data_0200F440 + 0xF3C,
                      (void *)0x06013D60, 8);
    } else {
        Entry0802BA08 *entry = func_0802BA08();

        func_08000B68((RequestNode *)entry, 0, 0x06013D60, 8);
    }
}
