/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:34:15 by oruban            #+#    #+#             */
/*   Updated: 2024/02/07 10:45:11 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// tracing function 4 debug
void	tracing_t_stack_node(t_stack *a, char *name)
{
	ft_printf("======node %s=========\n", name);
	ft_printf("%s = %p\n", name, a);
	if (!a)
		return ;
	ft_printf("%s->number = %i\n", name, a->number);
	ft_printf("%s->index = %i\n", name, a->index);
	ft_printf("%s->above_median = %i\n", name, a->above_median);
	ft_printf("%s->push_cost = %i\n", name, a->push_cost);
	ft_printf("%s->cheapest = %i\n", name, a->cheapest);
	ft_printf("%s->target_node = %p\n", name, a->target_node);
	if (a->target_node)
		ft_printf("%s->target_node->number = %d\n", name,
			a->target_node->number);
	ft_printf("%s->prev = %p\n", name, a->previous);
	ft_printf("%s->next = %p\n", name, a->next);
}

// tracing list lst
void	tracing_lst(t_stack *lst, char *name)
{
	if (!lst)
	{
		printf("list %s = NULL", name);
		return ;
	}
	while (lst)
	{
		tracing_t_stack_node(lst, name);
		lst = lst->next;
	}
}


/* void print_out(char oprtn)
{
	
} */