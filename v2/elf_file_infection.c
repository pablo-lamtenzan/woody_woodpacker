/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf_file_infection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 03:43:44 by plamtenz          #+#    #+#             */
/*   Updated: 2020/02/19 05:26:02 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bin_packer.h"

static bool         address_detection(char *code, void *arg1 , void *arg2)
{
    if (!strcmp(code, "entry_segment"))
    {
        return (((Elf64_Ehdr *)(arg1))->e_entry < ((Elf64_Phdr *)(arg2))->sh_addr
                || (((Elf64_Ehdr *)(arg1))->e_entry > (Elf64_Phdr *)(arg2))->sh_addr
                + ((Elf64_Phdr *)(arg2))->filesz);
    }
    else if (!strcmp(code, "entry_section"))
    {
        return (((t_elf64 *)(arg1))->elf64_hdr->e_entry >= ((Elf64_Shdr *)(arg2))->sh_addr
                && ((t_elf64 *)(arg1))->elf64_hdr->e_entry < ((Rlf64_Shdr *)(arg2))->sh_addr
                + ((Rlf64_Shdr *)(arg2))->sh_size);
    }
    else if (!strcmp(code, "last_section"))
    {
        return (((t_elf64 *)(arg1))->sh_offset + ((Elf64_Shdr *)(arg2))->sh_size
                == ((t_elf64 *)(arg1))->segment.phdr_off + ((t_elf64 *)(arg2))->segment.p_filesz);
    }
    else
        error(ERR_THROW, "bad code in address_detection in elf_file_detection.c\n");
}

static bool         uptate_entry_segment(t_packer *data, t_elf64 *elf)
{
    bool            inc;
    int             it;
    Elf64_Phdr      *seg;

    inc = false;
    it = -1;
    while (++it < elf->elf64_hdr->e_phnum)
    {
        if (!(seg = goto_next_segment_x64(data, elf->elf64_hdr, it)))
            return (false);
        if (inc)
        {
            seg->p_flags |= PF_W;
            seg->p_offset += PAGE_SIZE;
        }
        if (address_detection("entry segment", elf->elf64_hdr, seg))
        {
            elf->segment.p_offset = endian_64bits(seg->p_offset);
            elf->segment.p_vaddr = endian_64bits(seg->p_vaddr);
            elf->segment.p_filesz = endian_64bits(seg->p_filesz);
            seg->p_flag |= PF_W;
            seg->p_filesz += PAYLOAD_SIZE;
            seg->p_memsz += PAYLOAD_SIZE;
            inc = true;
        }
    }
    return (true);
}

static bool         uptate_entry_section(t_packer *data, t_elf64 *elf)
{
    bool            inc;
    int             it;
    Elf64_Shdr      *sec;

    inc = false;
    it = -1;
    while (++it < elf->elf64_hdr->e_phnum)
    {
        if (!(sec = goto_next_section_x64(data, elf->elf64_hdr, it)))
            return (false);
        if (inc)
            sec->p_offset += PAGE_SIZE;
        if (address_detection("entry section", elf->elf64_hdr, sec))
        {
            elf->section.sh_offset = endian_64bits(sec->sh_offset);
            elf->section.sh_addr = endian_64bits(sec->sh_addr);
            elf->section.sh_size = endian_64bits(sec->sh_size);
        }
        if (address_detection("last section", elf->sh_offset, sec))
        {
            sec->sh_size += PAYLOAD_SIZE;
            inc = true;
        }
    }
    return (true);
}

t_elf64             *find_entry(t_packer *data)
{
    t_elf64         elf;

    elf.elf64_hdr = (Elf64_Ehdr *)pack->map;
    if (uptate_entry_segment(data, &elf))
        if (uptate_entry_section(data, &elf))
            return (&elf); // atention that can hurt
    return (NULL);
}

bool                infect_elf_file_x64(t_packer *data)
{
    t_elf64         *elf64_hdr;

    if ((elf64_hdr = find_entry(data)))
        if (update_elf64_header(elf64_hdr))
            if (create_infected_elf_x64(data, elf64_hdr))
                return (true);
    return (false);
}