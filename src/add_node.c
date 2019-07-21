/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_node.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: krioliin <krioliin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/28 17:49:50 by krioliin       #+#    #+#                */
/*   Updated: 2019/07/21 23:32:47 by krioliin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

t_spot	*creat_node(int y, int x)
{
	t_spot *new_node;

	new_node = (t_spot *)ft_memalloc(sizeof(t_spot));
	new_node->x = x - 4;
	new_node->y = y;
	if (PRINT)
		printf("TRUE x = %d y = %d\n", new_node->x, new_node->y);
	new_node->next = NULL;
	return (new_node);
}

void	add_spot(t_spot **spot_top, int y, int x)
{
	t_spot *current;

	if (*spot_top == NULL)
		(*spot_top) = creat_node(y, x);
	current = *spot_top;
	while (current->next)
		current = current->next;
	current->next =  creat_node(y, x);
}
