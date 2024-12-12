/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:06:21 by yrio              #+#    #+#             */
/*   Updated: 2024/12/02 11:39:02 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_tuple normal_vector_sphere(t_shape sphere, t_tuple point)
{
    t_tuple *vector;

    if (sphere.type == 1)
        vector = create_tuple(point.coor[0], point.coor[1], point.coor[2], 1);
    else
        vector = create_tuple(0, 0, 0, 1);
    return (*vector);
}

// double  lighting(t_minirt *minirt, t_tuple point, t_tuple eyev, t_shape *shape)
// {
//     double  ambient = 1;
//     double  diffuse = 0.9;
//     double  specular = 0.1;
// 	t_tuple	normal;
// 	t_tuple lightv;
//     // t_tuple pixel = negate_tuple(eyev);
//     double  factor;

// 	if (shape->type == SPHERE)
// 		normal = create_tuple2(point.coor[0] - shape->xyz.coor[0], point.coor[1] - shape->xyz.coor[1], point.coor[2] - shape->xyz.coor[2]);
// 	else
// 		normal = shape->vector_xyz;
//     normal = vec_normalization2(normal);
//     double effective_color = ((double)shape->rgb[0] / 255) * ((double)minirt->light->rgb[0] / 255) + ((double)shape->rgb[1] / 255) * ((double)minirt->light->rgb[1] / 255) + ((double)shape->rgb[2] / 255) * ((double)minirt->light->rgb[2] / 255);
//     lightv = vec_normalization2(vec_sub_vec2(minirt->light->xyz, point));
//     ambient = effective_color * ambient;

//     double light_dot_normal = dot_product2(lightv, normal);
//     if (light_dot_normal < 0)
//     {
//         diffuse = 0;
//         specular = 0;
//     }
//     else
//     {
//         diffuse = effective_color * diffuse * light_dot_normal;
//         t_tuple reflectv = reflect(negate_tuple(lightv), normal);
//         reflectv = vec_normalization2(reflectv);
//         eyev = vec_normalization2(eyev);
//         double  reflect_dot_eye = dot_product2(reflectv, eyev);
//         if (reflect_dot_eye <= 0)
//             specular = 0;
//         else
//         {
//             factor = pow(reflect_dot_eye, 100.0);

//             specular = 1 * specular * factor; 
//         }
//     }
//     return (ambient + diffuse + specular);
// }

t_tuple	reflect(t_tuple in, t_tuple normal)
{
	return (vec_sub_vec2(in, vec_multiplication2(normal, 2 * dot_product2(in, normal))));
}

static double	min_diffuse(double diffuse)
{
	if (diffuse > 0.25)
		return (diffuse);
	else
		return (0.25);
}

double	lightning(t_minirt *minirt, t_tuple ray, t_shape *shape, t_tuple intersection)
{
	t_tuple	light_ray;
	t_tuple	normal_shape;
	t_tuple	reflection;
	double	diffuse;
	t_uint8	rgb[3];

	light_ray = vec_normalization2(vec_sub_vec2(minirt->light->xyz, intersection));
	if (shape->type == SPHERE)
		normal_shape = vec_normalization2(vec_sub_vec2(shape->xyz, intersection));
	else
		normal_shape = vec_normalization2(shape->vector_xyz);
	reflection = vec_normalization2(reflect(ray, normal_shape));
	printf("reflection : ");
	print_coor(&reflection);
	printf("-light_ray : ");
	print_coor(&light_ray);
	diffuse = min_diffuse(dot_product2(reflection, light_ray));
	printf("diffuse = %f\n", diffuse);
	rgb[0] = shape->rgb[0] * diffuse;
	rgb[1] = shape->rgb[1] * diffuse;
	rgb[2] = shape->rgb[2] * diffuse;
	printf("r = %d g = %d b = %d\n", rgb[0], rgb[1], rgb[2]);
	return (convert_rgb(rgb));
}
