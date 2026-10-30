#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0C];
    const void *field_0C;
} Object0802C9F4;

typedef struct {
    u8 unknown_00[0x1C];
} Entry0802BA08;

typedef struct TransferRecord TransferRecord;
struct TransferRecord {
    u8 status;
    u8 kind;
    u8 unknown_02[2];
    const void *source;
    void *destination;
    u32 control;
    u8 unknown_10[8];
    TransferRecord *next;
};

extern u8 *data_0200F440;
extern s32 func_080C7EA4(const void *object, u32 selector);
extern Entry0802BA08 *func_0802BA08(void);
extern void func_08000ADC(TransferRecord *entry, const void *source,
                          void *destination, u16 words);

/* Complete [0x0802C9F4, 0x0802CA58): 100 bytes.
 * 30b506490c6806496518c06801219bf04ffa142806d015280ad00be040f400025c0c00000148251804e000001c0e000009496518fef7eeff084a291c2023d4f753f8fef7e7ff291c8031054a1823d4f74bf830bc01bc00473c0d000040970006609b0006
 */
void func_0802C9F4(const Object0802C9F4 *object)
{
    u8 *root = data_0200F440;
    const u8 *source = root + 0xC5C;

    switch (func_080C7EA4(object->field_0C, 1)) {
    case 0x14:
        source = root + 0xE1C;
        break;
    case 0x15:
        source = root + 0xD3C;
        break;
    }

    /* The allocator's opaque 0x1C-byte entry is viewed as a transfer record. */
    func_08000ADC((TransferRecord *)func_0802BA08(), source,
                  (void *)0x06009740, 0x20);
    func_08000ADC((TransferRecord *)func_0802BA08(), source + 0x80,
                  (void *)0x06009B60, 0x18);
}
