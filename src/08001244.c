#include "oam_lists.h"

void func_08001244(void)
{
    HideEntries(data_03002F68[data_03002F58], data_03002F60[data_03002F58]);
    HideEntries(data_03003170[data_03002F58], data_03003168[data_03002F58]);

    data_03002F60[data_03002F58] = data_03003168[data_03002F58] = 0;
}
