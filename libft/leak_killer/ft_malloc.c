/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:21:26 by mzhukova          #+#    #+#             */
/*   Updated: 2024/05/04 17:21:30 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_alloc.h"

void	*ft_malloc(size_t size)
{
	t_allocs	*allocs;
	void		*ptr;

	allocs = ft_allocs(NULL);
	if (allocs == NULL)
		return (malloc(size));
	ptr = malloc(size);
	if (ptr == NULL)
	{
		printf("Memory allocation failed for %p\n", ptr);
		ft_destructor();
		exit(EXIT_FAILURE);
	}
	create_alloc(&allocs, add_alloc(ptr));
	return (ptr);
}
