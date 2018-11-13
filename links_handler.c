/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 16:46:42 by popanase          #+#    #+#             */
/*   Updated: 2018/07/17 12:24:55 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_link	*ft_copy_link(char *a, char *b)
{
	t_link	*new;

	new = (t_link *)ft_memalloc(sizeof(t_link));
	new->a = ft_strdup(a);
	new->b = ft_strdup(b);
	return (new);
}

int		ft_linkcmp(char *a, char *b, t_farm *farm)
{
	if (ft_strcmp(a, b) > 0)
	{
		if (!ft_strcmp(b, farm->finish))
			return (0);
		if (!ft_strcmp(a, farm->start))
			return (0);
		return (1);
	}
	else if (ft_strcmp(a, b) < 0)
	{
		if (!ft_strcmp(a, farm->finish))
			return (1);
		if (!ft_strcmp(b, farm->start))
			return (1);
	}
	return (0);
}

void	ft_add_link(t_link *link, t_farm *farm)
{
	t_link	*tmp;
	t_link	*tmpn;

	if (farm->links)
	{
		tmp = farm->links;
		while (tmp)
		{
			if (!tmp->next)
			{
				tmp->next = link;
				break ;
			}
			if (ft_linkcmp(tmp->next->a, link->a, farm))
			{
				tmpn = tmp->next;
				tmp->next = link;
				link->next = tmpn;
				break ;
			}
			tmp = tmp->next;
		}
	}
	else
		farm->links = link;
}

void	ft_add_links(char *s, t_farm *farm)
{
	char	**a;
	t_link	*link1;
	t_link	*link2;

	if (farm->flag_s || farm->flag_f)
		ft_exit_lemin();
	a = ft_strsplit(s, '-');
	ft_validate_links_data(farm, a);
	link1 = (t_link *)ft_memalloc(sizeof(t_link));
	link1->a = ft_strdup(a[0]);
	link1->b = ft_strdup(a[1]);
	link2 = (t_link *)ft_memalloc(sizeof(t_link));
	link2->a = ft_strdup(a[1]);
	link2->b = ft_strdup(a[0]);
	ft_strdel(&a[0]);
	ft_strdel(&a[1]);
	free(a);
	ft_add_link(link1, farm);
	ft_add_link(link2, farm);
}

void	ft_shift_links(t_farm *farm)
{
	t_link	*tmp;
	t_link	*tmps;
	t_link	*tmpn;

	if (!farm->links)
		ft_exit_lemin();
	tmp = farm->links;
	tmps = farm->links;
	if (ft_strcmp(tmps->a, farm->start))
	{
		farm->links = tmp->next;
		while (tmp)
		{
			if (!tmp->next || ft_linkcmp(tmp->next->a, tmps->a, farm))
			{
				tmpn = tmp->next;
				tmp->next = tmps;
				tmps->next = tmpn;
				break ;
			}
			tmp = tmp->next;
		}
	}
}
