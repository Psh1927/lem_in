/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 17:02:29 by popanase          #+#    #+#             */
/*   Updated: 2018/05/24 17:02:32 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_route	*ft_copy_route(t_route *route)
{
	t_route	*new;
	t_link	*tmp;
	t_link	*tmpn;
	t_link	*tmpp;

	new = (t_route *)ft_memalloc(sizeof(t_route));
	tmp = route->link;
	tmpp = NULL;
	while (tmp)
	{
		tmpn = ft_copy_link(tmp->a, tmp->b);
		if (tmpp)
			tmpp->next = tmpn;
		else
			new->link = tmpn;
		tmpp = tmpn;
		tmp = tmp->next;
	}
	return (new);
}

int		ft_is_in_route(t_link *link, char *s)
{
	t_link	*tmp;

	tmp = link;
	while (tmp)
	{
		if (!ft_strcmp(tmp->a, s))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	ft_get_weight_routes(t_farm *farm)
{
	t_route	*tmp;
	t_link	*tmpl;

	tmp = farm->routes;
	while (tmp)
	{
		if (!tmp->w)
		{
			tmpl = tmp->link;
			while (tmpl)
			{
				tmp->w++;
				tmpl = tmpl->next;
			}
		}
		tmp = tmp->next;
	}
}

void	ft_add_route(t_route *begin, t_route *new)
{
	t_route	*tmp;

	tmp = begin;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int		ft_newroute(t_farm *farm, t_link *link)
{
	t_route	*newr;
	t_link	*tmpl;
	t_link	*new;
	t_link	*prev;

	newr = (t_route *)ft_memalloc(sizeof(t_route));
	tmpl = link;
	prev = NULL;
	while (tmpl)
	{
		new = ft_copy_link(tmpl->a, tmpl->b);
		if (!newr->link)
			newr->link = new;
		if (prev)
			prev->next = new;
		prev = new;
		tmpl = tmpl->next;
	}
	if (!farm->routes)
		farm->routes = newr;
	else
		ft_add_route(farm->routes, newr);
	ft_get_weight_routes(farm);
	farm->qnt_r++;
	return (1);
}
