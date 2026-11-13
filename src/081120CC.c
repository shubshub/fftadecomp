#include "control_flags.h"
/* Target 0x081120CC..0x08112360, 660 bytes including literal pools. */
typedef struct { u32 unknown_00; void *argument; u32 unknown_08[5]; } SchedulerDescriptor;
typedef struct { u16 counter; u16 unknown_02; u32 unknown_04; void *argument; void *task0; void *task1; void *task2; void *task3; s16 tween0[6]; u16 tween1[6]; u16 tween2[6]; void *resource; void *object0; void *object1; void *effect; } State;
typedef struct { u16 phase; u16 unknown_02; void *argument; } Event;
extern void *func_080DAB84(int,int,int,void *);
extern void func_080D9BA8(void *,int);
extern void *func_080D3E9C(const void *,void *);
extern void func_080D3EFC(void *);
extern void func_080E0608(void *,int,int,int);
extern void func_080E064C(void *);
extern void func_080DABC4(void *,int,int,int,int,int);
extern void func_080DADFC(void *);
extern void func_080DAC40(void *,int,int,int);
typedef void SchedulerCallback(void);
extern void *func_08005B6C(SchedulerCallback *,int,SchedulerDescriptor *,void *);
extern void *func_080DFD8C(const void *,int,int,int,void *);
extern void *func_080E051C(void *);
extern void *func_080D9B64(void *);
extern void func_08111C7C(void),func_08111D50(void),func_08111DE8(void),func_08111F60(void);
extern const u8 data_0894DBDC[],data_083A33CC[];
int func_081120CC(void *owner, Event *event, State *state)
{
    SchedulerDescriptor first, second;
    switch (event->phase) {
    case 0:
        state->argument=event->argument;
        state->object0=func_080DAB84(1,0,240,owner);
        state->object1=func_080DAB84(0,0,0,owner);
        func_080D9BA8(state->object0,1);
        func_080D9BA8(state->object1,1);
        g_control_flags_03000940.win0h_hi=0;
        g_control_flags_03000940.win0h_lo=0;
        g_control_flags_03000940.win0v_hi=0;
        g_control_flags_03000940.win0v_lo=160;
        g_control_flags_03000940.win1h_hi=0;
        g_control_flags_03000940.win1h_lo=0;
        g_control_flags_03000940.win1v_hi=0;
        g_control_flags_03000940.win1v_lo=160;
        g_control_flags_03000940.winin_lo=63;
        g_control_flags_03000940.winin_hi=63;
        g_control_flags_03000940.winout_lo=31;
        g_control_flags_03000940.display |= 0x6000;
        state->resource=func_080D3E9C(data_0894DBDC,owner);
        func_080E0608(state->tween0,12,0,4);
        func_080E0608(state->tween2,40,12,4);
        break;
    case 1: break;
    case 0x100:
        func_080DABC4(state->object0,(s16)(308-state->tween0[0]),0,(s16)(-68-state->tween0[0]),248,0);
        func_080DABC4(state->object0,(s16)(state->tween0[0]+308),0,(s16)(state->tween0[0]-68),248,1);
        func_080DADFC(state->object1);
        func_080DAC40(state->object1,120,124,state->tween2[0]);
        func_080E064C(state->tween0);
        func_080E064C(state->tween2);
        if (++state->counter>5) {
            func_080D3EFC(state->resource);
            state->resource=0;
            state->task0=func_08005B6C(func_08111C7C,28,&first,owner);
            first.argument=state->argument;
            state->task1=func_08005B6C(func_08111D50,16,&first,owner);
            first.argument=&state->object0;
            state->task2=func_08005B6C(func_08111DE8,68,&first,owner);
            state->effect=func_080DFD8C(data_083A33CC,1,4,0,owner);
            state->counter=0;
            event->phase++;
        }
        break;
    case 0x101:
        func_080E064C(state->tween1);
        func_080E064C(state->tween2);
        if (state->counter<=7) state->counter++;
        else if (!(state->task0=func_080E051C(state->task0)) &&
                 !(state->task1=func_080E051C(state->task1)) &&
                 !(state->task2=func_080E051C(state->task2))) {
            state->counter=1;
            event->phase++;
        }
        break;
    case 0x102:
        if (--state->counter==0) {
            second.argument=state->argument;
            state->task3=func_08005B6C(func_08111F60,40,&second,owner);
            event->phase++;
        }
        break;
    case 0x103:
        if (!(state->object0=func_080D9B64(state->object0)) &&
            !(state->object1=func_080D9B64(state->object1)) &&
            !(state->task3=func_080E051C(state->task3))) event->phase=2;
        break;
    }
    return 0;
}
