
#include <woody_woodpacker.h>

static char         big = false;

uint16_t            endian_16bits(uint16_t x)
{
    if (!big)
        return (x);
    return ((x >> 8) | (x << 8));
}

uint32_t            endian_32bits(uint32_t x)
{
    if (!big)
        return (x);
    return ((x >> 24) | ((x & 0xff0000) >> 8) | ((x & 0xff00) << 8) | (x << 24))
}

uint64_t            endian_64bits(uint64_t x)
{
    if (!big)
        return (x);
    return ((x & 0xff00000000000000) >> 56 \
			| (x & 0x00ff000000000000) >> 40 \
			| (x & 0x0000ff0000000000) >> 24 \
			| (x & 0x000000ff00000000) >> 8 \
			| (x & 0x00000000ff000000) << 8 \
			| (x & 0x0000000000ff0000) << 24 \
			| (x & 0x000000000000ff00) << 40 \
			| (x & 0x00000000000000ff) << 56);
}

void                isbig(char _isbig)
{
    big = _isbig;
}