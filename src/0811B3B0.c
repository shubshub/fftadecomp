/* Target: complete [0x0811B3B0, 0x0811B764), 948 bytes, 402 instructions,
 * including six literal pools.
 * f0b557464e464546e0b48db00a900b91171c098880204000814228d0814204dc00290ed0
 * 01291fd0bbe181204000814200d137e181422fdb0130814200d1ade1afe1074801210a9a
 * bcf73afb7862054801210091062100220023b9f7e1f8a0e1186a3a08a4b48e08b8f7def8
 * 99e1786abcf74cfb7862002800d092e1044a054b0a98009001200621bdf70efb38627ae1
 * 0050000600580006386abdf74ffb3862002800d07de13e1c28360020311c02f7abfe3822
 * d21990460120414602f7a4fe6c46123404a8211cbdf70efb434618783a25ed19aa462a78
 * 04a900254b5f0025615f0091c025ed040195584902910021bcf71ef830782a21c9198946
 * 0a780c9204a900228b5e9c460023e15e009101954f49029100210c9a6346bcf709f8381c
 * 39300178544622783c257b5f3e24385f0090386c0190786c02900220bbf7f8ff381c2930
 * 01784d462a782c203b5e2e24385f0090386b0190786b02900320bbf7e7ff0220e8f648f8
 * 3a4da94629880143002429800320e8f63ff829880143298049463b3108780c7001390878
 * f020087005310878a02008704a463e32117810703078e8f63df8041c41460878e8f638f8
 * 04433f25281ca0434a464232117810704946443108783f2008703078e8f628f8041c4246
 * 1078e8f623f80443a5434946453108780d704b4618888024a401211c084380252d02291c
 * 0843188005200090381c0c300190144802900a9803907820002100220123baf767fdb860
 * 0f4d2e8805ac69461531201c03f77cf8207840014419b8f705fa0006002811d0b8f78af9
 * 211c602226f03af90fe00000005800060050000640090003246a3a086038000301204042
 * 211cfef609ff0b4806800b4801210091062100220023b8f7d1ff08480a99009101210422
 * 0023c4f7a7fbb8640b9a1088013083e060380003a4b48e089c6a3a0806ad0d49281c0522
 * 28f0cefe08ac0b49201c052228f0c8fe38880130388000220004000c2b7898420cd10548
 * 21783f300278017016e00000889f14088d9f140840090003501c0006020e042a0ad8a918
 * 388809788842f5d12449a01802783f3108780a70b868baf73bfdb860002846d1381c3830
 * 0078391c393109783a1c3a3212783c243b5f3e257c5f00943c6c01947c6c0294bbf7fafe
 * 381c28300078391c293109783a1c2a3212782c243b5f2e257c5f00943c6b01947c6b0294
 * bbf7e6fe0220e7f647ff094c2188814321800320e7f640ff218881430548014005480140
 * 21800b9908880130088008e040090003ffdf0000ff7f000002200b9a108000200db038bc
 * 9846a146aa46f0bc02bc0847
 */
#include "ffta.h"
#include "control_flags.h"

typedef struct {
    u16 phase;
} Event;

/* The 16-byte record func_0801E1B8 fills for one background layer. */
typedef struct {
    u8 layer;
    u8 format;
    u8 mode;
    u8 unknown_03;
    u16 x;
    u16 y;
    void *resource;
    void *tilemap;
} Layer;

typedef struct {
    u16 timer;
    u8 unknown_02[6];
    void *coordinate_child;
    u32 unknown_0c[5];
    void *transition;
    void *startup;
    Layer first;
    Layer second;
    void *record_task;
} State;

extern u16 data_03003860[][16];
extern u8 data_06005000[];
extern u8 data_06005800[];
extern const u8 data_083A6A18[];
extern const u8 data_083A6A24[];
extern const u8 data_083A6A9C[];
extern const u8 data_088EB4A4[];

extern void *func_080D7A70(const void *, u8, void *);
extern void *func_080D7ABC(void *);
extern void func_080D45D0(const void *, u8, u8, u8, u8);
extern void func_080D35D8(void);
extern void *func_080D8A58(u8 mode, u8 palette, void *first_destination,
                           void *second_destination, void *parent);
extern void *func_080D8AEC(void *task);
extern void func_0801E1B8(u8 layer, Layer *output);
extern void func_080D8A98(u16 *first_output, u16 *second_output);
extern void func_080D74E0(u8 first, u8 second, u8 third, s16 x, s16 y,
                          void *first_buffer, void *second_buffer);
extern u16 func_080035A8(u8 index);
extern u16 func_080035D0(u8);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080D6134(void *);
extern void func_0801E6D4(u8 *first, u8 *second);
extern u8 func_080D39F0(void);
extern void *func_080D3904(void);
extern void func_0814186C(const void *, void *, u32);
extern void func_0801A42C(s16 index, void *destination);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
/* agbcc copies the initialised arrays of phase 0x102 from .rodata
 * (0x08149F88, 0x08149F8D) with memcpy, the ROM's func_081443FC. */
extern void *memcpy(void *, const void *, unsigned long);

u32 func_0811B3B0(void *task, Event *event, State *s)
{
    switch (event->phase) {
    case 0:
        s->startup = func_080D7A70(data_083A6A18, 1, task);
        func_080D45D0(data_088EB4A4, 6, 0, 0, 1);
        break;
    case 1:
        func_080D35D8();
        break;
    case 0x100:
        s->startup = func_080D7ABC(s->startup);
        if (s->startup == 0) {
            s->transition = func_080D8A58(1, 6, data_06005000, data_06005800,
                                          task);
            event->phase++;
        }
        break;
    case 0x101:
        s->transition = func_080D8AEC(s->transition);
        if (s->transition == 0) {
            u16 x, y;
            u8 first, count;
            u16 saved;
            u16 *destination;

            func_0801E1B8(0, &s->first);
            func_0801E1B8(1, &s->second);
            func_080D8A98(&x, &y);
            func_080D74E0(s->second.layer, 0, s->second.mode, x, y,
                          (void *)0x06000000, data_06005800);
            func_080D74E0(s->first.layer, 0, s->first.mode, x, y,
                          (void *)0x06000000, data_06005000);
            func_080D74E0(2, s->second.format, s->second.mode, s->second.x,
                          s->second.y, s->second.resource, s->second.tilemap);
            func_080D74E0(3, s->first.format, s->first.mode, s->first.x,
                          s->first.y, s->first.resource, s->first.tilemap);
            g_control_flags_03000940.display |= func_080035A8(2);
            g_control_flags_03000940.display |= func_080035A8(3);
            g_control_flags_03000940.win0h_hi = 0;
            g_control_flags_03000940.win0h_lo = 0xf0;
            g_control_flags_03000940.win0v_hi = 0xa0;
            g_control_flags_03000940.win0v_lo = 0xa0;
            g_control_flags_03000940.winin_lo =
                0x3f & ~(func_080035D0(s->first.layer)
                         | func_080035D0(s->second.layer));
            g_control_flags_03000940.winout_lo = 0x3f;
            g_control_flags_03000940.winout_hi =
                0x3f & ~(func_080035D0(s->first.layer)
                         | func_080035D0(s->second.layer));
            g_control_flags_03000940.display |= 0x2000;
            g_control_flags_03000940.display |= 0x8000;
            s->coordinate_child = func_080D6098(0x78, 0, 0, 1, 5, s->unknown_0c,
                                                data_083A6A24, task);
            saved = data_03003860[0][0];
            func_0801E6D4(&first, &count);
            destination = data_03003860[first];
            if (func_080D39F0())
                func_0814186C(func_080D3904(), destination, 0x60);
            else
                func_0801A42C(-1, destination);
            data_03003860[0][0] = saved;
            func_080D45D0(data_088EB4A4, 6, 0, 0, 1);
            s->record_task = func_080DFD8C(data_083A6A9C, 1, 4, 0, task);
            event->phase++;
        }
        break;
    case 0x102:
    {
        u8 timers[5] = {39, 51, 63, 75, 87};
        u8 heights[5] = {0x80, 0x60, 0x40, 0x20, 0};
        u8 i;

        s->timer++;
        for (i = 0; i < 5; i++) {
            if (s->timer == timers[i]) {
                g_control_flags_03000940.win0v_hi = heights[i];
                break;
            }
        }
        s->coordinate_child = func_080D6134(s->coordinate_child);
        if (s->coordinate_child == 0) {
            func_080D74E0(s->second.layer, s->second.format, s->second.mode,
                          s->second.x, s->second.y, s->second.resource,
                          s->second.tilemap);
            func_080D74E0(s->first.layer, s->first.format, s->first.mode,
                          s->first.x, s->first.y, s->first.resource,
                          s->first.tilemap);
            g_control_flags_03000940.display &= ~func_080035A8(2);
            g_control_flags_03000940.display &= ~func_080035A8(3);
            g_control_flags_03000940.display &= 0xdfff;
            g_control_flags_03000940.display &= 0x7fff;
            event->phase++;
        }
        break;
    }
    case 0x103:
        event->phase = 2;
        break;
    }
    return 0;
}
