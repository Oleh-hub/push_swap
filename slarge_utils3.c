/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slarge_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oruban <oruban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:48:03 by oruban            #+#    #+#             */
/*   Updated: 2024/02/06 20:24:50 by oruban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* pushes nodes from list (named stack) src into stack dst */
void	push(t_stack **src, t_stack **dst)
{
	t_stack	*tmp;

	tmp = *src;
	*src = (*src)->next;
	if (*src)
		(*src)->previous = NULL;
	if (*dst)
	{
		(*dst)->previous = tmp;
		tmp->next = *dst;
		*dst = tmp;
	}
	else
	{
		*dst = tmp;
		(*dst)->next = NULL;
		(*dst)->previous = NULL;
	}
}

//initialisation of ->index ans ->above_median elements of the stack
static void	index_median_ini(t_stack *lst)
{
	size_t	i;
	size_t	size;
	size_t	median;

	if (!lst)
		return ;
	i = 0;
	size = stack_size (lst);
	median = size / 2 + size % 2;
	while (lst)
	{
		lst->index = i;
		if (i < median)
			lst->above_median = true;
		else
			lst->above_median = false;
		lst->cheapest = false;
		lst = lst->next;
		i++;
	}
}

/* find for every node of src list the target node in dst list */
/* max is maximum number in dst
targeted indicates if the number less than src one was found in dst and 
the target_node was therefore found */
static void	target_ini(t_stack *src, t_stack *dst)
{
	t_stack	*tmp;
	bool	targeted;

	if (!src || !dst)
		return ;
	tmp = dst;
	while (src)
	{
		targeted = false;
		dst = tmp;
		while (dst)
		{
			if (dst->number < src->number && (!src->target_node
					|| dst->number > src->target_node->number))
			{
				src->target_node = dst;
				targeted = true;
			}
			dst = dst->next;
		}
		if (!targeted)
			src->target_node = max_number(tmp);
		src = src->next;
	}
}

/* initialisation (finding out the correct element to push) of both stacks b4 
sorting (moving the correct element to another stack).
wher epush_cost_ini assingns ->push_cost with the number of r or rr needed
to get to the top of the stack */
static void	stacks_ini(t_stack *a, t_stack *b)
{
	index_median_ini(a);
	index_median_ini(b);
	target_ini(a, b);
	push_cost_ini(a);
	push_cost_ini(b);
	cheapest_ini(a);
	tracing_lst(a, "a"); // 
	tracing_lst(b, "b"); // 
}

// soritng the stak when it is larger then 3 nodes
void		sort_large_stack(t_stack **a)
{
	size_t		size;
	t_stack		*b;
	int			i;

	b = NULL;
	size = 0;
	i = 2;
	size = stack_size(*a);
	while (size > 3 && !issorted(*a) && i--)
	{
		push(a, &b);
		ft_printf("pb\n");
		size--;
	}
	while (size-- > 3 && !issorted(*a))
	{
		stacks_ini(*a, b);
		move_node(*a, b);
		exit(EXIT_SUCCESS); //
	}
	ft_printf("sorted!\n");
}