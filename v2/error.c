/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 02:16:44 by plamtenz          #+#    #+#             */
/*   Updated: 2020/02/19 02:24:28 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bin_packer.h"

void            error(char *code, char *message)
{
    (void)message;
    (void)code;
    exit(EXIT_FAILURE);
}