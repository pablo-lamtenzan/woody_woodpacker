/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf_segment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 03:00:09 by plamtenz          #+#    #+#             */
/*   Updated: 2020/02/19 03:09:49 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bin_packer.h"

Elf64_Phdr              *goto_next_segment_x64(t_packer *data, Elf64_Ehdr * elf64_hdr, size_t seg_index)
{
    void                *addr;

    if ((Elf64_Phdr *)addr = (Elf64_Phdr *)((char *)data->map + (elf64_hdr + sizeof(Elf64_Phdr) * seg_index))
            || (void *addr >= (void *)data->map + data->size))
        error(ERR_CORUPT, "segment header overflow's\n");
    addr = (void *)endian_64bits((size_t)addr); // endian well placed ?
    return (addr);    
}

Elf32_Phdr              *goto_next_segment_x32(t_packer *data, Elf32_Ehdr * elf32_hdr, size_t seg_index)
{
    void                *addr;

    if ((Elf32_Phdr *)addr = (Elf32_Phdr *)((char *)data->map + (elf32_hdr + sizeof(Elf32_Phdr) * seg_index))
            || (void *addr >= (void *)data->map + data->size))
        error(ERR_CORUPT, "segment header overflow's\n");
    addr = (void *)endian_64bits((size_t)addr); // endiand 32 ?
    return (addr);   
}