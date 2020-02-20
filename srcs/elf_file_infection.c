/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf_file_infection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 03:43:44 by plamtenz          #+#    #+#             */
/*   Updated: 2020/02/20 04:21:10 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bin_packer.h>

__warn_unused_result
static bool         address_detection(char *code, void *arg1 , void *arg2)
{
    if (!strcmp(code, ENTRY_SEGMENT))
    {
        return (((Elf64_Ehdr *)(arg1))->e_entry < ((Elf64_Phdr *)(arg2))->sh_addr
                || (((Elf64_Ehdr *)(arg1))->e_entry > (Elf64_Phdr *)(arg2))->sh_addr
                + ((Elf64_Phdr *)(arg2))->filesz);
    }
    else if (!strcmp(code, ENTRY_SECTION))
    {
        return (((t_elf64 *)(arg1))->elf64_hdr->e_entry >= ((Elf64_Shdr *)(arg2))->sh_addr
                && ((t_elf64 *)(arg1))->elf64_hdr->e_entry < ((Rlf64_Shdr *)(arg2))->sh_addr
                + ((Rlf64_Shdr *)(arg2))->sh_size);
    }
    else if (!strcmp(code, LAST_SECTION))
    {
        return (((t_elf64 *)(arg1))->sh_offset + ((Elf64_Shdr *)(arg2))->sh_size
                == ((t_elf64 *)(arg1))->segment.phdr_off + ((t_elf64 *)(arg2))->segment.p_filesz);
    }
    else
        return (error(ERR_THROW, "bad code in address_detection in elf_file_detection.c\n"));
}

__warn_unused_result
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
        if (address_detection(ENTRY_SEGMENT, elf->elf64_hdr, seg))
        {
            elf->segment.phdr_off = endian_64bits(seg->p_offset);
            elf->segment.phdr_addr = endian_64bits(seg->p_vaddr);
            elf->segment.phdr_filesz = endian_64bits(seg->p_filesz);
            seg->p_flag |= PF_W;
            seg->p_filesz += PAYLOAD_SIZE;
            seg->p_memsz += PAYLOAD_SIZE;
            inc = true;
        }
    }
    return (true);
}

__warn_unused_result
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
        if (address_detection(ENTRY_SECTION, elf->elf64_hdr, sec))
        {
            elf->section.shdr_off = endian_64bits(sec->sh_offset);
            elf->section.shdr_addr = endian_64bits(sec->sh_addr);
            elf->section.shdr_filesz = endian_64bits(sec->sh_size);
        }
        if (address_detection(LAST_SECTION, elf->sh_offset, sec))
        {
            sec->sh_size += PAYLOAD_SIZE;
            inc = true;
        }
    }
    return (true);
}

__warn_unused_result
t_elf64             *find_entry(t_packer *data)
{
    t_elf64         elf;

    elf.elf64_hdr = (Elf64_Ehdr *)data->map;
    if (uptate_entry_segment(data, &elf))
        if (uptate_entry_section(data, &elf))
            return (&elf);
    return (NULL);
}

__warn_unused_result
bool                infect_elf_file_x64(t_packer *data)
{
    t_elf64         *elf64_hdr;

    if ((elf64_hdr = find_entry(data)))
        if (uptade_elf64_header(elf64_hdr))
        {
            create_infected_elf_x64(data, elf64_hdr);
            return (true);
        }
    return (false);
}