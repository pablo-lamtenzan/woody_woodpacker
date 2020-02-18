
#include <elf64.h>
#include <woody_woodpacker.h>

typedef static struct   s_off
{
    size_t              shift_amount;
    size_t              last_section_end;
}                       t_off;

static char             shift_phdr_addr(f_save_accessor safe, const size_t offset)
{
    Elf64_Phdr          *phdr;
    Elf64_Off           phdr_offset;

    if (!(phdr = safe(offset, sizeof(Elf64_Phdr))))
        return (0); // corrupt bad phdr offset
    // take program header offset
    phdr_offset = endian_64bits(phdr->p_offset);

    // only if phdr_offset > last_sect_end add shift to phdr_offset
    if (phdr_offset > t_off.last_section_end)
    {
        phdr_offset += t_off.shift_amount;
        phdr->p->p_offset = endian_64bits(phdr_offset);
    }
    return (1);
}

static char             shift_shdr_addr(f_save_accessor safe, const size_t offset)
{
    Elf64_Shdr          *shdr;
    Elf64_Off           shdr_offset;

    if (!(shdr = safe(offset, sizeof(Elf64_Shdr))))
        return (0); // corrupt bad phdr offset
    // take program header offset
    shdr_offset = endian_64bits(shdr->sh_offset);

    // only if phdr_offset > last_sect_end add shift to phdr_offset
    if (shdr_offset > t_off.last_section_end)
    {
        shdr_offset += t_off.shift_amount;
        shdr->p->p_offset = endian_64bits(shdr_offset);
    }
    return (1);
}

static char             adjust_phdr_off_tab(Elf64_Ehdr *elf64_hdr, size_t shift_amount, size_t last_section_end)
{
    Elf64_Off           phdr_offset;

    // offset must be > to the end of the last sequence
    if ((phdr_offset = endian_64bits(elf64_hdr->e_phoff) > last_section_end)
    {
        // add and uptate;
        phdr_offet += shift_amount;
        elf64_hdr->e_phoff = endian_64bits(phdr_offset);
    }
    return (1);
}

static char             adjust_shdr_off_tab(Elf64_Ehdr *elf64_hdr, size_t shift_amount, size_t last_section_end)
{
    Elf64_Off           shdr_offset;

    // offset must be > to the end of the last sequence
    if ((shdr_offset = endian_64bits(elf64_hdr->e_phoff) > last_section_end)
    {
        // add and uptate;
        shdr_offet += shift_amount;
        elf64_hdr->e_shoff = endian_64bits(phdr_offset);
    }
    return (1);
}

char                    adjust_offset(size_t shift_amount, const t_data *origin)
{
    Elf64_Ehdr          *elf64_hdr;

    // shitf amount == 0 no need this function, nothing to change
    if (!shift_amount)
        return (1);
    // 
    t_off.shift_amount = shift_amount;
    t_off.last_section_end = origin->last_section;

    if (!(elf64_hdr = get_clone_adrr(0, sizeof(Elf64_Ehdr)))
        return (0); // corrupt
    
    // adjust offset in header tabs first
    adjust_phdr_off_tab(elf64_hdr, shift_amount, t_off.last_section_end);
    adjust_shdr_off_tab(elf64_hdr, shif_amount, t_off.last_section_end):

    // now adjust the offset each phdr and shdr
    if (!foreach_phdr(get_clone_adrr, shift_phdr_addr)
            || !foreach_phdr(get_clone_adrr, shift_shdr_addr))
        return (0); // trow adjust offset
    return (1);
}