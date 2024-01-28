/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:48:49 by oruban            #+#    #+#             */
/*   Updated: 2024/01/28 11:38:14 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void swap(t_stack *a)
{
	if (!(a && a->next))
	{
		ft_printf("a or a->next == NULL\n"); //
		return ;
	}
	ft_printf("	a = %p\n", a);
	ft_printf("a->prev = %p\n", a->previous);
	ft_printf("a->next = %p\n", a->next);
	a = a->next;
	ft_printf("	a = %p\n", a);
	ft_printf("a->prev = %p\n", a->previous);
	ft_printf("a->next = %p\n", a->next);
	error_exit(&a);
}

size_t	stack_size(t_stack *a)
{
	size_t	i;

	i = 0;
	while (a)
	{
		i++;
		a = a->next;
	}
	return (i);
}

void	free_stack(t_stack *a)
{
	t_stack	*tmp_node;

	while (a)
	{
		tmp_node = a;
		a = tmp_node->next;
		free(tmp_node);
	}
	a = NULL;
}

/* fees memory allocated for the stack and
	 exits from the programm because of input errors 
	PARAMETERS:  pointer at the pointer to the stack
	RETURNS: 	nothing*/
void	error_exit(t_stack **a)
{
	free_stack(*a);
	ft_printf("Error\n");
	exit(1);
}

bool	issorted(t_stack *stack)
{
	while (stack->next)
	{
		if (stack->number > stack->next->number)
			return (false);
		stack = stack->next;
	}
	return (true);
}