/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 16:36:20 by popanase          #+#    #+#             */
/*   Updated: 2018/07/17 12:17:39 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		ft_validate_route_bfs(t_farm *farm, t_link *link)
{
	t_route	*tmp;
	t_link	*tmpa;
	t_link	*tmpb;

	tmp = farm->routes;
	while (tmp)
	{
		tmpb = tmp->link;
		tmpa = link;
		while (tmpb && tmpa)
		{
			if (!ft_strcmp(tmpa->a, tmpb->a) && ft_strcmp(farm->start, tmpa->a)
				&& ft_strcmp(farm->finish, tmpa->a))
				return (0);
			tmpb = tmpb->next;
			tmpa = tmpa->next;
		}
		tmp = tmp->next;
	}
	return (1);
}

int		ft_check_finish(t_farm *farm)
{
	int c;

	c = farm->qnt_r * farm->qnt_r + 1;
	if (farm->qnt == 1)
		c = farm->qnt_r * farm->qnt_r;
	if (c >= farm->qnt)
		return (1);
	return (0);
}

void	ft_exist_move_bfs_1(t_route *tr, t_link *link, t_farm *farm, t_route *r)
{
	t_link	*all;
	t_route	*new;

	all = farm->links;
	while (all)
	{
		if (!ft_strcmp(all->a, link->b) && !ft_is_in_route(tr->link, all->a))
		{
			link->next = ft_copy_link(all->a, all->b);
			if (!ft_strcmp(all->a, farm->finish))
			{
				if (ft_validate_route_bfs(farm, tr->link))
					ft_newroute(farm, tr->link);
			}
			else if (!ft_is_in_route(tr->link, all->b)
				&& ft_strcmp(farm->finish, all->a))
			{
				new = ft_copy_route(tr);
				ft_add_route(r, new);
			}
			ft_del_link(link->next);
			link->next = NULL;
		}
		all = all->next;
	}
}

void	ft_exist_move_bfs(t_farm *farm, t_route *routes)
{
	t_route	*tmp;
	t_route	*route;
	t_link	*cur;

	tmp = routes;
	route = (t_route *)ft_memalloc(sizeof(t_route));
	while (tmp)
	{
		cur = tmp->link;
		while (cur->next)
			cur = cur->next;
		ft_exist_move_bfs_1(tmp, cur, farm, route);
		tmp = tmp->next;
	}
	ft_del_all_route(routes);
	if (route->next && !ft_check_finish(farm))
	{
		ft_exist_move_bfs(farm, route->next);
		free(route);
	}
	else
		ft_del_all_route(route);
}

void	ft_get_all_routes_bfs(t_farm *farm)
{
	t_link	*tmp;
	t_route	*route;
	t_route	*new;

	tmp = farm->links;
	route = NULL;
	while (!ft_strcmp(tmp->a, farm->start))
	{
		new = (t_route *)ft_memalloc(sizeof(t_route));
		new->link = ft_copy_link(tmp->a, tmp->b);
		if (!route)
			route = new;
		else
			ft_add_route(route, new);
		tmp = tmp->next;
	}
	farm->qnt_r = 0;
	ft_exist_move_bfs(farm, route);
	if (!farm->routes)
		ft_exit_lemin();
}
