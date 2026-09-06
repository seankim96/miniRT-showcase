/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonjuki <yeonjuki@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:48:19 by yeonjuki          #+#    #+#             */
/*   Updated: 2025/08/18 11:18:15 by yeonjuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <fcntl.h>
# include "vector.h"
# include "color.h"

typedef struct s_vars		t_vars;
typedef struct s_object		t_object;
typedef struct s_texture	t_texture;

typedef struct s_flags
{
	int	is_camera;
	int	is_light;
	int	is_ambient;
}	t_flags;

/* parser_validation.c */
int			is_between_01(double value);
int			is_fov_in_range(double fov);
int			is_rgb_in_range(t_color color);
int			is_normal_vec(t_vector vec);
int			is_inf_vec(t_vector vec);

/* parser_validation1.c*/
int			check_tokens_length(char **tokens, \
char *object, int expected_length);

/* validate_texture.c */
int			is_readable_file(char *filename);
int			is_valid_texture(char *token);

/* parser_utils.c */
double		ft_atod(const char *str);
t_vector	parse_vector(char *token);
int			get_token_len(char **tokens);
void		free_line_and_token(char *line, char **tokens);
char		*remove_newline(char *line);

/* parser_utils1.c*/
void		free_and_get_next_line(int fd, char **line);

/* create_object.c */
int			get_bumpmap(char *token, t_texture **bumpmap);

t_hittable	*create_sphere_object(\
			char *tex_token, t_vector center, double radius);
t_hittable	*create_plane_object(\
			char *tex_token, t_vector center, t_vector normal);
t_hittable	*create_cylinder_object(\
			char *tex_token, t_vector center, t_vector normal, double dval[2]);

/* parser_object.c */
int			parse_sphere(t_vars *data, char **tokens, t_hittable_list *list);
int			parse_plane(t_vars *data, char **tokens, t_hittable_list *list);
int			parse_cylinder(t_vars *data, char **tokens, t_hittable_list *list);

/* parser_cam_light.c */
int			set_cam(t_vars *data, char **tokens, t_flags *flags);
int			set_light(t_vars *data, char **tokens, t_flags *flags);
int			set_ambient(t_vars *data, char **tokens, t_flags *flags);

int			read_file(char *filename, t_vars *data);

#endif
