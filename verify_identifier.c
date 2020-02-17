#include "elf64.h"
#include "woody_woodpacker.h"

char                    check_elf64_identifier(void)
{
    const Elf64_Ehdr    *elf64_hdr = get_origin_adrr(0, sizeof(Elf64_Ehdr));

    if (!elf64_hdr
            || memcmp(elf64_hdr->e_ident, ELFMAG, SELFMAG)
            || elf64_hdr->e_ident[EI_CLASS] != ELFCLASS64
            || !elf64_hdr->e_entry
            || !elf64_hdr->e_phoff
            || !elf64_hdr->e_shoff)
        return (0); 
    
    isbig(elf64_hdr->e_indent[EI_DATA] == ELFDATA2MSB);
    return (1);
}

/* Verify if 
1) no header at all
2) wrong magic
3) no 64bits
4) no entry 
5) no pogram header table
6) no section hdr table
*/