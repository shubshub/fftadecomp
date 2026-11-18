#include "ffta.h"

typedef struct Unit Unit;
typedef struct CollectionOwner CollectionOwner;
typedef struct {
    Unit *unit;
    u8 unknown_04[0x7C];
    CollectionOwner *collections;
} BattleActor;

typedef struct {
    BattleActor *actor;
    BattleActor *target;
    BattleActor **output;
    u8 count;
    u8 mode;
} TargetList;

typedef void (*ClearBuffer)(void *destination, u32 size);
typedef u32 (*ValueCallback)(void *value, void *argument);

extern ClearBuffer const g_callbacks_0836D4B8[];
extern u8 func_080C8240(void *unit);
extern u32 func_080A95EC(void *value, void *argument);
extern void func_08099878(CollectionOwner *owner, ValueCallback callback, void *argument);
extern void func_0809985C(CollectionOwner *owner, ValueCallback callback, void *argument);

u8 func_080B41CC(BattleActor *actor, BattleActor *target, BattleActor **output, u8 mode)
{
    TargetList list;

    g_callbacks_0836D4B8[0](&list, sizeof(list));
    list.actor = actor;
    list.target = target;
    list.mode = mode;
    list.output = output;
    list.count = 0;

    if (func_080C8240(actor->unit))
        func_08099878(actor->collections, func_080A95EC, &list);
    else
        func_0809985C(actor->collections, func_080A95EC, &list);
    return list.count;
}
