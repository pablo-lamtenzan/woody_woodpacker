/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier_criteria.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 03:11:43 by plamtenz          #+#    #+#             */
/*   Updated: 2020/02/20 04:21:47 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bin_packer.h>

__warn_unused_result
bool                        identifier_criteria_x64(t_packer *data)
{
    const Elf64_Ehdr        *elf64_hdr = (Elf64_Ehdr *)data->map;

    if (!elf64_hdr)
        return (error(ERR_CORUPT, "input file is not an executable file\n"));
    if (elf64_hdr->e_ident[EI_CLASS] != ELFCLASS64)
        return (error(ERR_CORUPT, "input file is not a elf64 file\n"));
    if (memcmp(elf64_hdr->e_ident, ELFMAG, SELFMAG))
        return (error(ERR_CORUPT, "input file has wrong magic number\n"));
    if (!elf64_hdr->e_entry)
        return (error(ERR_CORUPT, "input file has no entry\n"));
    if (!elf64_hdr->e_phoff)
        return (error(ERR_CORUPT, "input file has no program header table\n"));
    if (!elf64_hdr->e_shoff)
        return (error(ERR_CORUPT, "input file has no section header table\n"));
    if (*(uint32_t)&elf64_hdr->e_ident[EI_PAD] == SECRET_SIGNATURE)
        return (error(ERR_CORUPT, "input file is already packed"));
    if (elf64_hdr->e_shoff + (elf64_hdr->e_shnum * sizeof(Elf64_Shdr)) != data->size)
        return (error(ERR_CORUPT, "input file section real size and section size in header \
            aren't the same\n"));
    isbig(elf64_hdr->e_indent[EI_DATA] == ELFDATA2MSB);
    return (true);
}