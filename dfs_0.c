/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs_0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 16:38:36 by popanase          #+#    #+#             */
/*   Updated: 2018/05/24 16:38:39 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		ft_validate_route(t_farm *farm, t_route *route)
{
	t_route	*tmp;
	t_link	*tmpa;
	t_link	*tmpb;

	tmp = farm->routes;
	while (tmp && tmp != route)
	{
		tmpb = tmp->link;
		tmpa = route->link;
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

void	ft_validate_routes_repeat(t_farm *farm)
{
	t_route	*tmp;
	t_route	*tmpp;

	tmp = farm->routes;
	while (tmp)
	{
		if (!ft_validate_route(farm, tmp))
		{
			ft_del_route(farm->routes, tmp);
			tmp = tmpp;
		}
		tmpp = tmp;
		tmp = tmp->next;
	}
}

void	ft_exist_move_dfs(t_farm *farm, t_link *link)
{
	t_link	*cur;
	t_link	*all;

	all = farm->links;
	cur = link;
	while (cur->next)
		cur = cur->next;
	while (all)
	{
		if (!ft_strcmp(all->a, cur->b) && !ft_is_in_route(link, all->a))
		{
			cur->next = ft_copy_link(all->a, all->b);
			if (!ft_strcmp(all->a, farm->finish))
			{
				ft_newroute(farm, link);
				ft_del_link(cur->next);
				cur->next = NULL;
				break ;
			}
			ft_exist_move_dfs(farm, link);
			ft_del_link(cur->next);
			cur->next = NULL;
		}
		all = all->next;
	}
}

void	ft_get_all_routes_dfs(t_farm *farm)
{
	t_link	*tmp;
	t_link	*link;

	tmp = farm->links;
	while (!ft_strcmp(tmp->a, farm->start))
	{
		link = ft_copy_link(tmp->a, tmp->b);
		ft_exist_move_dfs(farm, link);
		ft_del_all_link(link);
		tmp = tmp->next;
	}
	if (!farm->routes)
		ft_exit_lemin();
	ft_sort_routes(farm);
	ft_validate_routes_repeat(farm);
}
