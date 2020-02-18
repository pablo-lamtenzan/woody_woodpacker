
#include <elf64.h>
#include <woody_woodpacker.h>

static char         copy_sections(size_t last_section_end)
{
    void            *origin;
    void            *clone;

    // take origin addr
    if (!(origin = get_origin_adrr(0, last_section_end)))
        return (0); // corrupt truncated file
    if (!(clone = get_clone_adrr(0, last_section_end)))
        return (0); // corrupt

    // simply copy origin to clone
    memcpy(clone, origin, last_section_end);
    return (1);
}
// not sure if data is a good name
static char         copy_data(size_t last_section_end, size_t shift_amount, size_t origin_size)
{
    void            *origin;
    void            *clone;
    const size_t    avalaible_size = origin_size - last_section_end;

    // take origin addr
    if (!(origin = get_origin_adrr(last_section_end, avalaible_size)))
        return (0); // corrupt truncated file
    if (!(clone = get_clone_adrr(last_section_end + shift_amount, avalaible_size)))
        return (0); // corrupt

    // simply copy origin to clone
    memcpy(clone, origin, avalaible_size);
}

char                copy_into_clone(size_t last_section_end, size_t shift_amount, size_t origin_size)
{
    if (!copy_sections(last_section_end)
            || !copy_data(last_section_end, shift_amount, origin_size))
        return (0); // throw err copy to clone
    return (1);
}