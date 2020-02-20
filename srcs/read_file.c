/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 02:08:38 by plamtenz          #+#    #+#             */
/*   Updated: 2020/02/20 02:52:40 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bin_packer.h>

__warn_unused_result
void                    read_file(char *filename, t_packer *data)
{
	struct stat         buff;

	if ((data->fd = open(filename, O_RDONLY)) < 0)
		error(ERR_SYS, "Can't open the executable file\n");
	if (fstat(data->fd, &buff) < 0)
	{
		close(data->fd);
		error(ERR_SYS, "fstat() failed\n");
	}
	if (buff.st_mode & S_IFDIR)
	{
		close(data->fd);
		error(ERR_CORUPT, "Can't parse diectories\n");
	}
	if ((data->map = mmap(0, buff.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE,
			data->fd, 0)) == MAP_FAILED)
	{
		close(data->fd);
        error(ERR_SYS, "mmap() failed\n");
	}
	data->size = buff.st_size;
}

void				free_map(t_packer *data)
{
	if ((close(data->fd)) < 0)
		error(ERR_SYS, "Can't close the file\n");
	if (data->map)
		if (munmap(data->map, data->size))
			error(ERR_SYS, "munmap() failed\n");
}