/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: popanase <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 12:38:19 by popanase          #+#    #+#             */
/*   Updated: 2018/07/17 13:32:48 by popanase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H
# include "libft/libft.h"
# include "libft/get_next_line.h"
# include "ft_printf/libftprintf.h"
# include <time.h>

typedef struct		s_inp
{
	char			*s;
	struct s_inp	*next;
}					t_inp;

typedef	struct		s_farm
{
	int				r;
	int				d;
	int				t;
	int				qnt;
	int				flag_s;
	int				flag_f;
	int				step;
	int				qnt_r;
	int				stop;
	char			*start;
	char			*finish;
	struct s_room	*rooms;
	struct s_inp	*in;
	struct s_link	*links;
	struct s_route	*routes;
}					t_farm;

typedef struct		s_room
{
	char			*name;
	int				x;
	int				y;
	struct s_room	*next;
}					t_room;

typedef struct		s_route
{
	int				n;
	int				w;
	struct s_link	*link;
	struct s_route	*next;
}					t_route;

typedef struct		s_link
{
	char			*a;
	char			*b;
	struct s_link	*next;
}					t_link;

void				ft_handler_s(t_farm *farm, char *s);
void				ft_validate_rooms_data(t_farm *farm, char **a);
void				ft_validate_links_data(t_farm *farm, char **a);
int					ft_pattern_link(char *s);
void				ft_get_all_routes_bfs(t_farm *farm);
void				ft_get_all_routes_dfs(t_farm *farm);
int					ft_is_in_route(t_link *link, char *s);
void				ft_sort_routes(t_farm *farm);
void				ft_del_route(t_route *begin, t_route *route);
void				ft_get_extend_routes(t_farm *farm);
void				ft_get_finish_routes(t_farm *farm);
int					ft_validate_route(t_farm *farm, t_route *route);
void				ft_shift_links(t_farm *farm);
void				ft_del_link(t_link *link);
t_link				*ft_copy_link(char *a, char *b);
int					ft_newroute(t_farm *farm, t_link *link);
void				ft_add_route(t_route *begin, t_route *new);
void				ft_add_links(char *s, t_farm *farm);
t_route				*ft_copy_route(t_route *route);
void				ft_validate_routes_repeat(t_farm *farm);
void				ft_print(t_farm *farm);
void				ft_print_input(t_farm *farm);
void				ft_printr(t_route *route);
void				ft_free_farm(t_farm *farm);
void				ft_del_all_link(t_link *link);
void				ft_del_all_route(t_route *begin);
void				ft_exit_lemin();
#endif
