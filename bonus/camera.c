/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:56:22 by seungjuk          #+#    #+#             */
/*   Updated: 2025/07/21 16:10:16 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"
#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "color.h"
#include "wrapper.h"

t_color	iterate_spec_lights(
	t_hittable *light,
	t_hit_record *rec,
	t_hittable *hittable,
	t_camera *camera)
{
	t_color		contribution;
	double		light_dist;
	t_vector	light_pos;
	t_vector	light_dir;
	t_ray		shadow_ray;

	light_pos = light->f.close_point(light, rec->p);
	light_dist = (vector_length(vector_sub(light_pos, rec->p)));
	light_dir = vector_unit(vector_sub(light_pos, rec->p));
	shadow_ray = init_ray(rec->p, light_dir);
	if (hittable->f.hit_rev(hittable, shadow_ray, \
		(t_interval){0.001, light_dist}, &(t_hit_record){0}))
		return ((t_color){0});
	contribution = vector_scalar(\
	light->tex->f.value(light->tex, rec->u, rec->v, rec->p), \
	specular_lighting(light_dir, rec->normal, \
	vector_unit(vector_sub(camera->lookfrom, rec->p)), 16) / \
	(light_dist * light_dist));
	return (contribution);
}

t_color	iterate_lights(
	t_hittable *light,
	t_hit_record *rec,
	t_hittable *hittable,
	t_camera *camera)
{
	t_color		contribution;
	double		light_dist;
	t_vector	light_pos;
	t_vector	light_dir;
	t_ray		shadow_ray;

	light_pos = light->f.close_point(light, rec->p);
	light_dist = (vector_length(vector_sub(light_pos, rec->p)));
	light_dir = vector_unit(vector_sub(light_pos, rec->p));
	shadow_ray = init_ray(rec->p, light_dir);
	if (hittable->f.hit_rev(hittable, shadow_ray, \
	(t_interval){0.001, light_dist}, &(t_hit_record){0}))
		return ((t_color){0});
	contribution = vector_scalar(\
	light->tex->f.value(light->tex, rec->u, rec->v, rec->p), \
	(fmax(0.0, vector_dot(rec->normal, light_dir)) / \
	(light_dist * light_dist)));
	return (contribution);
}

t_color	direct_light(
	t_hit_record *rec,
	t_hittable *hittable,
	t_hittable_list *lights,
	t_camera *camera)
{
	t_color			total_direct_light;
	t_color			ray_color;
	int				i;
	const t_color	albedo = \
	rec->tex->f.value(rec->tex, rec->u, rec->v, rec->local_p);

	i = -1;
	total_direct_light = (t_color){.vector = {0}};
	while (++i < lights->size)
	{
		ray_color = vector_mul(albedo, \
		iterate_lights(lights->hittables[i], rec, hittable, camera));
		ray_color = vector_add(ray_color, vector_mul((t_color){255, 255, 255}, \
		iterate_spec_lights(lights->hittables[i], rec, hittable, camera)));
		total_direct_light = vector_add(total_direct_light, ray_color);
	}
	total_direct_light = vector_add(\
	vector_mul(camera->ambient, albedo), total_direct_light);
	return (total_direct_light);
}

t_color	ray_color(
	t_ray r,
	t_hittable *hittable,
	t_hittable_list *lights,
	t_camera *camera)
{
	t_hit_record	world_rec;
	t_bool			hit_world;
	t_color			direct_c;

	hit_world = hittable->f.hit(hittable, r, \
	(t_interval){.min = 0.0001, .max = INFINITY}, &world_rec);
	direct_c = (t_vector){0};
	if (hit_world == true)
		direct_c = direct_light(&world_rec, hittable, lights, camera);
	return (direct_c);
}

void	render(t_vars *vars)
{
	int			i;
	int			j;
	t_color		rgb;
	t_color		color;
	t_ray		ray;

	j = -1;
	while (++j < vars->camera->height)
	{
		i = -1;
		while (++i < vars->camera->width)
		{
			color = (t_color){0};
			ray = get_ray(vars->camera->viewport, i, j);
			color = vector_add(color, \
			ray_color(ray, \
			(t_hittable *)vars->objs, vars->lights, vars->camera));
			color = (t_vector){fmin(color.x, 255), \
			fmin(color.y, 255), fmin(color.z, 255)};
			my_mlx_pixel_put(vars->data, i, j, \
			(int)(color.x) << 16 | (int)(color.y) << 8 | (int)(color.z));
		}
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->data->img, 0, 0);
}
