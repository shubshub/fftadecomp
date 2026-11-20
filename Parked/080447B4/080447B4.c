#include "ffta.h"

/* Complete target: [0x080447B4, 0x08044D90), 1500 bytes, 664 instructions,
 * with the five-entry jump table at 0x080447D8 and its literal pools.
 * f0b557464e464546e0b492b011910878042800d9d3e280000149401800688746
 * d8470408ec470408b0480408d64a0408404d0408724d0408294c226829495018
 * 0078294bd1180978284d521907f0acf92168274a8918087021688a1810780028
 * 00d17ce2234a8918002008708046a14634239a464d462f684146013156464e43
 * bc19f722d200a01800888305180f0d1c022801d0042819d1124be0180078124a
 * a1180978534642465a43d219124bd21807f07af94a46116889190d4bc9180870
 * 106880190b494018002202702806000e80460528ced90120119b18706fe20000
 * 10280003bb070000bd070000c1070000be070000bf070000f50700007d4a1068
 * f825ed0040190021017011687a4a881800780818794bc0180078043d49190870
 * 00208046734d296844460134342060430918f722d20089180878c007002803d0
 * 2006000e00f0a4fa2006000e80460528e8d9002398462f1c3a68414601313420
 * 48431118f725ed004b1918888005000f002803d01878c007002804d1f820c000
 * 0918ff200870404601300006000e80460528e1d9574c2168594a88180078594b
 * c918097807f0daf801380006070e0025a84622684146013134200d1c45435119
 * f722d20088180078c007002817d0f826f60088190078ff2811d0494bc8180078
 * 04328918097807f0b9f801380006000e874204d1206840198019ff2101704046
 * 01300006000e80460528d2d900239846384daa4650460168424601323420131c
 * 4343c918f824e40009190878151cff2820d02806020e052a1cd8342189461f1c
 * 251c043c53461968cb1958190078561cff280bd01a19484670430b1819191078
 * 0978884202d15919ff2008703006020e052ae7d9404601300006000e80460528
 * c8d90025a846f820c000824619490a6841460131342041435218f723db00d018
 * 0078c007002833d0554650190078ff282ed10022342081468c460e490b68501c
 * 494641435c18554667193d78291c061cff2919d0904517d061465818084a8018
 * 084be1180078097888420dd1ff20387080460de010280003bf070000c2070000
 * bb070000bc0700003006020e052ad4d9404601300006000e80460528b6d90220
 * 4be1002000f0c2fb0006000e41420143ca0f00208046354d2968444601343420
 * 60430918f823db00c9180878ff2804d02006000e00f0aafb00222006000e8046
 * 0528e8d9002a00d129e1fff7bdfaf1f7e9fa0020f1f7eaf828684168244a8018
 * 00780130ab310870286840686c301f218af0c6ff296849688b310870002310ae
 * 00226c4628684068990024304018026004c401330f2bf5dd8ef078f9134c2068
 * 4068ab300078f1f7e9fb0006000e21684968ab310978321c8cf01afe22685168
 * a43108803378012b16d15068a930037021684a68101ca430008810844a680548
 * 50844868a430d321018032e010280003bb070000ffff00005168081ca4300088
 * 002803d0081ca930037022e0081c2430102101228df054f821684968ac310870
 * f1f7caf920684168081cac300078002809d00a1c8e3211780820404208400321
 * 0843107005e0a931002008700020fff799fa284a10684068aa30002101700023
 * 171c254da846254d3c68591c342048432218f723db00d0180078c0070b1c0028
 * 08d05019611900780978884202d16068aa300370052be7dd4546697c01200840
 * 002834d13078002831d1124c21684868a430008800282ad1104a881800780130
 * 0006000ef1f75afb0006000e1e2817d1206841688e3108781022104308702068
 * 426850780221084350706820fcf03efc0de000001028000300000002bb070000
 * 20684268517803204042084050700e4801684868041c8e342378102018400006
 * 020e002a07d1094d4819023549190078097888420cd111204042184020700420
 * 119908702be0000010280003bb070000044802700449012008700320119a1070
 * 1de00000e8f40102e9f401021048006840688e3000780721014003290fd00429
 * 01d1119b19700b490878013008700006000e052803d908480078119d287012b0
 * 38bc9846a146aa46f0bc01bc0047000010280003e8f40102e9f40102
 */

/* The 0x34-byte entry of src/080445DC.c; choice, value, next, status and
 * details are named as func_08044E44 uses them. */
struct MenuEntry {
    u16 active : 1;
    u16 pending : 1;
    u16 changed : 1;
    u16 mode : 3;
    u16 type : 4;
    u16 unknown_0a : 3;
    u16 option : 1;
    u16 unknown_0e : 2;
    u8 unknown_02;
    u8 slot;
    u8 choice;
    u8 target;
    u8 value;
    u8 next;
    u8 status;
    u8 details[0x2B];
};

struct Item;

/* items and count are named as src/08049ED0.c names them, state as
 * src/08044158.c does. */
struct Panel {
    u8 unknown_00;
    u8 unknown_01_0 : 1;
    u8 unknown_01_1 : 1;
    u8 unknown_01_2 : 6;
    u8 unknown_02[0x1E];
    u16 unknown_20;
    u16 unknown_22;
    struct Item *items[16];
    u8 unknown_64[8];
    u8 buffer[0x1F];
    u8 unknown_8B;
    u8 unknown_8C[2];
    u8 state : 3;
    u8 unknown_8E_3 : 1;
    u8 unknown_8E_4 : 1;
    u8 unknown_8E_5 : 3;
    u8 unknown_8F[0x15];
    u16 unknown_A4;
    u8 unknown_A6[3];
    u8 unknown_A9;
    u8 unknown_AA;
    u8 unknown_AB;
    u8 count;
};

struct MenuContext {
    void *unknown_000;
    struct Panel *panel;
    u8 unknown_008[0x7B0];
    struct MenuEntry entries[8];
};

struct GameState {
    u8 unknown_00[0x11];
    u8 flags;
};

extern struct MenuContext *g_state_03002810;
extern struct GameState g_state_02000000;
extern u8 data_0201F4E8;
extern u8 data_0201F4E9;

extern u8 func_0804BB5C(u8 slot, u8 resource, u8 *details);
extern u8 func_0804BB10(u8 index, u8 key);
extern void func_08044E44(u8 index);
extern u8 func_08045260(u8 index);
extern void func_0804409C(void);
extern void func_080360F8(void);
extern void func_08035D00(s32 mode);
extern u8 func_080CFAD4(u8 *output, u8 clear_count);
extern void func_080D2E60(void);
extern u8 func_08036350(u8 value);
extern u32 func_080D17C4(u32 filter, u8 selection, u8 *kind_out);
extern u32 func_080D1C94(struct Item **items, u32 limit, u8 advance);
extern void func_08035F8C(void);
extern u32 func_08044158(u32 mode);
extern void func_08141540(u16 song_id);

/* Phase 3 counts calls in data_0201F4E8 and resumes at the phase kept in
 * data_0201F4E9; both bytes are referenced only from this function. */
void func_080447B4(void *task, u8 *phase)
{
    struct Item *items[16];
    u8 kind;
    u8 i;
    u8 j;
    u8 direction;
    u8 other;
    u8 done;
    s32 k;

    switch (*phase) {
    case 0:
        g_state_03002810->entries[0].value = func_0804BB5C(
            g_state_03002810->entries[0].slot,
            g_state_03002810->entries[0].target,
            g_state_03002810->entries[0].details);
        if (g_state_03002810->entries[0].value == 0) {
            *phase = 4;
            break;
        }
        g_state_03002810->entries[0].next = 0;
        for (i = 0; i <= 5; i++) {
            if (g_state_03002810->entries[i + 1].type == 2 ||
                g_state_03002810->entries[i + 1].type == 4) {
                g_state_03002810->entries[i + 1].value = func_0804BB5C(
                    g_state_03002810->entries[i + 1].slot,
                    g_state_03002810->entries[i + 1].target,
                    g_state_03002810->entries[i + 1].details);
                g_state_03002810->entries[i + 1].next = 0;
            }
        }
        *phase = 1;
        break;
    case 1:
        g_state_03002810->entries[0].status = 0;
        g_state_03002810->entries[0].choice =
            g_state_03002810->entries[0].details[g_state_03002810->entries[0].next + 1];
        for (i = 0; i <= 5; i++) {
            if (g_state_03002810->entries[i + 1].active)
                func_08044E44(i + 1);
        }
        for (i = 0; i <= 5; i++) {
            if (g_state_03002810->entries[i + 1].type == 0 ||
                !g_state_03002810->entries[i + 1].active)
                g_state_03002810->entries[i + 1].status = 0xFF;
        }
        direction = func_0804BB10(g_state_03002810->entries[0].slot,
                                  g_state_03002810->entries[0].choice) - 1;
        for (i = 0; i <= 5; i++) {
            if (g_state_03002810->entries[i + 1].active &&
                g_state_03002810->entries[i + 1].status != 0xFF) {
                other = func_0804BB10(g_state_03002810->entries[i + 1].slot,
                                      g_state_03002810->entries[i + 1].choice) - 1;
                if (direction == other)
                    g_state_03002810->entries[i + 1].status = 0xFF;
            }
        }
        for (i = 0; i <= 5; i++) {
            if (g_state_03002810->entries[i + 1].status != 0xFF) {
                for (j = i + 1; j <= 5; j++) {
                    /* The ROM tests entry i + 1 again here, not entry j + 1
                     * (ldrb at 0x08044A00 from the outer row offset in r7,
                     * cmp/beq at 0x08044A04).  The result is the same either
                     * way: only later entries are written in this loop. */
                    if (g_state_03002810->entries[i + 1].status != 0xFF &&
                        g_state_03002810->entries[i + 1].choice ==
                        g_state_03002810->entries[j + 1].choice)
                        g_state_03002810->entries[j + 1].status = 0xFF;
                }
            }
        }
        for (i = 0; i <= 5; i++) {
            if (g_state_03002810->entries[i + 1].active &&
                g_state_03002810->entries[i + 1].status == 0xFF) {
                for (j = 0; j <= 5; j++) {
                    if (g_state_03002810->entries[j + 1].status != 0xFF && i != j &&
                        g_state_03002810->entries[i + 1].slot ==
                        g_state_03002810->entries[j + 1].choice) {
                        g_state_03002810->entries[j + 1].status = 0xFF;
                        /* Restarts the outer loop: the 0xFF just stored goes
                         * to i as well (mov r8, r0 at 0x08044AA4) and the
                         * increment at 0x08044AC6 wraps it to 0. */
                        i = 0xFF;
                        break;
                    }
                }
            }
        }
        *phase = 2;
        break;
    case 2:
        done = func_08045260(0) != 0;
        for (i = 0; i <= 5; i++) {
            if (g_state_03002810->entries[i + 1].status != 0xFF) {
                func_08045260(i + 1);
                done = 0;
            }
        }
        if (!done)
            break;
        func_0804409C();
        func_080360F8();
        func_08035D00(0);
        g_state_03002810->panel->unknown_AB = g_state_03002810->entries[0].slot + 1;
        g_state_03002810->panel->unknown_8B =
            func_080CFAD4(g_state_03002810->panel->buffer, 0x1F);
        /* The local array is cleared and never read: the ROM keeps the
         * sixteen stores (stm r4!, {r2} at 0x08044B64, r4 = sp) in a 0x40-byte
         * frame area nothing else touches. */
        for (k = 0; k <= 15; k++) {
            g_state_03002810->panel->items[k] = 0;
            items[k] = 0;
        }
        func_080D2E60();
        g_state_03002810->panel->unknown_A4 = func_080D17C4(
            func_08036350(g_state_03002810->panel->unknown_AB),
            g_state_03002810->panel->unknown_AB, &kind);
        /* Both arms that record the kind store the byte loaded at 0x08044B98
         * (strb r3 at 0x08044BA2 and 0x08044BDC). */
        if (kind == 1) {
            g_state_03002810->panel->unknown_A9 = kind;
            g_state_03002810->panel->unknown_20 = g_state_03002810->panel->unknown_A4;
            g_state_03002810->panel->unknown_22 = 0xFFFF;
            g_state_03002810->panel->unknown_A4 = 0xD3;
        } else if (g_state_03002810->panel->unknown_A4 != 0) {
            g_state_03002810->panel->unknown_A9 = kind;
        } else {
            g_state_03002810->panel->count =
                func_080D1C94(g_state_03002810->panel->items, 16, 1);
            func_08035F8C();
            if (g_state_03002810->panel->count != 0) {
                g_state_03002810->panel->state = 3;
            } else {
                g_state_03002810->panel->unknown_A9 = 0;
                func_08044158(0);
            }
        }
        g_state_03002810->panel->unknown_AA = 0;
        for (k = 0; k <= 5; k++) {
            if (g_state_03002810->entries[k + 1].active &&
                g_state_03002810->entries[k + 1].slot == g_state_03002810->entries[0].slot)
                g_state_03002810->panel->unknown_AA = k + 1;
        }
        if (!(g_state_02000000.flags & 1) && kind == 0 &&
            g_state_03002810->panel->unknown_A4 == 0) {
            if (func_08036350(g_state_03002810->entries[0].slot + 1) == 0x1E) {
                g_state_03002810->panel->unknown_8E_4 = 1;
                g_state_03002810->panel->unknown_01_1 = 1;
                func_08141540(0x68);
            } else {
                g_state_03002810->panel->unknown_01_1 = 0;
            }
        }
        if (g_state_03002810->panel->unknown_8E_4 ||
            g_state_03002810->entries[0].slot == g_state_03002810->entries[0].target) {
            g_state_03002810->panel->unknown_8E_4 = 0;
            *phase = 4;
        } else {
            data_0201F4E8 = 0;
            data_0201F4E9 = 1;
            *phase = 3;
        }
        break;
    case 3:
        if (g_state_03002810->panel->state == 3)
            break;
        if (g_state_03002810->panel->state == 4)
            *phase = 4;
        if (++data_0201F4E8 > 5)
            *phase = data_0201F4E9;
        break;
    case 4:
        break;
    }
}
