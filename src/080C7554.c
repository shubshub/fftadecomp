#include "ffta.h"

typedef struct ListSource ListSource;
typedef struct InitializerState InitializerState;

extern void func_080C68EC(InitializerState *state, ListSource *source);

void func_080C7554(InitializerState *state, ListSource *source)
{
    func_080C68EC(state, source);
}
