
#include <woody_woodpacker.h>
#include <elf64.h>

char                adjust_sizes(size_t shift_amount)
{
    t_data          clone;
    Elf64_Xword     phdr_fsize;
    Elf64_Xword     phdr_memsize;
    size_t          shdr_size;

    const size_t    payload_size = end_payload - start_payload;
    // find entry in clone and deference for store
    if (!get_entry(&clone, get_clone_adrr))
        return (0); // throw adjust sizes
    
    // take sec header size, prog header size and mem size
    shdr_size = endian_64bits(clone.shdr_addr->sh_size);
    phdr_fsize = endian_64bits(clone.phdr_addr->p_filesz);
    phdr_memsize = endian_64bits(clone.phdr_addr->p_memsz);

    // add sizes
    shdr_size += endian_64bits(clone.last_shdr->sh_size);
    phdr_fsize += endian_64bits(clone.phdr_addr->p_filesz);
    phdr_memsize += endian_64bits(clone.phdr_addr->p_memsz);
    
    // store it
    clone.last_shdr->sh_size = endian_64bits(shdr_size);
    clone.phdr_addr->p_filesz = endian_64bits(phdr_fsize);
    clone.phdr_addr->p_memsz = endian_64bits(phdr_memsize);

    return (1);
}
