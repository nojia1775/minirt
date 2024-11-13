/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:56:25 by yrio              #+#    #+#             */
/*   Updated: 2024/11/13 16:37:33 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_matrix *alloc_matrix(t_matrix *mat, int x, int y, int z)
{
	int	count;
	int	count2;

	mat = malloc(sizeof(t_matrix));
	mat->shape[0] = x;
	mat->shape[1] = y;
	mat->shape[2] = z;
	mat->array = (int ***)malloc((mat->shape[0] + 1) * sizeof(int **));
	count = 0;
	while (count < mat->shape[0])
	{
		mat->array[count] = (int **)malloc((mat->shape[1] + 1) * sizeof(int *));
		count2 = 0;
		while (count2 < mat->shape[1])
		{
			mat->array[count][count2] = (int *)malloc((mat->shape[2] + 1) * sizeof(int));
			count2++;
		}
		count++;
	}
	return (mat);
}

t_matrix create_matrix(int x, int y, int z)
{
	t_matrix	*mat;
	int			count;
	int			count2;
	int			count3;

	mat = NULL;
	mat = alloc_matrix(mat, x, y, z);
	count = 0;
	while (count < x)
	{
		count2 = 0;
		while (count2 < y)
		{
			count3 = 0;
			while (count3 < z)
			{
				mat->array[count][count2][count3] = 0;
				count3++;
			}
			count2++;
		}
		count++;
	}
	return (*mat);
}

void	display_mat2d(t_matrix *mat, int axis_1, int axis_2, int slice_axis_3)
{
	int	count;
	int	count2;

	count = 0;
	if (axis_1 == 1 && axis_2 == 2)
	{
		while (count < mat->shape[0])
		{
			count2 = 0;
			while (count2 < mat->shape[1])
			{
				printf("%d", mat->array[count][count2][slice_axis_3]);
				count2++;
			}
			printf("\n");
			count++;
		}
	}
	count = 0;
	if (axis_1 == 1 && axis_2 == 3)
	{
		while (count < mat->shape[0])
		{
			count2 = 0;
			while (count2 < mat->shape[2])
			{
				printf("%d", mat->array[count][slice_axis_3][count2]);
				count2++;
			}
			printf("\n");
			count++;
		}
	}
	count = 0;
	if (axis_1 == 2 && axis_2 == 3)
	{
		while (count < mat->shape[1])
		{
			count2 = 0;
			while (count2 < mat->shape[2])
			{
				printf("%d", mat->array[slice_axis_3][count][count2]);
				count2++;
			}
			printf("\n");
			count++;
		}
	}
}

