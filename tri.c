/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:23:49 by mdouiri           #+#    #+#             */
/*   Updated: 2022/04/08 18:15:03 by mdouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

void	actionmax(bon *list, bon *listb) // actionmax pour le cas ou le plus grand element de toute les stacks se trouvent dans ma stack_B 
{
	position(list);
	position(listb);
	listmax(list);

	if(list->chef->mouv == list->fin && listb->push->mouv == 0)
	{
		pb(listb, list);
		(list->action)++;
		return;
	}
	else
	{
		if(list->chef->mouv < 0 && listb->push->mouv < 0 && list->chef->mouv != list->fin)
			rrr(list, listb);
		else if (list->chef->mouv > 0 && listb->push->mouv > 0 && list->chef->mouv != list->fin)
			doublerotate(list, listb);
		else if(list->chef->mouv < 0 && list->chef->mouv != list->fin)
			ft_rrotate(list);
		else if(listb->push->mouv < 0)
			ft_rrotate(listb);
		else if(list->chef->mouv >= 0 && list->chef->mouv != list->fin)
			ft_rotate(list);
		else if(listb->push->mouv > 0)
			ft_rotate(listb);
		(list->action)++;
		actionmax(list, listb);
	}

}

void	action(bon *list, bon *listb)
{
	found_your_place(list, listb->push->data);
	position(list);
	position(listb);
	if(listb->push->data > list->chef->data)
	{
		actionmax(list, listb);
		return;
	}
	if (listb->push->mouv == 0 &&  list->maxi->mouv == 0)
	{
		pb(listb, list);
		(list->action)++;
		list->push = NULL;
		return;
	}
	else
	{
		if( listb->push->mouv < 0 && list->maxi->mouv < 0 )
			rrr(list, listb);
		else if ( listb->push->mouv > 0 && list->maxi->mouv > 0)
			doublerotate(list, listb);
		else if ( list->maxi->mouv> 0)
			ft_rotate(list);
		else if ( listb->push->mouv > 0)
			ft_rotate(listb);
		else if ( listb->push->mouv < 0)
			ft_rrotate(listb);
		else if ( list->maxi->mouv < 0)
			ft_rrotate(list);
		(list->action)++;
		action(list, listb);
	}

}

void	organisation(bon *list, bon *listb) //fonction ou je donne les ordres de tri
{
	int len;

	len = ft_listlen(listb); //taille de list donc ici stack_b
	while(len != 0) // tant ma stack_b n'est pas vide 
	{
			position(list);//je donne les positions de chaque element 
			position(listb);
			foundit(list, listb);//je cherche le meilleur element a push
			action(list, listb);// j'envoie l'element a push

		len = len - 1;
	}
	
}

