
#include <elf64.h>
#include <woody_woodpacker.h>

static size_t       align_shift_amount(size_t payload_size, size_t alignment)
{
    return (((payload_size) + (alignment)) & ~((alignment) - 1));
}

char                calc_shift_amount(const t_data *origin, size_t *shift_amount)
{
    // get prog hdr file size and offset
    const size_t    phdr_size = endian_64bits(origin->phdr_addr->p_filesz);
    const size_t    phdr_offset = endian_64bits(origin->phdr_addr->p_offset);
    // calc last segment and payload size
    const size_t    segment_end = phdr_offset + phdr_size;
    const size_t    payload_size = end_payload - start_payload;
    // clac padding
    const size_t    seg_padding = segment_end - origin->last_section_end;

    // if true : nothing to shift
    if (seg_padding > payload_size)
        return (*shift_amount = 0);
    
    // take progrm mem size and align
    const size_t    phdr_memsize = endian_64bits(origin->phdr_addr->p_memsz);
    const size_t    phdr_align = endian_64bits(origin->phdr_adr->p_align);

    // align payload to get shift amount
    *shift_amount = align_shift_amount(payload_size, 4096);

    // realloc in clone address with new bits 
    if (!clone_reallocation(*shift_amount))
        return (0); // throw
    
    // calc end of the padding and check if is in range of align
    // align has always to be a module of page size
    const size_t    padding = (phdr_memsize % phdr_align) + shift_amount:
    
    if (padding > phdr_align)
        return (0); // ERR_USE no mem and overflow
    return (1);
}