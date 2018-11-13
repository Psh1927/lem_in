/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 14:48:19 by popanase          #+#    #+#             */
/*   Updated: 2018/05/15 14:48:23 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	ft_printr(t_route *route)
{
	t_route *tmp;
	t_link	*tmpl;

	tmp = route;
	ft_printf("\nPossible routes:");
	while (tmp)
	{
		ft_printf("\n");
		tmpl = tmp->link;
		ft_printf("w = %i ", tmp->w - 1);
		while (tmpl)
		{
			if (tmpl->next)
				ft_printf("%s->", tmpl->a);
			else
				ft_printf("%s", tmpl->a);
			tmpl = tmpl->next;
		}
		tmp = tmp->next;
	}
	ft_printf("\n");
}

void	ft_print_input(t_farm *farm)
{
	t_inp	*tmp;

	tmp = farm->in;
	while (tmp)
	{
		if (tmp->s)
			ft_printf("%s\n", tmp->s);
		tmp = tmp->next;
	}
	if (farm->r)
		ft_printr(farm->routes);
}

void	ft_print_result(t_route *route, t_link *link)
{
	static int		n;

	if (!route->n)
	{
		n++;
		route->n = n;
	}
	ft_printf("L%i-%s ", route->n, link->a);
}

void	ft_print(t_farm *farm)
{
	t_route	*tmp;
	t_link	*tmpl;
	int		i;
	int		j;

	i = 0;
	while (farm->step--)
	{
		tmp = farm->routes;
		while (tmp)
		{
			j = 0;
			tmpl = tmp->link;
			while (tmpl)
			{
				if (j == i && ft_strcmp(tmpl->a, farm->start))
					ft_print_result(tmp, tmpl);
				j++;
				tmpl = tmpl->next;
			}
			tmp = tmp->next;
		}
		ft_printf("\n");
		i++;
	}
}
