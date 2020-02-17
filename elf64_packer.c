
#include "elf64.h"
#include "woody_woodpacker.h"

char            elf64_packer(size_t origin_file_size)
{
    t_data *entry;
    size_t shift_amount;

    if (!get_entry(&entry, get_origin_adrr)
            || !calc_shift_amount(&entry, &shift_amount)
            || !copy_into_clone(entry.last_section, shift_amount, origin_file_size)
            || !adjust_offset(shift_amount, &entry)
            || !adjust_sizes(shift_amount)
            || setup_payload(&entry)
            || change_entry(&entry))
        return (0); // throw 
    return (1);
}