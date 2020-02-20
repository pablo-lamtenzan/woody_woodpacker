#include <elf64.h>
#include <woody_woodpacker.h>

char                change_entry(const t_data *origin)
{
    Elf64_Ehdr      *hdr_clone;
    Eldf64_Addr     entry;

    if (!(hdr_clone = get_clone_adrr(0, sizeof(Elf64_Ehdr))))
        return (0); // corrupt
    
    // calc sect header, sect, entry, payload offsets and payload dist
    const Elf64_Xword   shdr_offset = endian_64bits(origin->shdr_addr->sh_offset);
    const size_t        sect_offset = origin->section_offset;
    const size_t        entry_offset = shdr_offset + sect_offset;
    const size_t        payload_offset = origin->last_shdr;
    const Elf64_Xword   payload_distance = payload_offset - entry_offset;

    // take entry
    entry = endian_64bits(hdr_clone->e_entry);

    // uptate the entry by the payload size
    entry += payload_distance;
    hdr_clone->e_entry = endian_64bits(entry);

    return (1);
}