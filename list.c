/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:25:22 by mdouiri           #+#    #+#             */
/*   Updated: 2022/04/08 17:01:42 by mdouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include <stdlib.h> 

t_node	*ft_lstnew(int content)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!new)
		return (0);
	new->data = content;
	new->lis = 1;
	new->mouv = 1;
	new->next = NULL;
	return (new);
}

int	ft_lstsize(t_node *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

t_node	*ft_lstlast(t_node *lst)
{
	int	len;
	int	i;

	if (!lst)
		return (NULL);
	i = 0;
	len = ft_lstsize(lst);
	while (i < len && ((lst->next) != NULL))
	{
		lst = lst->next;
		i++;
	}
	return ((t_node*)lst);
}


void	ft_lstadd_front(t_node **alst, t_node *new, bon *list)
{
	if (alst != NULL)
		new->next = *alst;

	*alst = new;
}


void	front(bon *lis, t_node *new)
{
	if(lis->head == NULL)
	{
		lis->head = new;
		return;
	}
	lis->head->prev = new;
	new->next = lis->head;
	new->prev = NULL;
	
	lis->head = new;
	if(lis->head->next == NULL)
		return;
	while(new->next->next != NULL)
		new = new->next;
	lis->before = new;
	lis->last = new->next;
	
}

#include <stdio.h>

void	ft_lstadd_back(t_node **alst, t_node *new, bon *list)
{
	t_node	*last;

	last = NULL;
	if (!alst && !new)
		return ;
	if (!*alst)
	{
		*alst = new;
		return;
	}
	else
	{
		last = ft_lstlast(*alst);
		last->next = new;
		new->prev = last;
	}
	list->before = last;
	list->last = last->next;
}



