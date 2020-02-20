/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   woody_woodpacker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 02:15:16 by plamtenz          #+#    #+#             */
/*   Updated: 2020/02/20 02:52:46 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bin_packer.h>

void             woody_woodpacker(int ac, char **argv)
{
    t_packer    pack;

    pack = (t_packer){ .fd = 0, .size = 0, .map = NULL, .key = NULL};
    if (ac != 2)
        error(ERR_USE, "woody_woodpacker has only one argument\n");
    read_file(argv[1], &pack);
    /* here gen a key */
    identifier_criteria_x64(&pack);
    infect_elf_file_x64(&pack);
    free_map(&pack);
}