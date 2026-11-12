typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct Event { u16 phase; u16 unknown_2; void *object; u8 unknown_8[12]; short option; u16 mode; };
struct State { u8 count, index, timer, option, mode; u8 unknown_5[3]; void *object; u32 tasks[2]; void *pending; };
struct Parameters { u32 unknown_0; u32 object; u32 unknown_8[3]; u16 index; u16 option; u32 unknown_24; };
extern const u8 data_08397408[];
extern void *func_080E03F8(void *, const void *, int, int, int, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern int func_080D8858(void *, int);
extern int func_080E0570(u32 *, int);
extern u32 func_080DD4A4(void *, int);
extern void func_080E6714(void);
extern u32 func_08005B6C(void (*)(void), int, void *, void *);
/* Target: 0x080E691C, complete 298-byte Thumb body.
 * f0b5474680b489b080460e1c151c338880204000834232d0834204dc002b0bd0012b29d07ae0034883423bd0013083426ad073e001010000f08a28717068a860eb701420315e0a48814201d10120e87004222879002800d00022a86805490093434601930123f9f739fd686156e000002f01000008743908ecf78eff4ee06869f9f71efe6861002848d1a8680021f1f755ff2870000600283ed00120a870308801303ae02f1c0c37381c0221f9f7d2fda8780138a870000600282fd1e86844420443e40f02a968788882e878c882a8686978f6f759fd03900a48382102aa43461ff7b6f8a4003c1920603420a8706878013068700006000e2d78a8420ed1308801300ae015670e08281c0c300221f9f7a1fd0006002801d002203080002009b008bc9846f0bc02bc0847
 */
int func_080E691C(void *owner, struct Event *event, struct State *state)
{
    struct Parameters parameters;
    switch (event->phase) {
    case 0: {
        int mode;
        state->mode = event->mode;
        state->object = event->object;
        state->option = 0;
        if (event->option == 303) state->option = 1;
        mode = 4;
        if (state->mode) mode = 0;
        state->pending = func_080E03F8(state->object, data_08397408, mode, 1, 0, owner);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 256:
        state->pending = func_080E05DC(state->pending);
        if (!state->pending) {
            state->count = func_080D8858(state->object, 0);
            if (state->count) {
                state->timer = 1;
                event->phase++;
            } else event->phase = 2;
        }
        break;
    case 257:
        func_080E0570(state->tasks, 2);
        if (--state->timer == 0) {
            u8 slot = state->tasks[0] != 0;
            parameters.index = state->index;
            parameters.option = state->option;
            parameters.object = func_080DD4A4(state->object, state->index);
            state->tasks[slot] = func_08005B6C(func_080E6714, 56, &parameters, owner);
            state->timer = 52;
            state->index++;
            if (state->index == state->count) event->phase++;
        }
        break;
    case 258:
        if ((u8)func_080E0570(state->tasks, 2)) event->phase = 2;
        break;
    }
    return 0;
}
