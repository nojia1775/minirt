/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:46:37 by nadjemia          #+#    #+#             */
/*   Updated: 2024/11/18 19:52:23 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"
 
void	display(t_minirt *minirt)
{	
	double focal_lenght = (WIDTH / 2) / tan(convert_rad(minirt->camera->fov_x / 2));
	t_tuple v_cam_dir = vec_normalization2(minirt->camera->vector_xyz);
	
	t_tuple U, V, ref;

	ref.coor[0] = 0;
	ref.coor[1] = 1;
	ref.coor[2] = 0;

	if (double_abs(minirt->camera->vector_xyz.coor[1]) > 0.99f)
	{
		ref.coor[0] = 1;
		ref.coor[1] = 0;
		ref.coor[2] = 0;
	}

	U = vec_normalization2(vec_cross(ref, v_cam_dir));
	V = vec_normalization2(vec_cross(v_cam_dir, U));
	
	t_tuple pixel;
	t_tuple pixel_dir;

	int y = 0;
	while (y < HEIGHT)
	{
		int x = 0;
		while (x < WIDTH)
		{
			double u = ((double)x / WIDTH - 0.5) * WIDTH;
			double v = (0.5 - (double)y / HEIGHT) * HEIGHT;
			
			pixel.coor[0] = v_cam_dir.coor[0] * focal_lenght + U.coor[0] * u + V.coor[0] * v;
			pixel.coor[1] = v_cam_dir.coor[1] * focal_lenght + U.coor[1] * u + V.coor[1] * v;
			pixel.coor[2] = v_cam_dir.coor[2] * focal_lenght + U.coor[2] * u + V.coor[2] * v;

			pixel_dir = vec_normalization2(pixel);
		
			/*RAJOUTER L'EQUATION DU 2ND DEGRES POUR TROUVER INTERSECTION AVEC CERCLE*/
		}
	}
	



	printf("%f, %f, %f\n", pixel_dir.coor[0], pixel_dir.coor[1], pixel_dir.coor[2]);
}

int	put_one_color(t_minirt *minirt, int r, int g, int b)
{
	int count = 0;
	int	count2 = 0;
	int	value = create_trgb(0, r, g, b);
	while (count < 500)
	{
		count2 = 0;
		while (count2 < 500)
		{
			mlx_pixel_put(minirt->mlx, minirt->win, count, count2, value);
			count2++;
		}
		count++;
	}
	return (1);
}
