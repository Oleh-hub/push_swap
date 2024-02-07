/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slarge_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 14:10:09 by oruban            #+#    #+#             */
/*   Updated: 2024/02/07 10:54:04 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// finds the pointer at the node with max node->number
t_stack	*max_number(t_stack	*lst)
{
	t_stack	*max_node;
	long	max_number;

	max_node = NULL;
	max_number = LONG_MIN;
	while (lst)
	{
		if (lst->number > max_number)
		{
			max_number = lst->number;
			max_node = lst;
		}
		lst = lst->next;
	}
	return (max_node);
}

// initializes st->above_median and lst->push_cost
void	push_cost_ini(t_stack *lst)
{
	size_t	max;

	max = stack_size(lst);
	while (lst)
	{
		if (lst->above_median)
			lst->push_cost = lst->index;
		else
			lst->push_cost = max - lst->index;
		lst = lst->next;
	}
}

// finds out the cheapest node to push and ini-s it with true
void	cheapest_ini(t_stack *lst)
{
	long	cheapest_cost;
	long	current_cost;
	t_stack	*cheapest_node;

	cheapest_cost = LONG_MAX;
	cheapest_node = NULL;
	while (lst)
	{
		if (lst->above_median == lst->target_node->above_median)
		{
			if (lst->push_cost > lst->target_node->push_cost)
				current_cost = lst->push_cost;
			else
				current_cost = lst->target_node->push_cost;
		}
		else
			current_cost = lst->push_cost + lst->target_node->push_cost;
		if (current_cost < cheapest_cost)
		{
			cheapest_cost = current_cost;
			cheapest_node = lst;
		}
		lst = lst->next;
	}
	cheapest_node->cheapest = true;
}

/* rr, ra, rb as well as rrr, rra, rrb to till the node to b pushed adn target 
are on the top of both stacks 
is PARAMETER char stack is for std output if == 'a' the node is moved from 
stack a to stack b*/
static void	node2top(t_stack *src, t_stack *dst, void (*r_rr)(t_stack **),
	char *stack_str)
{
	char	*op_str;
	
	op_str = NULL;
	while ((src->push_cost) && (src->target_node->push_cost))
	{
		if (r_rr == rotate)
			op_str = ft_strdup ("r");
		else
			op_str = ft_strdup ("rr");
		if (!op_str)
		{
			free_stack(&dst);
			error_exit(&src);
		}
		r_rr(&src);
		r_rr(&dst);
		src->push_cost--;
		src->target_node->push_cost--;
		ft_printf("%sr\n", op_str);
	}
	while ((src->push_cost)--)
	{
		r_rr(&src);
		if (*stack_str == 'a')
			ft_printf("%sa\n", op_str);
		else
			ft_printf("%sb\n", op_str);
	}
	while ((src->target_node->push_cost)--)
	{
		r_rr(&dst);
		if (*stack_str == 'a')
			ft_printf("%sb\n", op_str);
		else
			ft_printf("%sa\n", op_str);
	}
	if (op_str)
		free (op_str);
}

/* moves teh cheapest node from src inot dst using r, rr , p ... commands */
void	move_node(t_stack *src, t_stack *dst, char *stack_str)
{
	t_stack	*tmp;

	tmp = src;
	while (!(src->cheapest))
		src = src->next;
	if (src->above_median == src->target_node->above_median)
	{
		if (src->above_median)
			node2top(src, dst, rotate, stack_str);
		else
			node2top(src, dst, rrotate, stack_str);
	}
	else if (src->above_median)
	{
		while ((src->push_cost)--)
		{
			rotate(&src);
			printf("ra\n");
		}
	}
	else ;
			//
	
}
