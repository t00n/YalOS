#include "pageframeallocator.h"


bool pageframe_isfree(unsigned int frame)
{
    return pageframe_list[frame>>5] & (1 << (frame & 0x1F));
}

void pageframe_free(unsigned int frame)
{
    if (! pageframe_isfree(frame)) {
        pageframe_list[frame>>5] |= (1 << (frame & 0x1F));
    }
}

void pageframe_unfree(unsigned int frame)
{
    if (pageframe_isfree(frame)) {
        pageframe_list[frame>>5] &= ~(1 << (frame & 0x1F));
    }
}

unsigned int pageframe_alloc()
{
    for (int frame = 0; frame < 1024*1024; ++frame) {
        if (pageframe_isfree(frame)) {
            pageframe_unfree(frame);
            return frame;
        }
    }
    return 0;
}