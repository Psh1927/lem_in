/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 12:32:06 by popanase          #+#    #+#             */
/*   Updated: 2018/07/17 13:31:50 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	ft_parse_flags(t_farm *farm, int ac, char **av)
{
	int i;

	i = 1;
	while (av[i])
	{
		if (!ft_strcmp(av[i], "-r"))
			farm->r = 1;
		if (!ft_strcmp(av[i], "-d"))
			farm->d = 1;
		if (!ft_strcmp(av[i], "-t"))
			farm->t = 1;
		i++;
	}
	if (ac - 1 != farm->r + farm->d + farm->t)
	{
		ft_printf("USAGE:\n");
		ft_printf("  -r shows used routes;\n");
		ft_printf("  -t shows time for execute algorithm;\n");
		ft_printf("  -d change BFS to DFS;\n");
		exit(0);
	}
}

void	ft_parse_input(t_farm *farm)
{
	t_inp	*tmp;
	char	*s;

	tmp = NULL;
	while (!farm->stop && get_next_line(0, &s) > 0)
	{
		if (tmp)
		{
			tmp->next = (t_inp *)ft_memalloc(sizeof(t_inp));
			tmp = tmp->next;
		}
		else
			tmp = (t_inp *)ft_memalloc(sizeof(t_inp));
		if (!farm->in)
			farm->in = tmp;
		tmp->s = ft_strtrim(s);
		free(s);
		ft_handler_s(farm, tmp->s);
	}
	if (farm->stop)
		ft_strdel(&tmp->s);
	else
		free(s);
	ft_shift_links(farm);
}

void	ft_exit_lemin(void)
{
	ft_printf("ERROR\n");
	exit(0);
}

void	ft_do_lemin(t_farm *farm, int mode)
{
	clock_t				t;

	t = clock();
	if (!mode)
		ft_get_all_routes_bfs(farm);
	else
		ft_get_all_routes_dfs(farm);
	ft_print_input(farm);
	ft_get_extend_routes(farm);
	ft_sort_routes(farm);
	ft_get_finish_routes(farm);
	ft_print(farm);
	t = clock() - t;
	if (farm->t && !mode)
		ft_printf("\nBFS took %ju miliseconds to execute \n", (uintmax_t)t);
	else if (farm->t && mode)
		ft_printf("\nDFS took %ju miliseconds to execute \n", (uintmax_t)t);
}

int		main(int ac, char **av)
{
	t_farm	*farm;

	farm = (t_farm *)ft_memalloc(sizeof(t_farm));
	farm->flag_s = -1;
	farm->flag_f = -1;
	ft_parse_flags(farm, ac, av);
	ft_parse_input(farm);
	ft_do_lemin(farm, farm->d);
	ft_free_farm(farm);
	return (0);
}
