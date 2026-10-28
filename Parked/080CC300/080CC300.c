typedef unsigned char u8;

extern u8 data_02002E64[];

/* Target: 080CC300..080CC348, 72 bytes. */
void func_080CC300(void)
{
    u8 i, j;

    for (i = 0; i < 20; i++) {
        if (data_02002E64[i] == 0) {
            for (j = i + 1; j < 20; j++) {
                if (data_02002E64[j] != 0) {
                    data_02002E64[i] = data_02002E64[j];
                    data_02002E64[j] = 0;
                    break;
                }
            }
        }
    }
}
