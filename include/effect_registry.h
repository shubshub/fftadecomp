#ifndef GUARD_EFFECT_REGISTRY_H
#define GUARD_EFFECT_REGISTRY_H

#include "ffta.h"

typedef u32 (*EffectRegistryCallback)(void *task, void *request, void *payload);

typedef struct EffectRegistryEntry {
    EffectRegistryCallback callback;
    u16 size;
    u16 metadata;
} EffectRegistryEntry;

extern const EffectRegistryEntry data_083947D8[341];
extern const EffectRegistryEntry data_08395280[20];
void *func_080D3508(u16 id, void *object, u32 argument);

#endif
