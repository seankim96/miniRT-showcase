/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonjuki <yeonjuki@student.42gyeongsan.kr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:31:13 by seungjuk          #+#    #+#             */
/*   Updated: 2025/08/18 11:11:00 by yeonjuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

double	degrees_to_radians(double degrees)
{
	return (degrees * PI / 180.0);
}

t_ray	get_ray(t_viewport viewport, int i, int j)
{
	t_vector	pixel_center;
	t_vector	ray_direction;

	pixel_center = vector_add(viewport.zero, \
							vector_scalar(viewport.delta_u, i));
	pixel_center = vector_add(pixel_center, \
							vector_scalar(viewport.delta_v, j));
	ray_direction = vector_sub(pixel_center, viewport.center);
	return ((t_ray){.orig = viewport.center, .dir = ray_direction, .tm = 0});
}

static void	zero(t_viewport *v_p, t_camera camera, double focal_length)
{
	v_p->upper_left = v_p->center;
	v_p->upper_left = \
	vector_sub(v_p->upper_left, vector_scalar(v_p->w, focal_length));
	v_p->upper_left = \
	vector_sub(v_p->upper_left, vector_scalar(v_p->viewport_u, 0.5));
	v_p->upper_left = \
	vector_sub(v_p->upper_left, vector_scalar(v_p->viewport_v, 0.5));
	v_p->delta_u = \
	vector_scalar_div(v_p->viewport_u, camera.width);
	v_p->delta_v = \
	vector_scalar_div(v_p->viewport_v, camera.height);
	v_p->zero = vector_add(v_p->upper_left, \
	vector_scalar(vector_add(v_p->delta_u, v_p->delta_v), 0.5));
}

t_viewport	set_viewport(t_camera camera)
{
	t_viewport	v_p;
	double		focal_length;
	double		h;

	v_p.center = camera.lookfrom;
	v_p.w = vector_unit(vector_scalar(camera.dir, -1));
	v_p.u = vector_unit(vector_cross(camera.vup, v_p.w));
	v_p.v = vector_cross(v_p.w, v_p.u);
	focal_length = 1.0;
	h = tan(degrees_to_radians(camera.fov) / 2);
	v_p.height = 2 * h * focal_length;
	v_p.width = v_p.height * ((double)camera.width / camera.height);
	v_p.viewport_u = vector_scalar(v_p.u, -v_p.width);
	v_p.viewport_v = vector_scalar(v_p.v, -v_p.height);
	zero(&v_p, camera, focal_length);
	return (v_p);
}
