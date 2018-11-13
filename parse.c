/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 16:39:15 by popanase          #+#    #+#             */
/*   Updated: 2018/07/17 13:15:06 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	ft_get_start_and_finish(t_farm *farm, char *s)
{
	if (farm->flag_s == 1)
	{
		farm->start = ft_strdup(s);
		farm->flag_s = 0;
	}
	if (farm->flag_f == 1)
	{
		farm->finish = ft_strdup(s);
		farm->flag_f = 0;
	}
}

void	ft_add_room(char *s, t_farm *farm)
{
	char	**a;
	t_room	*room;
	t_room	*tmp;

	a = ft_strsplit(s, ' ');
	ft_validate_rooms_data(farm, a);
	room = (t_room *)ft_memalloc(sizeof(t_room));
	room->name = ft_strdup(a[0]);
	ft_strdel(&a[0]);
	room->x = ft_atoi(a[1]);
	ft_strdel(&a[1]);
	room->y = ft_atoi(a[2]);
	ft_strdel(&a[2]);
	free(a);
	farm->qnt_r++;
	ft_get_start_and_finish(farm, room->name);
	if (farm->rooms)
	{
		tmp = farm->rooms;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = room;
	}
	else
		farm->rooms = room;
}

void	ft_parse_qnt(t_farm *farm, char *s)
{
	int	i;

	i = 0;
	if (!ft_strcmp(s, "##start") || !ft_strcmp(s, "##end"))
		ft_exit_lemin();
	if (s[0] != '#')
	{
		while (s[i])
		{
			if (ft_isdigit(s[i]) && !(!s[i + 1] || ft_isdigit(s[i + 1])))
				ft_exit_lemin();
			i++;
		}
		farm->qnt = ft_atoi(s);
		if (farm->qnt < 1)
			ft_exit_lemin();
	}
}

void	ft_parse_command(t_farm *farm, char *s)
{
	if (!ft_strcmp(s, "##start"))
	{
		if (farm->flag_s != -1)
			ft_exit_lemin();
		else
			farm->flag_s = 1;
	}
	if (!ft_strcmp(s, "##end"))
	{
		if (farm->flag_f != -1)
			ft_exit_lemin();
		else
			farm->flag_f = 1;
	}
}

void	ft_handler_s(t_farm *farm, char *s)
{
	if (!s[0])
		farm->stop = 1;
	else if (!farm->qnt)
		ft_parse_qnt(farm, s);
	else if (s[0] != '#' && ft_pattern_link(s))
		ft_add_links(s, farm);
	else if (s[0] != '#' || farm->flag_s == 1 || farm->flag_f == 1)
	{
		if (farm->links)
			farm->stop = 1;
		else
			ft_add_room(s, farm);
	}
	else if (s[0] == '#' && s[1] == '#')
		ft_parse_command(farm, s);
}
