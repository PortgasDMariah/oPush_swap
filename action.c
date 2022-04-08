/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:21:13 by mdouiri           #+#    #+#             */
/*   Updated: 2022/04/08 16:58:42 by mdouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

void	doublerotate(bon *list, bon *listb)
{
	ft_rotate(list);
	ft_rotate(listb);
}

void	rrr(bon *list, bon *listb)
{
	ft_rrotate(list);
	ft_rrotate(listb);
}




void	ft_delete(bon *list, t_node *node)
{
	t_node *head;
	
	head = list->head;
	list->head = list->head->next;
	free(head);
	if(list->head != NULL)
		list->head->prev = NULL;
}

void	pa(bon *list, bon *listb)
{
	pb(listb, list);
}

void pb(bon *list, bon *listb)
{
	int tmp;

	tmp = list->head->data;
	ft_delete(list, list->head);
	if(listb->head != NULL)
	{
		front(listb, ft_lstnew(tmp));
	}
	else
	{
		listb->head = ft_lstnew(tmp);
	}
}

void	ft_rrotate(bon *list)
{
	list->before = list->last->prev;
	list->before->next = NULL;

	list->last->prev = NULL;
	list->last->next = list->head;
	list->head->prev = list->last;
	//list->before->next = NULL;
	list->head = list->head->prev;
	
	list->last = list->before;
	list->before = list->before->prev;
}

void     ft_rotate(bon *list)
{
        t_node *tmp;
		t_node *node;

		node = list->head;
        tmp = list->head;

        node = node->next;
        node->prev = NULL;
        tmp->next = NULL;
        list->head = node;
	if(node->next == NULL)
	{
		tmp->prev = node;
		node->next = tmp;
		list->last = node->next;
		list->head = node;
		return;
	}
        while(node->next != NULL)
        {
                node = node->next;
                if( node->next == NULL)
                {
                        tmp->prev = node;
                        node->next = tmp;
			list->before = node;
	//		node = node->next;
			list->last = node->next;

                        return;
                }

        }

}

void	ft_swap(bon *list)
{

	list->node = list->head;

	list->node->prev = list->node->next;
        list->node->next = list->node->next->next;
        list->node = list->node->next;
        list->node = list->node->prev;
        list->node->next = list->node->prev;
        list->node->prev = NULL;
        list->node = list->node->next->next;
        list->node->prev = (list->node->prev)->next;

        list->node = list->node->prev->prev;
        list->head = list->node;
}




void	ft_swapbas(bon *list)
{
	t_node *tmp;
	t_node *node;
	tmp = list->before;

	tmp = tmp->next;

	tmp->next = tmp->prev;
	tmp->prev = tmp->prev->prev;

	list->before = tmp;


	tmp = tmp->prev;

	tmp->next = list->before;


	tmp = (tmp->next)->next;

	tmp->prev = list->before;
	tmp->next = NULL;
	list->last = tmp;
}
