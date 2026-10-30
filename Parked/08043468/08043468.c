#include "ffta.h"

typedef struct {
    u8 unknown_00 : 5;
    u8 flag_20 : 1;
    u8 flag_40 : 1;
    u8 unknown_07 : 1;
    u8 unknown_01[0x8D];
    u8 field_8E;
} Window08043468;

typedef struct {
    u16 unknown_00;
    u8 result;
    u8 state;
    u8 unknown_04[0x0A];
    u16 buttons;
    u16 selection;
    u8 unknown_12[0x86];
    void *source;
    u8 unknown_9C[0x30];
} Slot08043468;

typedef struct {
    void *owner;
    Window08043468 *window;
    u8 unknown_08[0x78];
    u8 field_80;
    u8 unknown_81[0x0F];
    u16 *field_90;
    u16 *field_94;
    u8 unknown_98[0x420];
    u8 closed[6];
    u8 active[6];
    u8 unknown_4C4[0x4C0];
    Slot08043468 slots[2];
    u8 unknown_B1C[0x422];
    u8 field_F3E;
} Context08043468;

typedef struct {
    u8 busy;
    u8 field_01;
    u8 flags;
    u8 unknown_03[2];
    u8 status;
    u8 unknown_06[8];
    u16 field_0E;
    u8 unknown_10[8];
    u16 *first_plane;
    u16 *second_plane;
    u8 unknown_20[8];
    u8 stride;
    u8 unknown_29[0x0B];
    u8 field_34;
    u8 field_35;
    u8 unknown_36[0x12];
    u8 field_48;
    u8 field_49;
    u8 field_4A;
    u8 field_4B;
} Renderer08043468;

typedef struct {
    u8 unknown_00[0x10];
    u16 *field_10;
} Resources08043468;

extern Context08043468 *g_state_03002810;
extern Resources08043468 data_03002740;
extern Renderer08043468 data_030009E0[];
extern u8 data_02003CB0[];
extern u8 data_0201F4E4;

extern u32 func_08043DF4(void *object, u32 value);
extern void func_0808A268(u32 index, u32 mode, u16 *first_resource,
    u16 *second_resource, u16 *first_tiles, u16 *second_tiles,
    u32 first_offset, u32 second_offset, u32 x, u32 y, u32 width, u32 height,
    u32 source_x, u32 source_y, u32 source_width, u32 source_height,
    u32 stride, u32 rows);
extern void func_08037C84(s32 slot, void *source, u32 mode, u32 a3,
                         u32 a4, u32 a5, u32 flags, u32 a7);
extern void func_08016344(void *, u8, u8, u16, u8, u16, u8);
extern void func_08016560(void *, u8, u8, u16, u8, u16, u8);
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern u32 func_08018524(u8 *destination, u16 code, u8 variant);
extern void func_08035678(u16 value, u16 *destination, u32 count, u16 step);
extern void func_0808A604(u8 index, u8 command);
extern u32 func_08040388(s32 slot, u16 mask);
extern void func_08141540(u16 song_id);
extern void func_08035844(u32 enabled);
extern void func_080C9574(u16 bit_index, u16 enabled);
extern void func_080359E4(s32 index, u8 value);
extern void func_080358B0(u32 enabled);

/* Target [08043468, 0804393C), complete bytes:
 * f0b557464e464546e0b48fb00e900c4881460168cc200e9a161c46438819094bc2181778032f00d1f4e1032f0cdc012f
 * 00d1f9e0012f00dd0ce2002f11d03fe21028000387090000fe2f00d12fe2fe2f03dcfd2f00d10ce232e2ff2f00d117e2
 * 2ee2644a88180e9bc0180770494608684268117821204042084010704a4610684268117841204042084010700b239846
 * 49460868584a801880190068092100f075fc06252d1a6d004b461868011c94310a6890300368514800690090b4214900
 * 40180190029703974046049003210591092006900f24641b2406240e0794414608910320099009210a910b940c910d94
 * 04200c2146f084fe414a9246b22040005044434603703f485044032101709f22520052440021cb201080663050440170
 * bc2040005044012202703748504402700720bd214900514408700c20401b3349514408704b4618682b49401880190168
 * 0097019783200290012203920e9804220023f4f75bfba620400050440068ac21490051440978264a5244127800910523
 * 01930c250295c023d2f7a8fea420400050440068092300930121019102950921221cc023d2f7a8ff1a4d042001210122
 * 012348f063f9041c17483e210322d4f77dff021c281c211c0123f2f721f8134850440322027004200b2146f0dfff1048
 * 012303704946086880190e4a8018fd2165e10000be0400001c0a000040270003e009000365010000790100007b010000
 * 590100003ec00000b03c000235010000e4f401028709000009490e98fcf778feff2813d14b4618688019064940180621
 * 017018688019044a8018ff2137e10000ffff000086090000870900004b46186881190d4d481902881740002f00d1a3e0
 * 0a4a88180488002c12d16420fdf02cff0020f2f7abf84b461868811949190c8080301621017077e09209000094090000
 * 012c0fd16420fdf017ff0020f2f796f848460268901940190021018080321520107061e0022c15d16420fdf005ff0020
 * f2f784f84946086880194019002101804020012185f012ff4a46106880301421017049e0032c2bd10020f2f76ff84b46
 * 18681049401800231e2101704a46106841688e310878402210430870494608688019401903800420012146f037ff0649
 * fe2008704a4610688019044bc018fd21bde000003e0f0000e4f4010287090000042c19d16420fdf0bffe084808494018
 * 0324047004200c2146f018ff4a4610688019044bc0180470a2e00000e009000335010000870900000420012146f006ff
 * 0649ff20087006480068cc210e9a51434018044bc018fd2189e00000e4f4010210280003870900000220104000281dd0
 * 6920fdf089fe0948094a81180320087004200c2146f0e2fe0649ff2008704b461868801904494018fd2168e0e0090003
 * 35010000e4f4010287090000044a8818007803285cd10420022146f0c7fe57e0860900000c4898235b00c0180478002c
 * 4ed101200221f2f7a9f8494608688019064a8018022101704b46186880190449401804803ce00000e009000387090000
 * 92090000034bc8180078fe2804d110702ee00000530a0000ff2829d10120107026e00548982149004018007800281fd1
 * 0248007810701be0e0090003e4f401024a6810782021084310704a461068426810784021084310700120f1f7cdff0848
 * 00689723db00c0180e994018002101700fb038bc9846a146aa46f0bc01bc004710280003
 */
void func_08043468(s32 slot)
{
    switch (g_state_03002810->slots[slot].state) {
    case 0:
    {
        s32 offset;
        u8 height;

        g_state_03002810->active[slot] = 0;
        g_state_03002810->window->flag_20 = 0;
        g_state_03002810->window->flag_40 = 0;
        offset = (6 - func_08043DF4(g_state_03002810->slots[slot].source, 9)) * 2;
        height = 15 - offset;
        func_0808A268(4, 12, g_state_03002810->field_94,
            g_state_03002810->field_90, data_03002740.field_10,
            data_03002740.field_10 + 0xB4, 0, 0, 11, 3, 9, height,
            11, 3, 9, height, 9, height);
        data_030009E0[4].field_34 = 11;
        data_030009E0[4].field_35 = 3;
        data_030009E0[4].field_0E = 0xCB;
        data_030009E0[4].field_01 = 0;
        data_030009E0[4].field_48 = 1;
        data_030009E0[4].field_49 = 1;
        data_030009E0[4].field_4A = 7;
        data_030009E0[4].field_4B = 12 - offset;
        func_08037C84(slot, g_state_03002810->slots[slot].source,
                      4, 0, 0, 0, 0x83, 1);
        func_08016344(data_030009E0[4].second_plane,
            data_030009E0[4].stride, data_030009E0[4].field_4B,
            0xC0, data_030009E0[4].stride, 5, 12);
        func_08016560(data_030009E0[4].first_plane,
                      9, height, 0xC0, 9, 1, 12);
        func_08035678(0xC03E, func_0808B8E4(4, 1, 1, 1),
                      func_08018524(data_02003CB0, 0x3E, 3), 1);
        data_030009E0[4].status = 3;
        func_0808A604(4, 11);
        data_0201F4E4 = 1;
        g_state_03002810->slots[slot].state = 0xFD;
        break;
    }
    case 1:
        if (func_08040388(slot, 0xFFFF) == 0xFF) {
            g_state_03002810->slots[slot].result = 6;
            g_state_03002810->slots[slot].state = 0xFF;
        } else if (g_state_03002810->slots[slot].buttons & 1) {
            if (g_state_03002810->slots[slot].selection == 0) {
                func_08141540(100);
                func_08035844(0);
                g_state_03002810->slots[slot].buttons = 0;
                g_state_03002810->field_80 = 0x16;
            } else if (g_state_03002810->slots[slot].selection == 1) {
                func_08141540(100);
                func_08035844(0);
                g_state_03002810->slots[slot].buttons = 0;
                g_state_03002810->field_80 = 0x15;
            } else if (g_state_03002810->slots[slot].selection == 2) {
                func_08141540(100);
                func_08035844(0);
                g_state_03002810->slots[slot].buttons = 0;
                func_080C9574(0x40, 1);
                g_state_03002810->field_80 = 0x14;
            } else if (g_state_03002810->slots[slot].selection == 3) {
                func_08035844(0);
                g_state_03002810->field_F3E = 0x1E;
                g_state_03002810->window->field_8E |= 0x40;
                g_state_03002810->slots[slot].buttons = 0;
                func_0808A604(4, 1);
                data_0201F4E4 = 0xFE;
                g_state_03002810->slots[slot].state = 0xFD;
                break;
            } else if (g_state_03002810->slots[slot].selection == 4) {
                func_08141540(100);
                data_030009E0[4].status = 3;
                func_0808A604(4, 12);
                g_state_03002810->slots[slot].state = 3;
                break;
            }
            func_0808A604(4, 1);
            data_0201F4E4 = 0xFF;
            g_state_03002810->slots[slot].state = 0xFD;
        } else if (g_state_03002810->slots[slot].buttons & 2) {
            func_08141540(105);
            data_030009E0[4].status = 3;
            func_0808A604(4, 12);
            data_0201F4E4 = 0xFF;
            g_state_03002810->slots[slot].state = 0xFD;
        } else if (g_state_03002810->slots[slot].result == 3) {
            func_0808A604(4, 2);
        }
        break;
    case 3:
        if (!data_030009E0[4].busy) {
            func_080359E4(1, 2);
            g_state_03002810->slots[slot].state = 2;
            g_state_03002810->slots[slot].buttons = 0;
        }
        break;
    case 2:
        if (g_state_03002810->slots[1].state == 0xFE)
            g_state_03002810->slots[slot].state = 0xFE;
        else if (g_state_03002810->slots[1].state == 0xFF)
            g_state_03002810->slots[slot].state = 1;
        break;
    case 0xFD:
        if (!data_030009E0[4].busy)
            g_state_03002810->slots[slot].state = data_0201F4E4;
        break;
    case 0xFF:
        g_state_03002810->window->flag_20 = 1;
        g_state_03002810->window->flag_40 = 1;
        func_080358B0(1);
    case 0xFE:
        g_state_03002810->closed[slot] = 0;
        break;
    }
}
