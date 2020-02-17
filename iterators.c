
/* DID SHIT WITH CONST DECLARATIONS */

#include "woody_woodpacker.h"
#include "elf64.h"

char                        foreach_phdr(f_safe_accessor safe, f_iter_callback callback)
{
    const Elf64_Ehdr        *elf64_hdr;
    const Elf64_Off         phdr_offset;
    const Elf64_Half        phdr_ent_size;
    Elf64_Half              phdr_num;
    char                    ***segments;
    const size_t            segments_size;
    size_t                  elf64_seg_hdr;
    size_t                  offset;

    if ((elf64_hdr = safe(0, sizeof(Elf64_Ehdr))))
        return (0); // corrupt no elf64 header
    
    // take offset, entity size and nun of segments
    phdr_offset = endian_64bits(elf64_hdr->e_phoff);
    phdr_ent_size = endian_16bits(elf64_hdr->e_phentsize);
    phdr_num = endian_16bits(elf64_hdr->e_phnum);

    // now init the array where we ll iterate
    (*segments)[phdr_num][phdr_ent_size] = NULL;
    segments_size = phdr_ent_size * phdr_num;

    // check corruption in segment
    if (!(segments = safe(phdr_offset, segments_size)
            || phdr_ent_size < sizeof(Elf64_Phdr)
            || segments_size / phdr_ent_size != phdr_num))
        return (0); // corrupt invalid segment table
    
    // iteate using offet of segments
    while (phdr_num--)
    {
        elf64_seg_hdr = (size_t)(*segments)[phdr_num];
        offset = elf64_seg_hdr - (size_t)elf64_hdr;
        if (!callback(safe, offset))
            return (0); // trow err 
    }
    return (1);
}

char                        foreach_shdr(f_safe_accessor safe, f_iter_callback callback)
{
    const Elf64_Ehdr        *elf64_hdr;
    const Elf64_Off         shdr_offset;
    const Elf64_Half        shdr_ent_size;
    Elf64_Half              shdr_num;
    char                    ***segments;
    const size_t            segments_size;
    size_t                  elf64_seg_hdr;
    size_t                  offset;

    if ((elf64_hdr = safe(0, sizeof(Elf64_Ehdr))))
        return (0); // corrupt no elf64 header
    
    // take offset, entity size and nun of sections
    shdr_offset = endian_64bits(elf64_hdr->e_shoff);
    shdr_ent_size = endian_16bits(elf64_hdr->e_shentsize);
    shdr_num = endian_16bits(elf64_hdr->e_shnum);

    // now init the array where we ll iterate
    (*segments)[shdr_num][shdr_ent_size] = NULL;
    segments_size = shdr_ent_size * shdr_num;

    // check corruption in section
    if (!(segments = safe(shdr_offset, segments_size)
            || shdr_ent_size < sizeof(Elf64_Phdr)
            || segments_size / shdr_ent_size != shdr_num))
        return (0); // corrupt invalid segment table
    
    // iteate using offet of sections
    while (shdr_num--)
    {
        elf64_seg_hdr = (size_t)(*segments)[shdr_num];
        offset = elf64_seg_hdr - (size_t)elf64_hdr;
        if (!callback(safe, offset))
            return (0); // trow err 
    }
    return (1);
}

