#include "ffta.h"

typedef struct TransferRecord TransferRecord;
typedef void (*BufferCopier)(void *destination, const void *source, u32 size);

typedef struct {
    s16 from[3];
    s16 to[3];
    void *owner;
    u16 tile;
    void *menu;
    void *object;
    void *sprite;
    u8 transfer[0x1C];
    void *graphics;
    u8 palette[8];
} State080A0FF0;

extern void (*data_08394030[])(void *, void *);
extern BufferCopier const data_0836D4BC[];
extern const u8 data_083943B4[8];
extern const void *const data_083943BC[];
extern void *func_08021B1C(void *owner);
extern s32 func_08021C90(void *owner, u32 alternate, s32 step);
extern void *func_08021B9C(void *menu);
extern void func_08021C84(void *object, u16 first, u16 second);
extern void *func_0808F79C(void);
extern u32 func_08021DA0(void *object, void *value);
extern void func_08021D98(void *menu, void *object);
extern void func_08021DE4(void *object, u16 clear, u16 set);
extern void *func_08022840(u32 size);
extern u16 func_08141860(s16 horizontal, s16 vertical);
extern s32 func_08005318(const void *data, u8 *output, u16 start, u16 count);
extern void func_08000ADC(TransferRecord *entry, const void *source,
                          void *destination, u16 words);

/* Complete [0x080A0FF0, 0x080A10D4): 228 bytes.
 * 30b5051ce86880f791fd6861e8680121202280f745fe041c2c82686980f7c6fda861
 * 2404240c211c202280f733feeef7bdfbe861264a69691268a1f00ff925482c1c4034
 * 24490368201c0822a1f008f9a869211c80f7acfe6869a96980f7a4fea8690021402280
 * f7c5fe8020c00081f7effbe8630621685e0023ea5e0a24295f04242b5f801a00040014
 * c91a09040914a0f0eefb0004000e0830ff21084000090e49800040180068e96b002200
 * 2364f73bf9281c2030e96b2a8a5201084bd21880235b005ff712fd30bc01bc00470000
 * 30403908bcd43608b4433908bc43390800000106
 */
void func_080A0FF0(State080A0FF0 *state)
{
    s32 tile;
    s32 to_x;
    s32 from_x;
    s32 to_z;
    s32 from_z;
    u32 direction;

    state->menu = func_08021B1C(state->owner);
    tile = func_08021C90(state->owner, 1, 0x20);
    state->tile = tile;
    state->object = func_08021B9C(state->menu);
    func_08021C84(state->object, tile, 0x20);
    state->sprite = func_0808F79C();
    data_08394030[0](state->sprite, state->menu);
    data_0836D4BC[0](state->palette, data_083943B4, sizeof(state->palette));
    func_08021DA0(state->object, state->palette);
    func_08021D98(state->menu, state->object);
    func_08021DE4(state->object, 0, 0x40);
    state->graphics = func_08022840(0x400);
    to_x = state->to[0];
    from_x = state->from[0];
    to_z = state->to[2];
    from_z = state->from[2];
    direction = func_08141860(to_x - from_x, to_z - from_z) >> 8;
    direction = ((direction + 8) & 0xFF) >> 4;
    func_08005318(data_083943BC[direction], state->graphics, 0, 0);
    func_08000ADC((TransferRecord *)state->transfer, state->graphics,
                  (u8 *)0x06010000 + (state->tile << 5), 0x100);
}
