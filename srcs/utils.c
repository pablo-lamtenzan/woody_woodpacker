/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 03:43:52 by plamtenz          #+#    #+#             */
/*   Updated: 2020/02/20 04:22:10 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <bin_packer.h>

void        insert_signature(t_packer *pack)
{
    *(uint32_t *)&pack->map[EI_PAD] = SECRET_SIGNATURE;
}

__warn_unused_result
bool        generate_key(char *key)
{
    int     fd;
    size_t  off;

    off = -1;
    if ((fd = open("/dev/random", O_RDONLY)) < 0)
    {
        while(++off < SECRET_SIZE)
            key[off] = 0x42;
        return (false);
    }
    if (read(fd, key, SECRET_SIZE) < 0)
    {
        close(fd);
        error(ERR_SYS, "read() failed\n");
    }
    if (close(fd) < 0)
        error(ERR_SYS, "close() failed\n");
    return (true);
}