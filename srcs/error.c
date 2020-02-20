/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 02:16:44 by plamtenz          #+#    #+#             */
/*   Updated: 2020/02/20 02:52:13 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bin_packer.h>

void            error(char code, char *message)
{
    if (code == ERR_CORUPT)
        printf("Error corrupt file: %s", message);
    else if (code == ERR_SYS)
        printf("Error syscall: %s", message);
    else if (code == ERR_THROW)
        printf("Error trowed value from: %s", message);
    else if (code == ERR_USE)
        printf("Usage error: %s", message);
    else
        error(ERR_THROW, "...");
}