/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:02:16 by nadjemia          #+#    #+#             */
/*   Updated: 2024/11/14 15:42:45 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H

# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

typedef unsigned char t_uint8;

typedef struct s_light
{
	double		xyz[3];
	double		luminosity;
	t_uint8	rgb[3];
}	t_light;

typedef struct s_ambient
{
	double		ambient;
	t_uint8	rgb[3];
}	t_ambient;

typedef struct s_camera
{
	double		xyz[3];
	double		vector_xyz[3];
	t_uint8	fov;
}	t_camera;

typedef struct s_matrix
{
	int	shape[3];
	int	***array;
}	t_matrix;

typedef struct s_shape
{
	double		xyz[3];
	t_uint8	rgb[3];
	double		height;
	double		diameter;
	double		vector_xyz[3];
	t_matrix 	*mat;
}	t_shape;

typedef struct s_minirt
{
	t_shape		*sphere;
	t_shape		*plan;
	t_shape		*cylinder;
	t_camera	*camera;
	t_light		*light;
	t_ambient	*ambient;
}	t_minirt;

typedef struct s_vector
{
	double coor[3];
}	t_vector;

//vector_utils
t_vector	*create_vector(double x, double y, double z);

//vector_operation
t_vector	*vec_add_nbr(t_vector *vec, double nbr);
t_vector	*vec_add_vec(t_vector *vec, t_vector *add);
t_vector	*vec_sub_vec(t_vector *vec, t_vector *add);
double		vec_magnitude(t_vector *vec);
double		dot_product(t_vector *first, t_vector *second, int length);
t_vector	*vec_normalization(t_vector *vec);
t_vector	*vec_multiplication(t_vector *vec, double scalar);

//matrix
t_matrix	*alloc_matrix(t_matrix *mat, int x, int y, int z);
t_matrix	create_matrix(int x, int y, int z);
void		display_mat2d(t_matrix *mat, int axis_1, int axis_2, int slice_axis_3);

//sphere
t_shape		create_sphere(int height);

int			parsing(int argc, char **argv, char **env);

#endif