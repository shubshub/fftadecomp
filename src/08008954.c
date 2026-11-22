#include "ffta.h"

/* Complete [0x08008954, 0x08008D4E): 1018 bytes, 414 instructions, the
 * eleven-entry jump table at 0x08008978, five alignment halfwords and
 * nineteen literal words.
 * Target bytes:
 * 70b586b00549086880880e1c0a2800d9eee18000024940180068874688910002
 * 78890008a4890008408d0008cc890008148b0008e6890008f88a0008b08a0008
 * 328b0008f48b0008b08c0008008d000800f0d4f90748026804239380d188481c
 * d0800904c90b101c08304018038002209080bde18891000230682030007800f0
 * e7ff0006002800d1b2e100f059fa3268f8e0306800f0aafb0006040e251c3068
 * b121890040180df01bfc022c0ad0022c03dc002c00d19be13de0032d04d0042d
 * 14d038e031688ae1306822301d210170326809249480d088411cd1800004c00b
 * 131c083318180480042410e0306822301e21017032680a249480d088411cd180
 * 0004c00b131c08331818048006249480d088411cd1800004c00b181804800824
 * 9480d088411cd1800004c00b1b181c80072090805ce10848026804239380d188
 * 481cd0800904c90b101c083040180380052090804ce10000889100023468ad22
 * 9200a4180d48bf218901401800784007800f00f02bff3068b12292008018217a
 * 0ef018fd0648002100f00aff3168203108703168032088802ae1000000000002
 * 798e00083068c921890040180ff092f93068b122920080180df092fb326861e0
 * 30682030007800f043ff0006002800d10ee130680021c1800121818008e11a48
 * 0168c42080000c18c92292008d18174a88180a1c223212788b69c96900910221
 * 019102911821039104210491e82189000591012108f0f0fd02200af015fc0c48
 * 0c490af045fc0c48b0300021405e0af051fc6089e18940183f280fdc201c0021
 * 0ff0c0f80ee0000088910002c8110000e196000829970008d0200002201c0121
 * 0ff0b0f8002d05d0287cfb210140402001432974094c2068b122920080180df0
 * 2ffb2268d0880138d0800004c00b111c0831091808889080aae0000088910002
 * 08f034fe000400284dd00af0bffb00060012030c0e4c2068c92189004218002a
 * 05d0107cbf2101400420014311741804001400280eda2068c422920080180721
 * 0ff070f821680020c880042088802ae088910002002814dd2068c42189004018
 * 07210ff05ff82268d18801390023d1800904c90b101c0830401800889080d380
 * 11e02368d988481ed8800004c00b1a1c08321018008898800239d9800904c90b
 * 52181088988004480068b122920080180df0c6fa4ce00000889100023068104d
 * 4019104904223bf19ffb0f4cbf208001241831684919201c04223bf195fb2078
 * 4007800f00f022fe3068c4218900401807210ff017f83068b1229200801819e0
 * cc1b00004eba5108000000020d4cbf208001241831680c4a8918201c04223bf1
 * 73fb20784007800f00f000fe3068b121890040180df084fa31680020c8800620
 * 888005e000000002cc1b0000012000e0002006b070bc02bc0847
 */

typedef struct {
    u8 unknown_00[8];
    u8 mode;                        /* +0x08 */
    u8 unknown_09[7];
} Descriptor08008954;

typedef struct {
    u32 unknown_00;
    void *owner;                    /* +0x04 */
    u16 position;                   /* +0x08 */
    u16 extent;                     /* +0x0A */
    u16 unknown_0c;
    u16 limit;                      /* +0x0E */
    u8 flags;                       /* +0x10 */
    u8 unknown_11[3];
} Panel08008954;

typedef struct {
    u16 phase;                      /* +0x00, func_08008880 */
    u16 row;                        /* +0x02 */
    u16 state;                      /* +0x04 */
    u16 depth;                      /* +0x06 */
    u16 history[8];                 /* +0x08 */
    void *first;                    /* +0x18 */
    void *second;                   /* +0x1C */
    u8 handle;                      /* +0x20 */
    u8 count;                       /* +0x21 */
    u8 command;                     /* +0x22 */
    u8 unknown_23[0x291];
    Descriptor08008954 descriptor;  /* +0x2B4 */
    u8 window[0x2C];                /* +0x2C4 */
    u8 list[0x20];                  /* +0x2F0 */
    Panel08008954 panel;            /* +0x310 */
    Panel08008954 menu;             /* +0x324 */
    u8 unknown_338[0xE90];
    u8 dialog[0xA04];               /* +0x11C8 */
    u8 settings[4];                 /* +0x1BCC */
} State08008954;

/* The options byte at 0x02002FC0: bits 1-2 are read as a two-bit field
 * (lsls #29; lsrs #30 at 0x08008AC2, 0x08008CD4 and 0x08008D18). */
typedef struct {
    u8 unknown_0 : 1;
    u8 speed : 2;
    u8 unknown_3 : 5;
    u8 unknown_1[3];
} Options08008954;

/* The game state at 0x02000000.  Cases 6, 9 and 10 reach it through a local
 * pointer, as func_080099C4 does: the options address is formed at run time
 * from the 0x02000000 base (ldr; movs #0xbf; lsls #6; adds at 0x08008CBE and
 * 0x08008D00), not loaded as one literal. */
typedef struct {
    u8 unknown_0000[0x2FC0];
    Options08008954 options;        /* +0x2FC0 */
} Game08008954;

/* The record at 0x020020D0; func_08008818 names the s16 at +0xB0. */
typedef struct {
    u8 unknown_00[0xB0];
    s16 depth;                      /* +0xB0 */
} Control08008954;

extern State08008954 *data_02009188;
extern Game08008954 g_state_02000000;
extern Control08008954 g_state_020020D0;
extern const u8 g_table_0851BA4E[];

void func_08008D50(void);
u16 func_08008E78(u32 context);
void func_08008E94(void);
/* The call passes the state pointer: ldr r0, [r6] at 0x080089E6, ahead of
 * the bl at 0x080089E8. */
u8 func_08009140(State08008954 *state);
void func_080096E0(void);
void func_08009728(void);
u8 func_080098F4(u16 (*callback)(u32), u32 context);
void func_08009920(u8 mode);
u8 func_080099A4(u32 handle);
void func_0801174C(void *window, u32 kind, u8 index, void *first,
                   void *second, u32 x, u32 y, u32 width, u32 height,
                   u32 tile);
u16 func_08011860(void);
s8 func_08013380(void);
void func_0801339C(u16 value);
void func_08013404(u32 first, u32 second);
void func_08013428(s16 value);
void func_08016234(void *window);
void func_08017508(void *window, u8 value);
void func_08017D18(Panel08008954 *panel, u8 flags);
void func_08017E28(Panel08008954 *panel);
void *func_081443FC(void *destination, const void *source, u32 bytes);

/* The state stack, as func_0804CBB4 spells it: PUSH_STATE saves the current
 * state, POP_STATE resumes the last one saved. */
#define PUSH_STATE() \
    (data_02009188->history[data_02009188->depth++] = data_02009188->state)
#define POP_STATE() \
    (data_02009188->state = data_02009188->history[--data_02009188->depth])

/* The menu panel's flag updates are null-guarded, as func_0804F060's
 * prepare_cursor and func_0804F0F4's deactivate_cursor are: the ROM tests
 * the panel pointer before each (cmp r5, #0 at 0x08008BB8; cmp r2, #0 at
 * 0x08008C12). */
static inline void show_menu(Panel08008954 *menu)
{
    if (menu)
        menu->flags = (menu->flags & ~4) | 0x40;
}

static inline void hide_menu(Panel08008954 *menu)
{
    if (menu)
        menu->flags = (menu->flags & ~0x40) | 4;
}

/* The cases are written in the order of their bodies in the ROM (the jump
 * table at 0x08008978 lists them by value). */
u8 func_08008954(void)
{
    switch (data_02009188->state) {
    case 0:
        func_08008D50();
        data_02009188->state = 4;
        PUSH_STATE();
        data_02009188->state = 2;
        break;
    case 2:
        if (func_080099A4(data_02009188->handle)) {
            func_08008E94();
            POP_STATE();
        }
        break;
    case 4: {
        u8 selection = func_08009140(data_02009188);

        func_08016234(data_02009188->window);
        switch (selection) {
        case 0:
            break;
        case 2:
            data_02009188->state = 6;
            break;
        case 3:
            data_02009188->command = 0x1D;
            data_02009188->state = 9;
            PUSH_STATE();
            data_02009188->state = 4;
            PUSH_STATE();
            data_02009188->state = 8;
            PUSH_STATE();
            data_02009188->state = 7;
            break;
        case 4:
            data_02009188->command = 0x1E;
            data_02009188->state = 10;
            PUSH_STATE();
            data_02009188->state = 6;
            PUSH_STATE();
            data_02009188->state = 8;
            PUSH_STATE();
            data_02009188->state = 7;
            break;
        default:
            data_02009188->state = 4;
            PUSH_STATE();
            data_02009188->state = 5;
            break;
        }
        break;
    }
    case 6: {
        Descriptor08008954 *descriptor = &data_02009188->descriptor;
        Game08008954 *game = &g_state_02000000;

        func_08009920(game->options.speed);
        func_08017508(data_02009188->window, descriptor->mode);
        data_02009188->handle = func_080098F4(func_08008E78, 0);
        data_02009188->state = 3;
        break;
    }
    case 5:
        func_08017E28(&data_02009188->menu);
        func_08016234(data_02009188->window);
        POP_STATE();
        break;
    case 3:
        if (func_080099A4(data_02009188->handle)) {
            data_02009188->depth = 0;
            data_02009188->state = 1;
        }
        break;
    case 7: {
        Panel08008954 *panel = &data_02009188->panel;
        Panel08008954 *menu = &data_02009188->menu;

        func_0801174C(data_02009188->dialog, 1, data_02009188->command,
                      data_02009188->first, data_02009188->second,
                      2, 2, 24, 4, 0x3A0);
        func_0801339C(2);
        func_08013404((u32)func_080096E0, (u32)func_08009728);
        func_08013428(g_state_020020D0.depth);
        if (panel->extent + panel->limit <= 63)
            func_08017D18(panel, 0);
        else
            func_08017D18(panel, 1);
        show_menu(menu);
        func_08016234(data_02009188->window);
        POP_STATE();
        break;
    }
    case 8:
        if (func_08011860()) {
            s16 result = func_08013380();

            hide_menu(&data_02009188->menu);
            if (result < 0) {
                func_08017D18(&data_02009188->panel, 7);
                data_02009188->depth = 0;
                data_02009188->state = 4;
            } else if (result > 0) {
                func_08017D18(&data_02009188->panel, 7);
                POP_STATE();
                data_02009188->depth = 0;
            } else {
                POP_STATE();
                POP_STATE();
            }
        }
        func_08016234(data_02009188->window);
        break;
    case 9: {
        Game08008954 *game;

        func_081443FC(data_02009188->settings, g_table_0851BA4E, 4);
        game = &g_state_02000000;
        func_081443FC(&game->options, data_02009188->settings, 4);
        func_08009920(game->options.speed);
        func_08017D18(&data_02009188->panel, 7);
        func_08016234(data_02009188->window);
        data_02009188->depth = 0;
        data_02009188->state = 6;
        break;
    }
    case 10: {
        Game08008954 *game = &g_state_02000000;

        func_081443FC(&game->options, data_02009188->settings, 4);
        func_08009920(game->options.speed);
        func_08016234(data_02009188->window);
        data_02009188->depth = 0;
        data_02009188->state = 6;
        break;
    }
    case 1:
        return 1;
    }
    return 0;
}
