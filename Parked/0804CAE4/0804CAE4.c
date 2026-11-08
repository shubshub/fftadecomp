#include "ffta.h"

/* Complete [0x0804CAE4, 0x0804CBB2): 206 bytes.
 * 30b50d1c287804285ed880000149401800688746fcca040810cb040830cb040888cb0408
 * 50cb04089ccb0408054c2c20fff7a0ff206004490a682c21f5f094fb032040e044f50102
 * b8d43608064c2068002839d0fff798ff00202060fff79eff0121018005202ee044f50102
 * 01f05afa0006000e092827d1094a1168002308200870126813815189481c50810904c90b
 * 101c0c304018038019201081022012e044f5010200f014f8000600280cd0002001f03efa
 * 042006e001f034fa0006000e092801d10120287030bc01bc0047
 */

typedef struct Work0804CAE4 {
    u8 mode;
    u8 unknown_01[7];
    u16 timer;
    u16 count;
    u16 queue[16];
} Work0804CAE4;

typedef void (*BufferInitializer)(void *destination, u32 size);

extern Work0804CAE4 *data_0201F544;
extern BufferInitializer g_callbacks_0836D4B8[];

extern void *func_0804CA58(u32 bytes);
extern void func_0804CA6C(void *block);
extern u16 *func_0804CA80(void);
extern u8 func_0804E008(void);
extern void func_0804E014(u8 enabled);
extern u8 func_0804CBB4(void);

void func_0804CAE4(void *unused, u8 *state)
{
    Work0804CAE4 *work;

    switch (*state) {
    case 0:
        data_0201F544 = func_0804CA58(sizeof(Work0804CAE4));
        g_callbacks_0836D4B8[0](data_0201F544, sizeof(Work0804CAE4));
        *state = 3;
        break;
    case 1:
        if (data_0201F544 == 0)
            break;
        func_0804CA6C(data_0201F544);
        data_0201F544 = 0;
        *func_0804CA80() = 1;
        *state = 5;
        break;
    case 3:
        if (func_0804E008() != 9)
            break;
        data_0201F544->mode = 8;
        work = data_0201F544;
        work->timer = 0;
        work->queue[work->count++] = 0;
        work->timer = 25;
        *state = 2;
        break;
    case 2:
        if (!func_0804CBB4())
            break;
        func_0804E014(0);
        *state = 4;
        break;
    case 4:
        if (func_0804E008() != 9)
            break;
        *state = 1;
        break;
    }
}
