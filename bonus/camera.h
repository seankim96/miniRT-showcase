/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:17:19 by seungjuk          #+#    #+#             */
/*   Updated: 2025/07/22 16:03:19 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "raytracing.h"
# include "hittable.h"

typedef struct s_hittable_list	t_hittable_list;
typedef struct s_hittable		t_hittable;

typedef struct s_viewport
{
	t_vector	w;
	t_vector	u;
	t_vector	v;
	t_vector	center;
	double		height;
	double		width;
	t_vector	viewport_u;
	t_vector	viewport_v;
	t_vector	upper_left;
	t_vector	delta_u;
	t_vector	delta_v;
	t_vector	zero;
}	t_viewport;

typedef struct s_camera
{
	t_vector		lookfrom;
	t_vector		dir;
	t_quaternion	orientation;
	t_vector		vup;
	double			ratio;
	double			fov;
	int				width;
	int				height;
	t_color			ambient;
	t_viewport		viewport;
}	t_camera;

void		render(t_vars *var);
t_viewport	set_viewport(t_camera camera);
double		degrees_to_radians(double degrees);
t_color		ray_color(t_ray r, t_hittable *hittable, \
t_hittable_list *lights, t_camera *camera);
t_ray		get_ray(t_viewport viewport, int i, int j);
double		specular_lighting(t_vector light_dir, t_vector normal, \
t_vector view_dir, double shininess);

#endif
