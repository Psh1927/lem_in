/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 16:38:45 by popanase          #+#    #+#             */
/*   Updated: 2018/07/17 13:30:01 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	ft_validate_links_data(t_farm *farm, char **a)
{
	int		flag;
	t_room	*tmp;

	tmp = farm->rooms;
	flag = 0;
	while (tmp)
	{
		if (!ft_strcmp(a[0], tmp->name) || !ft_strcmp(a[1], tmp->name))
			flag++;
		tmp = tmp->next;
	}
	if (a[2] || !ft_strcmp(a[0], a[1]) || flag != 2)
		farm->stop = 1;
}

void	ft_validate_rooms_repeat(t_farm *farm, char **a)
{
	t_room	*tmp;

	tmp = farm->rooms;
	while (tmp)
	{
		if ((tmp->x == ft_atoi(a[1]) && tmp->y == ft_atoi(a[2])) ||
				!ft_strcmp(tmp->name, a[0]))
			ft_exit_lemin();
		tmp = tmp->next;
	}
}

void	ft_validate_rooms_data(t_farm *farm, char **a)
{
	int		i;
	int		j;

	i = 0;
	j = 1;
	if (a[3] || !a[0] || !a[1] || !a[2] || a[0][0] == 'L' ||
			ft_strchr(a[0], '-'))
		ft_exit_lemin();
	while (j < 3)
	{
		while (a[j][i])
		{
			if (!(ft_isdigit(a[j][i]) || a[j][i] == '-' || a[j][i] == '+')
				|| (ft_isdigit(a[j][i]) && !(!a[j][i + 1]
					|| ft_isdigit(a[j][i + 1]))))
				ft_exit_lemin();
			i++;
		}
		j++;
	}
	ft_validate_rooms_repeat(farm, a);
}

int		ft_pattern_link(char *s)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (s[i])
	{
		if (s[i] == ' ')
			return (0);
		if (s[i] == '-')
			flag++;
		i++;
	}
	if (flag == 1)
		return (1);
	else
		return (0);
}
