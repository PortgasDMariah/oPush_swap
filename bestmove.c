/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bestmove.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:21:50 by mdouiri           #+#    #+#             */
/*   Updated: 2022/04/08 17:42:47 by mdouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

//permet de calculer la taille de ma liste soit le nombre de noeuds
int	ft_listlen(bon *list)
{
	int	i;

	i = 0;
	list->tmp2 = malloc(sizeof(t_node));
	if(!list->tmp2)
		return(0);	
	list->tmp2 = list->head;
	while(list->tmp2)
	{
		list->tmp2 = list->tmp2->next;
		i++;
	}
	return(i);
}

//permet d'attribuer une position a chaque element que j'ai. 
void	position(bon *list)
{
	int limite;
	int i;
	int j;
	
	i = ft_listlen(list);
	limite = i / 2; // la moitie de ma liste est la limite qui va me permettre d'attribuer des position positive (si je suis en dessous de ma limite ) ou negatives( si je suis au dessus);
	list->tmp2 = list->head;
	j = -1;
	if(i == 1)
	{
		list->tmp2->mouv = 0;
		list->maxi = list->tmp2;
		list->fin = 0;
		return;
	}
	while(++j < (i - limite)) //position positive avec list->head qui a la position 0 
	{
		
		if(list->maxi != NULL && list->tmp2->data == list->maxi->data) //je fais ca pour attribuer une position a maxi que j'utilise afin de placer le nombre a push juste avant maxi
			list->maxi = list->tmp2; // maxi signifie le max du chiffre que je dois push_a et list->chef signifie le plsu grand element de ma liste
		list->tmp2->mouv = j;
		if(list->min && list->tmp2 && list->min->data == list->tmp2->data)
			list->min = list->tmp2; // j'attribue une position a list->min
		list->tmp2 = list->tmp2->next;
	}
	j = -1;
	while(limite >= 0) // position negative
	{
		
		if(list->maxi != NULL && list->tmp2->data == list->maxi->data)
			list->maxi = list->tmp2;
		list->tmp2->mouv = j;
		if(list->min && list->tmp2 && list->min->data == list->tmp2->data)
			list->min = list->tmp2;
		list->fin = list->tmp2->mouv;
		list->tmp2 = list->tmp2->next;
		if(list->tmp2 == NULL)
			break;
		j--;
		limite--;
	}
}

t_node *listmax(bon *list) // je trouve le plus grand element d'une liste
{
	list->chef = malloc(sizeof(t_node));
	list->tmp2 = list->head;
	list->chef = list->head;
	while(list->tmp2)
	{
		if(list->tmp2->data > list->chef->data)
			list->chef = list->tmp2;
		list->tmp2 = list->tmp2->next;
	}
	return(list->chef);

}

t_node *found_your_place(bon *list, int c) //je trouve la place de l'element que je souhaite push soit un element plus grand et le plus proche de mon chiffre a push et je le stock dans maxi
{
	int i = ft_listlen(list);
	listmax(list);
	if(list->chef->data < c)
		return(NULL);
	list->maxi = list->chef;
	list->tmp2 = list->head;
	while(i-- != 0)
	{
		if((list->tmp2->data < list->maxi->data) && (list->tmp2->data > c))
		{
			list->maxi = list->tmp2;
		}
		list->tmp2 = list->tmp2->next;
	}
	return(list->maxi);
}

