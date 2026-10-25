/* Target 0x080ED308, complete [0x080ED308, 0x080ED3B8), 176 bytes.
 * Fill the handle's byte-pair buffer around a signed table offset.
 */

#include "ffta.h"

typedef struct {
    u8 unknown_00[0x150];
    s32 offset;
    u8 unknown_154[0x84];
    void *handle;
} Payload080ED308;

extern u8 *func_080D9B08(void *handle);
extern void func_080D9B98(void *handle);
extern const u8 gUnknown_083992B8[];

void func_080ED308(Payload080ED308 *payload)
{
    u8 *output = func_080D9B08(payload->handle);
    u8 output_index = 0;
    u8 table_index;

    for (; output_index < payload->offset; output_index++, output += 2) {
        output[0] = 0;
        output[1] = 0x10;
    }

    table_index = 0;
    if (payload->offset < 0)
        table_index = -payload->offset;

    if (table_index <= 30) {
        const u8 *table = gUnknown_083992B8;
        do {
            output[0] = table[table_index * 2];
            output[1] = table[table_index * 2 + 1];
            table_index++;
            output_index++;
            output += 2;
        } while (output_index <= 159 && table_index <= 30);
    }

    for (; output_index <= 159; output_index++, output += 2) {
        output[0] = 0x10;
        output[1] = 0x10;
    }

    func_080D9B98(payload->handle);
}
