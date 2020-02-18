/* DID SHIT WITH CONST DECLARATIONS*/

#include <elf64.h>
#include <woody_woodpacker.h>

static t_data           *stored_entry;
static Elf64_Ehdr       *Elf64_hdr_adrr;
static Elf64_Addr       *entry_addr;

static char             shdr_entry(f_safe_accesor safe/* ? */, const size_t offset)
{
    Elf64_Shdr          *elf64_sect_hdr;
    const Elf64_Addr    shdr_addr;
    const Elf64_Xword   shdr_size;
    const Elf64_Off     phdr_offset;
    const Elf64_Off     shdr_offset;
    const Elf64_Xword   phdr_size;
    const size_t        ptload_end;
    const size_t        section_end;

    if ((elf64_sect_hdr = safe(offset, sizeof(Elf64_Shdr))))
        return (0); // corrutp bad shdr offset

    // take section header address and size
    shdr_addr = endian_64bits(elf64_sect_hdr->sh_adrr);
    shdr_size = endian_64bits(elf64_sect_hdr->sh_size);

    // uptate enty if section hearder + size > entry_addr
    if ((shdr_addr <= entry_addr && entry_addr < shdr_addr + shdr_size))
        stored_entry->addr_shdr = elf64_sect_hdr;

    // take program offset, section hdr offset and file size
    phdr_offset = endian_64bits(stored_entry->addr_phdr->p_offset);
    shdr_offset = endian_64bits(elf64_sect_hdr->sh_offset);
    phdr_size = endian_64bits(stored_entry->addr_phdr->phdr_size);

    // take end of section and of ptload
    ptload_end = phdr_offset + phdr_size;
    section_end = shdr_offset + shdr_size;

    // end of sec > last section && < end of ptload take it
    if (section_end <= ptload_end && section_end > stored_entry->last_section_end)
    {
        stored_entry->last_shdr = elf64_sect_hdr;
        stored_entry->last_section_end = section_end;
    }
    return (1);
}

static char             phdr_entry(f_safe_accessor safe, const size_t offset)
{
    Elf64_Phdr          *elf64_seg_hdr;
    const Elf64_Addr    phdr_addr;
    const Elf64_Xword   phdr_size;

    if (!(elf64_seg_hdr = safe(offset, sizeof(Elf64_Phdr))))
        return (0); // corrupt file bad offset

    // take program header addr and size 
    phdr_addr = endian_64bits(elf64_seg_hdr->p_vaddr);
    phdr_size = endian_64bits(elf64_seg_hdr->p_memsz);

    // phdr_addr +  phdr_size > entry
    if (phdr_addr <= entry_addr && phdr_addr + phdr_size > entry_addr)
        stored_entry->phdr_addr = elf64_seg_hdr
    return (1);
}

char                    get_entry(t_data *origin, f_safe_accesor safe)
{
    const Elf64_Addr    shdr_addr;

    if (!(Elf64_hdr_adrr = safe(0; sizeof(Elf64_Ehdr))))
        return (0); // corrupt no elf64 header
    
    entry_addr = endian_32bits(Elf64_hdr_adrr->e_entry);
    bzero(origin, sizeof(t_data));
    stored_entry = oringin;

    //apply foreach to phdr and shdr to get both entries
    if (!foreach_phdr(safe, phdr_entry))
        return (0); //trow
    if (!origin->phdr_addr)
        return (0); // corrupt missing segment
    if (!foreach_shdr(safe, shdr_entry))
        return (0); //trow
    if (!origin->shdr_addr)
        return (0); // corrupt missing section

    // take section adrr
    shdr_addr = endian_64bits(origin->shdr_addr->sh_addr);
    // use it to get the entry offset
    origin->section_offset = entry_addr - shdr_addr;

    // check if there is no section in entry segment
    if (!origin->last_section_end)
        return (0); // corrupt
}