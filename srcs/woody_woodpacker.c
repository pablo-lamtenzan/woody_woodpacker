/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   woody_woodpacker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 02:15:16 by plamtenz          #+#    #+#             */
/*   Updated: 2020/02/20 04:22:15 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bin_packer.h>

__warn_unused_result
bool            woody_woodpacker(int ac, char **argv)
{
    t_packer    pack;

    pack = (t_packer){ .fd = 0, .size = 0, .map = NULL, .key = NULL};
    if (ac != 2)
        return (error(ERR_USE, "woody_woodpacker has only one argument\n"));
    if (!read_file(argv[1], &pack)
        || generate_key(pack.key)
        || identifier_criteria_x64(&pack)
        || infect_elf_file_x64(&pack)
        || free_map(&pack))
    return (false);
return (true);
}