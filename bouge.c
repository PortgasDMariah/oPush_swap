/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bouge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:22:24 by mdouiri           #+#    #+#             */
/*   Updated: 2022/04/08 17:55:03 by mdouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include <stdlib.h>
#include <stdio.h>

int	foryou(bon *list, bon *listb) //j'ai cree cette fonction pour le cas ou le nombre a push dans la stack_A est l'element le plus grand des deux stacks
{
	int max;
	int node;
	int count;

	count = 0;
	max = list->chef->mouv;
	node = listb->tmp->mouv;
	while(max != list->fin)
	{
		if(max != 0 && node != 0 && node != listb->fin)
		{
			max--;
			node--;
		}
		else if (max != 0)
			max--;
		else if(max == 0 && node == 0)
			max = list->fin;
		else if(node == listb->fin)
			node = 0;
		else if(max == 0)
			max = list->fin;
		count++;
	}
	if(node != 0)
	{
		while(node != 0)
		{
			if(node != 0 && node != listb->fin)
			       node--;
			else if(node == listb->fin)
			{
				node = 0;
				count++;
				break;
			}
			count++;	
		}
	}
	count++;
	return(count);
	
}

int counti(bon *list, bon *listb) //je compte le nombre totale d'action si je dois push le list->tmp actuel 
{
	int maxi;//le max de node donc node se placera juste derriere max dans ma stack_a
	int nodi;//le chiffre qu'on analyse (le chiffre a push soit list->tmp)
	int count;
	
	count = 0;
	if(!(listb->tmp->data > list->chef->data))
	{
		nodi = listb->tmp->mouv;
		maxi = list->tmp->mouv;
	}
	else
	{
		count = foryou(list, listb);
		return(count);
	}
	while(maxi != 0) //tant que maxi n'est pas a le premier element de ma stack_a 
	{
		if((maxi != 0 && (maxi != list->fin) && (nodi != 0 && (nodi != listb->fin)))) //je compte pour rrr ou doublerotate. List->fin est la position du dernier element
		{
			maxi--;
			nodi--;
		}
		else if(maxi != 0 && (maxi != list->fin)) //rotate ou reverserotate dans stack_a
			maxi--;
		else if (maxi == list->fin && nodi == listb->fin)
		{
			maxi = 0;
			nodi = 0;
		}
		else if( nodi != 0 && (nodi != listb->fin)) //rotate ou reverserotate dans stack_b
			nodi--;
		else if(maxi == list->fin) 
			maxi = 0;
		else if(nodi == listb->fin)
			nodi = 0;	
		count++;
	}
	count++;//pour le push dans lista
	return(count);
}

void	foundit(bon *list, bon *listb) //je cherche le meilleur element a push
{
	int count ;
	count = 0;
	list->tmp = malloc(sizeof(t_node));
	listb->tmp = malloc(sizeof(t_node));
	listb->push = malloc(sizeof(t_node));
	
	listb->tmp = listb->head;
	list->tmp = found_your_place(list, listb->tmp->data);
	listmax(list);
	listb->count = counti(list, listb);
	listb->push = listb->tmp;
	while(listb->tmp)
	{
		list->tmp = found_your_place(list, listb->tmp->data);
		count = counti(list, listb);
		if (count <= listb->count)
		{
			listb->count = count;
			listb->push = listb->tmp; //list->push est l'element avec le moins d'actions  possible 
		}
		listb->tmp = listb->tmp->next;
		if(!listb)
			break;
	}
}



