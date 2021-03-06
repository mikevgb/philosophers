/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillaes <mvillaes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 21:56:44 by mvillaes          #+#    #+#             */
/*   Updated: 2021/06/17 21:56:58 by mvillaes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*ft_bzero(void *ft, size_t i)
{
	char	*ptr;

	ptr = ft;
	while (i > 0)
	{
		*ptr++ = 0;
		i--;
	}
	return (ft);
}
