/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_routes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 14:48:04 by popanase          #+#    #+#             */
/*   Updated: 2018/05/15 14:48:07 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	ft_get_finish_routes(t_farm *farm)
{
	t_route	*tmp;
	int		q;

	q = farm->qnt;
	tmp = farm->routes;
	if (q == 1)
		farm->step = tmp->w;
	while (q--)
	{
		tmp = tmp->next;
		if (q == 1)
			farm->step = tmp->w;
	}
	while (tmp)
	{
		ft_del_route(farm->routes, tmp);
		tmp = tmp->next;
	}
}

void	ft_newextroute(t_farm *farm, t_route *route)
{
	t_route	*tmpr;
	t_link	*tmp;
	t_link	*new;
	t_link	*cur;

	if (route->next)
		tmpr = route->next;
	else
		tmpr = NULL;
	route->next = (t_route *)ft_memalloc(sizeof(t_route));
	tmp = route->link;
	route->next->link = (t_link *)ft_memalloc(sizeof(t_link));
	cur = route->next->link;
	cur->a = ft_strdup(farm->start);
	cur->b = ft_strdup(farm->start);
	route->next->next = tmpr;
	while (tmp)
	{
		new = (t_link *)ft_memalloc(sizeof(t_link));
		new->a = ft_strdup(tmp->a);
		new->b = ft_strdup(tmp->b);
		cur->next = new;
		cur = cur->next;
		tmp = tmp->next;
	}
}

void	ft_get_extend_routes(t_farm *farm)
{
	t_route	*tmp;
	int		i;

	tmp = farm->routes;
	while (tmp)
	{
		i = farm->qnt - 1;
		while (i--)
		{
			ft_newextroute(farm, tmp);
			tmp->next->w = tmp->w + 1;
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
}

void	ft_sort_routes(t_farm *farm)
{
	t_route *tmp;
	t_link	*tmpl;
	int		w;

	tmp = farm->routes;
	while (tmp->next)
	{
		if (tmp->w > tmp->next->w)
		{
			w = tmp->next->w;
			tmp->next->w = tmp->w;
			tmp->w = w;
			tmpl = tmp->next->link;
			tmp->next->link = tmp->link;
			tmp->link = tmpl;
			tmp = farm->routes;
		}
		else
			tmp = tmp->next;
	}
}
