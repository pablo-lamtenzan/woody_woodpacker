
#include <woody_woodpacker.h>

/* put this in a header an dinclude it to wwpck.c */
typedef static const struct     t_format[FRMT_SIZE] =
{
    [FRMT_ELF64] = {elf64_identifier, elf64_packer},
    [FRMT_ELF32] = {elf32_identifier, elf32_packer},
	[FRMT_MACHO64] = {macho64_identifier, macho64_packer},
	[FRMT_MACHO32] = {macho32_identifier, macho32_packer},
	//[FRMT_PE64] = {pe64_identifier, pe64_packer},
	//[FRMT_PE32] = {pe32_identifier, pe32_packer},
};

size_t                          get_format(void)
{
    int                         i;

    i = -1;
    while (++i < FRMT_SIZE)
        if (t_format[i].format_identifier()) /* TO DO */
            return (i);
    return (FRMT_SIZE);
} 