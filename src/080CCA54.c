typedef unsigned char u8;

extern u8 data_02002E64[20];

u8 func_080CCA54(void)
{
    u8 index = 0;
    u8 count = 0;

    for (; index < 20; index++) {
        if (data_02002E64[index])
            count++;
    }
    return count;
}
