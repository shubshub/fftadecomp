/* Target bytes (44):
 * 10 b5 04 1c 69 20 f0 f0 59 fa 21 68 60 68 08 70
 * 04 48 00 68 a1 68 04 4a 80 18 01 70 10 bc 01 bc
 * 00 47 00 00 28 f4 00 02 44 1d 00 00
 */
#include "ffta.h"

typedef struct {
    u8 *destination;
    u32 value_04;
    u32 value_08;
} UpdateRequest;

typedef struct {
    u8 unknown_0000[0x1D44];
    u8 selection;
} MenuContext;

extern MenuContext *data_0200F428;
extern void func_08141540(u32 sound);

void func_08051084(UpdateRequest *request)
{
    func_08141540(0x69);
    *request->destination = request->value_04;
    data_0200F428->selection = request->value_08;
}
