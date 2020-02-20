/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 05:11:50 by plamtenz          #+#    #+#             */
/*   Updated: 2020/02/20 04:21:14 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bin_packer.h>

__warn_unused_result
bool            uptade_elf64_header(t_elf64 *elf64_hdr)
{
    *(uint32_t *)&elf64_hdr->elf64_hdr->e_ident[EI_PAD] = SECRET_SIGNATURE;
    
    elf64_hdr->elf64_hdr->e_shoff += PAGE_SIZE;
    elf64_hdr->original_entry = elf64_hdr->elf64_hdr->e_entry;
    elf64_hdr->elf64_hdr->e_entry = elf64_hdr->segment.phdr_addr + elf64_hdr->segment.phdr_filesz;
    return (true);
}