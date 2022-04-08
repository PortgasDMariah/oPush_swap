/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_num.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:23:11 by mdouiri           #+#    #+#             */
/*   Updated: 2022/04/08 17:33:11 by mdouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include "struct.h"
#include <stdio.h>
// si tu es un chiffre ou non 
int ft_num(char c)
{
	if(c >='0' && c <= '9')
		return(1);
	return(0);
}

// Cette fonction verifie mes arguments 
int	ft_ato(char *str)
{
	int	i;
	long int	a;
	long int	b;

	i = -1;
	a = 1;
	b = 0;
	if(!str)
		//return(//printf("gfge"), 0);
		exit(0);
	while (str[++i])
	{
		if(!((ft_num(str[i]) == 1) || (str[i] == '-') || (str[i] == ' ')))
			//return(//printf("ytr"), (void *)'c');
				exit(0);

		else if(str[i] == '-' && (!(ft_num(str[i + 1]) == 1) || (ft_num(str[i - 1]) == 1)))
			//return(//printf("kbverbg \n"), (void *)'c');
			exit(0);

		else if(str[i] == '-')
			a = -a;
		if(ft_num(str[i]) == 1)
			b = b * 10 + str[i] - 48;
	}
	if(((a * b) > (2147483647)) || ((a * b) < (-2147483648)) )
		//return(//printf("hjktg \n"),(void *)'c');
		exit(0);

	//printf("int = %ld \n", (a * b));
	return (a * b);
}

//fonction pour afficher une liste
void    printnode(t_node *start)
{
        t_node *temp;

        temp = start;
        while(temp)
        {
                printf("%ld \n", (long int)temp->data);
                temp = temp->next;
        }
}

//fonction pour free une list
void	deleteallnodes(t_node *start)
{
	t_node	*temp;

	while (start != NULL)
	{
		temp = start;
		start = start -> next;
		free(temp);
	}
}

// Algo quand je n'ai que 3 elements
void	three(bon *list)
{
	list->maxi = list->chef;
	position(list);
	list->chef = list->maxi;
	if(!(list->min->mouv == 0 && list->chef->mouv == list->fin))
	{
		if((list->min->mouv == list->fin && list->chef->mouv == 0) || (list->chef->mouv != 0 && list->min->mouv == 1))
	       		ft_swap(list);
		else if(list->chef->mouv == 0 && list->min->mouv == 1)
			ft_rotate(list);
		else if((list->min->mouv == 0 && list->chef->mouv == 1) || list->min->mouv == list->fin)
			ft_rrotate(list);
		list->action++;
		three(list);
	}
	else
		return;
}

// cette fonction me permet de rotate ou de reverserotate jusqu'a que le 1er element de ma liste soit le plus petit element 
void    firsti(bon *list, t_node *c)
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
       // pb(list, listb);//c'est un pa
       // list->action++;
}

#include <stdio.h>
//Alors dans ce main, je verifie si je n'ai pas de doublons, je cree ma list qui est en faite ma stack_a et listb pour stack_b. 
int main(int ac, char **av)
{
	bon *list;
	bon *listb;
	bon *listtmp;

	list = malloc(sizeof(*list));
	listb = malloc(sizeof(*listb));
	listtmp = malloc(sizeof(*listtmp));
	list->min = malloc(sizeof(t_node));
	list->min = NULL;
	int i = 1;
	int tot = 0;
	int val;
	
	list->action = 0;
	if(ac == 1)
		return(0);
	tot = ac;
	val = ft_ato(av[i]);
	int n = 0;
	//je cree le premier noeud de ma liste 
	if( val)
	{
		list->head = ft_lstnew(ft_ato(av[i]));
		listb->head = NULL;
		list->min = list->head;
	}
	else
		return(printf(" non"), 0);
	i++;
	i = 1;
	int j = 0;
	//pour les doublons
	while(av[i] && ft_ato(av[i]))
	{
		val = ft_ato(av[i]);
		j = i + 1;
		while( av[j] )
		{
			if(val == ft_ato(av[j]))
				return(0);
			j++;
		}
		i++;
	}
	i = 2;
	//je cree ma liste 
	while(av[i] && tot != 1)
	{
		val = ft_ato(av[i]);
		/*
		if(val)
		{
			deleteallnodes(list->head);
			deleteallnodes(listtmp->head);
			return(printf("k.o"), 0);
		}
		*/
		//if(val < list->min)
			//list->min = val;
		ft_lstadd_back(&list->head, ft_lstnew(val), list);
		if(val < list->min->data)
			list->min = list->last; // je retiens stock l'element le plus petit dans list->min
		tot--;
		i++;
	}
	list->tot = ac;
		list->maxi = malloc(sizeof(t_node));
		list->maxi = NULL;
	listmax(list); // me trouve l'element le plus grand de ma list et je le stock dans list->chef 
	if(ac == 4) // pour que 3 chiffre 
	{
		three(list);
		printnode(list->head);
		return(0);
	}
	firsti(list, list->min); // list->head vaut list->min et je fais ca pour effectuer ma lis
	bienfait(list, listtmp, listb); // fonction pour faire ma lis 
		list->maxi = malloc(sizeof(t_node));
		list->maxi = NULL;
	organisation(list, listb);// fonction de tri 
	firsti(list, list->min);// list->head vaut list->min
		printnode(list->head); // j'affiche ma liste pour voir que tout est bien trier et c'est le cas
	printf("action %d \n", list->action); // j'affiche mon compteur d'action

	return(1);
}

