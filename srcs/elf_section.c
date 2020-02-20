/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf_section.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 02:45:10 by plamtenz          #+#    #+#             */
/*   Updated: 2020/02/20 02:51:53 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bin_packer.h>

Elf64_Shdr          *goto_next_section_x64(t_packer *data, Elf64_Ehdr *elf64_hdr, size_t sect_index)
{
    void            *addr;

    if (!((Elf64_Shdr *)addr = (Elf64_Shdr *)((char *)data->map + (elf64_hdr + sizeof(Elf64_Shdr) * actual_sect_nb)))
            || (void *)addr >= (void *)data->map + data->size)
        error(ERR_CORUPT, "section header overflow's\n");
    addr = (void *)endian_64bits((size_t)addr);
    // is endian well placed ?
    return (addr);
}

Elf32_Shdr          *goto_next_section_x32(t_packer *data, Elf32_Ehdr *elf32_hdr, size_t sect_index)
{
    void            *addr;

    if (!((Elf32_Shdr *)addr = (Elf32_Shdr *)((char *)data->map + (elf32_hdr + sizeof(Elf32_Shdr) * actual_sect_nb)))
            || (void *)addr >= (void *)data->map + data->size)
        error(ERR_CORUPT, "section header overflow's\n");
    addr = (void *)endian_64bits((size_t)addr);
    // is endian well placed  + endian for 32 bits to add ?
    return (addr);
}
