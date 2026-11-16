// Target: complete [0x080E2398, 0x080E2750), 952 bytes:
// f0b54f464646c0b489b080460c1c151c218880204000814200d176e1814205dc00290fd0012900
// d16ce1bde10448814200d189e10130814200d1ade1b4e10000010100000126e28a0848824200d1
// abe16970ff20104010281bd1e06802210840002805d08222920013e00000ff7f0000f020000110
// 40000a0b2801d1112202e00d2800d11222802000021040002800d08ae12a70f02000011040000a
// a870f02000020240aa80208b28820004b5214904884204d860686862fbf714f800e06068a86106
// 4f022081462878162800d9dce0800003494018006887460000205739087c240e08d8240e08d824
// 0e08d8240e08d8240e08d8240e08d8240e08e4240e0800250e08d8240e0818250e08d8240e0830
// 250e0844250e085c250e0844250e0844250e0888250e0898250e08b4250e08cc250e08dc250e08
// e4250e0808260e08014801216de00000d0a68e080548a368333b1b061b0e0121009106210122f2
// f76bf892e050a58e080448a3686e331b061b0e012400940621012247e0d8a68e08044801210091
// 062101220023f2f754f8032058e0709c8e080348ab78012400940621012232e00000709c8e0804
// 4801210091062101220123f2f73ef8022042e0609c8e08084801240094062101220123f2f732f8
// 05480094072101220023f2f72bf802202fe00000609c8e0860b28e08024f02218946042025e000
// 0038573908054801240094062101220123f2f714f86c70002639e00000609c8e080121a9700348
// 0091062101220023f2f705f82ce0d0a68e08024f02208146042003e00000385739080520687000
// 261ee0064801210091062101220023f1f7eeff034f01218946062010e00000f0a78e0850573908
// 0d4801210091062101220623f1f7dcff0a4f0120814607206870298ab520400081420dd8686a00
// 21009141460191391c4a4600230ce00000f0a78e085c573908686a0021009141460191391c4a46
// 0723fdf7cefee861002e6ed000232878152806d016280ad00149ab7808e06ca68e080149012303
// e00000b0af8e08044901200090081c06210022f1f79eff54e0000050b68e08f1f70af94ee0a869
// 002849d0e869fdf797ffe861002845d108492b78980040180268002a07d0064818180178101c42
// 46f5f7d0f928622088013032e0405839089c583908286af5f7ebf9021c2a62002a28d102a92878
// 8882a878c882081c0283a8690390686a0490084a6978880080180068074a49008918098802aa43
// 4623f727fa6861208801300be000001c5c39083c5c39086869fdf7f3fe6861002801d102202080
// 002009b018bc9846a146f0bc02bc0847

#include "ffta.h"

typedef u32 (*TaskCallback080E2398)(void *task, void *descriptor, void *work);

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    void *object;
    u32 value;
    u32 flags;
    u8 unknown_10[6];
    u16 code;
    u16 level;
} Descriptor080E2398;

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    void *object;
    void *source;
    u8 unknown_0C[8];
    u16 selector;
    u16 index;
    u16 level;
    u8 unknown_1A[2];
} Request080E2398;

typedef struct {
    u8 kind;
    u8 slot;
    u8 row;
    u8 unknown_03;
    u16 high;
    u8 unknown_06[10];
    u16 level;
    u8 unknown_12[2];
    void *child;
    void *unit;
    void *loader;
    void *startup;
    void *object;
} Work080E2398;

extern const u8 data_08395720[];
extern const u8 data_08395738[];
extern const u8 data_08395750[];
extern const u8 data_0839575C[];
extern const void *const data_08395840[];
extern const u8 data_0839589C[];
extern const TaskCallback080E2398 data_08395C1C[];
extern const u16 data_08395C3C[];
extern const u8 data_088E9C60[];
extern const u8 data_088E9C70[];
extern const u8 data_088EA550[];
extern const u8 data_088EA66C[];
extern const u8 data_088EA6D0[];
extern const u8 data_088EA6D8[];
extern const u8 data_088EA7F0[];
extern const u8 data_088EAFB0[];
extern const u8 data_088EB260[];
extern const u8 data_088EB650[];

extern void *func_080DD47C(void *object);
extern void func_080D45D0(const void *record, u8 slot, u8 bank, u8 first, u8 count);
extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern void *func_080D7A70(const void *data, u8 mode, void *parent);
extern void *func_080D7ABC(void *startup);
extern void *func_08005B6C(TaskCallback080E2398 callback, u16 size,
                           void *descriptor, void *parent);
extern void *func_080E051C(void *);

u32 func_080E2398(void *task, Descriptor080E2398 *descriptor,
                  Work080E2398 *work)
{
    Request080E2398 request;
    u8 reload;
    const u8 *entries;
    u8 count;
    u16 code;

    switch (descriptor->phase) {
    case 0:
        reload = 1;
        code = descriptor->code;
        if (code == 0x7FFF)
            break;
        work->slot = 0;
        if ((code & 0xFF) == 0x10) {
            if (descriptor->flags & 2) {
                code = 0x208;
            } else {
                if (((code & 0xF00) >> 8) == 0xB)
                    code = 0x11;
                else if (((code & 0xF00) >> 8) == 0xD)
                    code = 0x12;
                if (code & 0x8000)
                    break;
            }
        }
        work->kind = code;
        work->row = (code & 0xF00) >> 8;
        work->high = code & 0xF000;
        work->level = descriptor->level;
        if (work->level <= 0x16A) {
            work->object = descriptor->object;
            work->unit = func_080DD47C(work->object);
        } else {
            work->unit = descriptor->object;
        }
        entries = data_08395720;
        count = 2;
        switch (work->kind) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 8:
        case 10:
            func_080D45D0(data_088EA6D0, 6, 1, 0, 1);
            break;
        case 6:
            func_080D45D0(data_088EA550, 6, 1, descriptor->value - 0x33, 1);
            break;
        case 7:
            func_080D45D0(data_088EA6D8, 6, 1, descriptor->value + 0x6E, 1);
            work->slot = 1;
            reload = 0;
            break;
        case 9:
            func_080D45D0(data_088E9C70, 6, 1, 0, 1);
            work->slot = 3;
            reload = 0;
            break;
        case 11:
            func_080D45D0(data_088E9C70, 6, 1, work->row, 1);
            work->slot = 1;
            reload = 0;
            break;
        case 12:
        case 14:
        case 15:
            func_080D45D0(data_088E9C60, 6, 1, 1, 1);
            work->slot = 2;
            reload = 0;
            break;
        case 13:
            func_080D45D0(data_088E9C60, 6, 1, 1, 1);
            func_080D45D0(data_088EB260, 7, 1, 0, 1);
            work->slot = 2;
            reload = 0;
            break;
        case 16:
            entries = data_08395738;
            count = 2;
            work->slot = 4;
            reload = 0;
            break;
        case 17:
            func_080D45D0(data_088E9C60, 6, 1, 1, 1);
            work->slot = 1;
            reload = 0;
            break;
        case 18:
            work->row = 1;
            func_080D45D0(data_088EA6D0, 6, 1, 0, 1);
            break;
        case 19:
            entries = data_08395738;
            count = 2;
            work->slot = 4;
            reload = 0;
            break;
        case 20:
            work->slot = 5;
            reload = 0;
            break;
        case 21:
            func_080D45D0(data_088EA7F0, 6, 1, 0, 1);
            entries = data_08395750;
            count = 1;
            work->slot = 6;
            break;
        case 22:
            func_080D45D0(data_088EA7F0, 6, 1, 6, 1);
            entries = data_0839575C;
            count = 1;
            work->slot = 7;
            break;
        }
        if (work->level <= 0x16A)
            work->loader = func_080E03F8(work->object, entries, count, 0, 0,
                                         task);
        else
            work->loader = func_080E03F8(work->object, entries, count, 7, 0,
                                         task);
        if (reload) {
            const u8 *rows;
            u8 first = 0;

            switch (work->kind) {
            case 0x15:
                rows = data_088EAFB0;
                first = 1;
                break;
            case 0x16:
                rows = data_088EB650;
                break;
            default:
                rows = data_088EA66C;
                first = work->row;
                break;
            }
            func_080D45D0(rows, 6, 0, first, 1);
        }
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        if (work->unit == 0) {
            descriptor->phase = 2;
            break;
        }
        work->loader = func_080E05DC(work->loader);
        if (work->loader)
            break;
        if (data_08395840[work->kind])
            work->startup = func_080D7A70(data_08395840[work->kind],
                                          data_0839589C[work->kind], task);
        descriptor->phase++;
        break;
    case 0x101:
        work->startup = func_080D7ABC(work->startup);
        if (work->startup)
            break;
        request.selector = work->kind;
        request.index = work->row;
        request.level = 0;
        request.object = work->unit;
        request.source = work->object;
        work->child = func_08005B6C(data_08395C1C[work->slot],
                                    data_08395C3C[work->slot], &request, task);
        descriptor->phase++;
        break;
    case 0x102:
        work->child = func_080E051C(work->child);
        if (work->child == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
