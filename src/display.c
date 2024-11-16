/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nojia <nojia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:46:37 by nadjemia          #+#    #+#             */
/*   Updated: 2024/11/16 23:08:30 by nojia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	display(t_minirt *minirt)
{
	int	i;
	int	j;
	int	x;
	int	y;
	double	delta_angle_x = minirt->camera->fov_x / WIDTH;
	double	delta_angle_y = minirt->camera->fov_y / HEIGHT;
	double	vector[3] = {0};

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			x = j - WIDTH / 2;
			y = i - HEIGHT / 2;
		}
	}
}