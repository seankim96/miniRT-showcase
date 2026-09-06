/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungjuk <seungjuk@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:53:43 by seungjuk          #+#    #+#             */
/*   Updated: 2025/08/10 15:22:13 by seungjuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACING_H
# define RAYTRACING_H
# define PI  3.141592653589793
# define X_MAX 1050
# define Y_MAX 450
# define Z_LEFT 65430
# define Z_RIGHT 65432
# define ZEROING 65437
# define Y_DOWN 65433
# define Y_UP 65431
# define X_DOWN 65429
# define X_UP 65434
# define ESC 65307
# define N1	49
# define N2 50
# define N3 51
# define N4 52
# define N5 53
# define N6 54
# define A 97
# define D 100
# define E 101
# define Q 113
# define S 115
# define W 119
# define PLUS 65451
# define MINUS 65453
# define WHEEL_UP 4
# define WHEEL_DOWN 5
# define TAB 65289
# define TWO 65433
# define FOUR 65430
# define SIX 65432
# define EIGHT 65431
# define EPSILON 1e-4

# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <pthread.h>
# include "libft.h"
# include "math/interval.h"
# include "ray.h"
# include "vector.h"
# include "color.h"
# include "math/quaternion.h"

typedef struct s_camera			t_camera;
typedef struct s_hittable_list	t_hittable_list;
typedef struct s_hittable		t_hittable;
typedef t_bool					(*t_comparator)(void *, void *);

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_vars
{
	void			*mlx;
	void			*win;
	t_data			*data;
	t_camera		*camera;
	t_hittable_list	*objs;
	t_hittable_list	*lights;
	t_hittable_list	*objs_list;
	t_hittable_list	*planes_list;
	t_hittable		*curr_obj;
	t_hittable		*curr_light;
	int				axis;
	t_bool			dirty_c;
	t_bool			dirty_l;
	t_bool			dirty_o;
	t_bool			is_plane;
	int				m_flag;
	int				f_flag;
	int				light_idx;
}	t_vars;

void			quick_sort(\
				void *start, int l_h[2], \
				size_t size, t_bool (*comparator)(void *a, void *b));
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			init_vars(t_vars *vars, t_data *data);
int				destroy_exit(t_vars *vars);
int				key_hooks(int keycode, void *vars);
int				rotate_obj(void	*self, int axis, t_bool pos);
int				translate_obj(void *self, int axis, t_bool pos);
int				translate_camera(t_camera *cam, int axis, t_bool pos);
int				mouse_hooks(int event, int x, int y, void *vars);
int				rotate_cam(t_camera *cam, int axis, t_bool pos);
void			init_cam(\
				t_camera *cam, t_vector center, t_vector direction, double fov);
int				initialize(t_vars *vars, char *filename);
void			free_split(char **split);
int				move_objs(t_hittable *obj, int keycode);
int				rotate_objs(t_hittable *objs, int keycode);
int				resize_objs(t_hittable *curr_obj, int keycode);
int				light_etc(t_vars *vars, int keycode);

#endif
