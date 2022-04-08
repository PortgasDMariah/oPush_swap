/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:24:36 by mdouiri           #+#    #+#             */
/*   Updated: 2022/04/08 18:11:41 by mdouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "struct.h"
#include <stdlib.h>

int	ft_many(bon *list) //je crois que je ne l'utilise pas 
{
	position(list);
	int count = 0;
	int place;
       if(list->tmp)	
	place = list->tmp->mouv;
	while(place != 0)
	{
		if( place > 0 || place < 0 && place != list->fin)
			place--;
		else if( place == list->fin)
			place = 0;
		count++;
	}
	count++;
	return(count);
}




void    firstone(bon *list, bon *listb, t_node *c) //je push mex element dans la stack_b de maniere a faire le moins de mouv possible 
{
        position(list);
        if( c->mouv < 0)
        {
                while(list->head->data != c->data)
		{
                        ft_rrotate(list);
			list->action++;
		}
        }
        else if(c->mouv > 0)
	{
                while(list->head->data != c->data)
		{
                        ft_rotate(list);
			list->action++;
		}
	}
        pb(list, listb);//c'est un pa
	list->action++;
}

void	bienfait(bon *list, bon *listtmp, bon *listb)
{
	int i;
	int j;
	int max;
	int who;
	t_node *wha;

	i = 1;
	list->tmp2 = malloc(sizeof(t_node));
	list->tmp = list->head;// l'equivalent d'un index i 
	list->tmp2 = list->head;
	list->tmp2 = list->tmp2->next;// l'equivalent d'un j et pour l'instant j = i + 1 
	max = 1;
	//who = 0;
	wha = (void *)'c';
	while(i <= list->tot) //voici comment j'effectue ma lis
	{
		while(list->tmp->data != list->tmp2->data) //tant que i != j
		{
			if(list->tmp->data < list->tmp2->data) // si i < j 
			{
				if(list->tmp2->lis <= (list->tmp->lis + 1)) //chaque element au depart a une lis qui vaut 1 
					list->tmp2->lis = list->tmp->lis + 1;//ici je change leur lis 

				if((list->tmp->lis + 1) >= max) //puis ici ca devient ou non ma lis max
				{
					max = list->tmp2->lis;
					who = list->tmp2->data;
				}
			}
			list->tmp = list->tmp->next; //je fais i++
			if(list->tmp->data == list->tmp2->data) //si i = j alors j'ai parcouru jusqu'a j donc je remets a 0 i et je sors 
			{
				list->tmp = list->head;
				break;
			}
		}
		if(list->tmp2->data == list->last->data) //si je calculer l'integralite de ma stack alors je sors
			break;
		else //si c'est pas le cas alors j++
		{
			list->tmp2 = list->tmp2->next; // 
			i++;
		}
	}
	//maintenant que j'ai ma lis, il faut que je separe l'element qui appartiennent pas a ma lis et que je les mettent dans ma stack_b
	while(list->tmp2->data != who) // tant que tu n'es pas l'element avec la lis maximum alors je parcours
	{
		list->tmp2 = list->tmp2->prev;
		if(list->tmp2->data == who )
			break;
	}
	//listtmp->head = ft_lstnew(list->tmp2->data);
	list->tmp = list->tmp2; //donc ici mon tmp vaut l'element avec ma lis maximum
      	while(list->tmp2) // donc tous les elements qui sont apres mon lixmax, je change leur lis a -1 pcq je compte les push dans la stack_b vu qu'ils font pas parti de ma lis
	{
		if(list->tmp2->data != who)
		{
			list->tmp2->lis = -1;
			//counti = ft_many(list);
			//wha = list->tmp2->data;
		}
		list->tmp2 = list->tmp2->next;
	}
	list->tmp2 = list->tmp; //mon tmp2 prend la valeur de mon lismax
	list->tmp2 = list->tmp2->prev;
	while(list->tmp2->prev != NULL) // ici je determine ma lis avec certains calculs. Je pars de mon lismax jusqu'a atteindre le premier element qui a une lis de 1
	{
		if(list->tmp2->data != list->head->data) 
		{
			if(((max - 1) != 1) && list->tmp2->lis == (max - 1) && list->tmp2->data > list->head->data)
				max = list->tmp2->lis;
			else 
				list->tmp2->lis = -1;
		}
		list->tmp2 = list->tmp2->prev;
		if(list->tmp2->data == list->head->data)
			break;
	}
	list->tmp = list->head;
	wha = malloc(sizeof(t_node));
	//wha = NULL;
	int counti = -1;
	while(list->tmp2) //ici je push dans la stack_b tous les elements qui n'appartiennent pas a ma lis
	{
		if(list->tmp2->lis == -1) 
		{
			firstone(list, listb, list->tmp2);
			list->tmp2 = list->head;
		}
		else
			list->tmp2 = list->tmp2->next;
	}
}
