/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 12:12:52 by popanase          #+#    #+#             */
/*   Updated: 2018/05/25 12:12:54 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	ft_free_farm(t_farm *farm)
{
	t_inp	*tinp;
	t_room	*troom;

	ft_strdel(&farm->start);
	ft_strdel(&farm->finish);
	while (farm->in)
	{
		ft_strdel(&farm->in->s);
		tinp = farm->in->next;
		free(farm->in);
		farm->in = tinp;
	}
	while (farm->rooms)
	{
		ft_strdel(&farm->rooms->name);
		troom = farm->rooms->next;
		free(farm->rooms);
		farm->rooms = troom;
	}
	ft_del_all_link(farm->links);
	ft_del_all_route(farm->routes);
	free(farm);
}

void	ft_del_link(t_link *link)
{
	ft_strdel(&link->a);
	ft_strdel(&link->b);
	free(link);
}

void	ft_del_all_link(t_link *link)
{
	t_link	*tmplp;

	while (link)
	{
		tmplp = link->next;
		ft_strdel(&link->a);
		ft_strdel(&link->b);
		free(link);
		link = tmplp;
	}
}

void	ft_del_all_route(t_route *begin)
{
	t_route	*tmp;

	while (begin)
	{
		tmp = begin->next;
		ft_del_route(begin, begin);
		begin = tmp;
	}
}

void	ft_del_route(t_route *begin, t_route *route)
{
	t_link	*tmpl;
	t_link	*tmplp;
	t_route	*tmp;
	t_route *prev;

	tmp = begin;
	prev = NULL;
	while (tmp != route)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	tmpl = route->link;
	while (tmpl)
	{
		tmplp = tmpl->next;
		ft_del_link(tmpl);
		tmpl = tmplp;
	}
	if (prev)
		prev->next = route->next;
	else
		begin = route->next;
	free(route);
}
