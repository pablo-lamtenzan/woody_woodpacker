/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 02:16:44 by plamtenz          #+#    #+#             */
/*   Updated: 2020/02/20 04:21:44 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bin_packer.h>

__warn_unused_result
bool            error(char code, char *message)
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
    return (false);
}