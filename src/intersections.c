/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrio <yrio@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:35:32 by nojia             #+#    #+#             */
/*   Updated: 2024/12/02 16:03:15 by yrio             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

double	intersec_sphere(t_minirt *minirt, t_tuple pixel, t_shape sphere)
{
	double	b;
	double	c;
	double	delta;

	b = 2 * ((minirt->camera->xyz.coor[0] - sphere.xyz.coor[0])
		* pixel.coor[0] + ((minirt->camera->xyz.coor[1]
		- sphere.xyz.coor[1]) * pixel.coor[1])
		+ ((minirt->camera->xyz.coor[2] - sphere.xyz.coor[2])
		* pixel.coor[2]));
	if (b > 0)
		return (-1);
	c = pow(minirt->camera->xyz.coor[0] - sphere.xyz.coor[0], 2)
		+ pow(minirt->camera->xyz.coor[1] - sphere.xyz.coor[1], 2)
		+ pow(minirt->camera->xyz.coor[2] - sphere.xyz.coor[2], 2)
		- pow(sphere.diameter / 2, 2);
	delta = pow(b, 2) - 4 * 1 * c;
	if (delta < 0)
		return (-1);
	if (delta == 0)
		return (-b / 2);
	return (get_min((-b + sqrt(delta)) / 2, (-b - sqrt(delta))
		/ 2));
}

double	intersec_plan(t_minirt *minirt, t_tuple pixel, t_shape plan)
{
	t_tuple	p;
	t_tuple	o;

	p = create_vector2(plan.xyz.coor[0], plan.xyz.coor[1],
		plan.xyz.coor[2]);
	o = create_vector2(minirt->camera->xyz.coor[0],
		minirt->camera->xyz.coor[1],
		minirt->camera->xyz.coor[2]);
	if (dot_product2(plan.vector_xyz, pixel) == 0)
		return (-1);
	return ((dot_product2(plan.vector_xyz,
		vec_sub_vec2(p, o)))
		/ dot_product2(plan.vector_xyz, pixel));
}
static int	point_in_cylinder(t_shape cy, t_point intersec)
{
	t_tuple	intersec_proj;

	intersec_proj = vec_add_vec2(*(t_tuple *)&cy.xyz, vec_multiplication2(
		cy.vector_xyz, dot_product2(create_vector2(
		intersec.coor[0] - cy.xyz.coor[0],
		intersec.coor[1] - cy.xyz.coor[1],
		intersec.coor[2] - cy.xyz.coor[2]), cy.vector_xyz)));
	if (dot_product2(create_vector2(intersec_proj.coor[0] - cy.xyz.coor[0],
		intersec_proj.coor[1] - cy.xyz.coor[1],
		intersec_proj.coor[2] - cy.xyz.coor[2]), cy.vector_xyz) < 0)
		return (0);
	if (vec_magnitude2(create_vector2(
		intersec_proj.coor[0] - cy.xyz.coor[0],
		intersec_proj.coor[1] - cy.xyz.coor[1],
		intersec_proj.coor[2] - cy.xyz.coor[2])) > cy.height)
		return (0);
	return (1);
}

// static void	get_bases_cy(t_shape cy, t_shape *base1, t_shape *base2)
// {
// 	base1->xyz.coor[0] = cy.xyz.coor[0];
// 	base1->xyz.coor[1] = cy.xyz.coor[1];
// 	base1->xyz.coor[2] = cy.xyz.coor[2];
// 	base1->vector_xyz = cy.vector_xyz;
// 	cy.xyz = apply_vec_to_nbr(vec_multiplication2(cy.vector_xyz, cy.height), cy.xyz);
// 	base2->xyz.coor[0] = cy.xyz.coor[0];
// 	base2->xyz.coor[1] = cy.xyz.coor[1];
// 	base2->xyz.coor[2] = cy.xyz.coor[2];
// 	base2->vector_xyz = cy.vector_xyz;
// }

double	intersec_cylinder(t_minirt *minirt, t_tuple pixel, t_shape cy)
{
	double	quadratic[3];
	double	delta;
	t_point	intersec;
	t_tuple	oc;
	// t_shape	base1;
	// t_shape	base2;
	// double	b1;
	// double	b2;

	oc = vec_sub_vec2(*(t_tuple *)&minirt->camera->xyz,
		*(t_tuple *)&cy.xyz);
	pixel = vec_normalization2(pixel);
	quadratic[0] = dot_product2(pixel, pixel) - pow(dot_product2(pixel,
		vec_normalization2(cy.vector_xyz)), 2);
	quadratic[1] = 2 * (dot_product2(pixel, oc) - dot_product2(pixel, cy.vector_xyz)
		* dot_product2(oc, cy.vector_xyz));
	quadratic[2] = dot_product2(oc, oc) - pow(dot_product2(oc, cy.vector_xyz), 2) - pow(cy.diameter / 2, 2);
	delta = pow(quadratic[1], 2) - 4 * quadratic[0] * quadratic[2];
	if (delta < 0)
		return (-1);
	intersec = apply_vec_to_nbr(vec_multiplication2(pixel, get_min((
		-quadratic[1] + sqrt(delta)) / (2 * quadratic[0]),
		(-quadratic[1] - sqrt(delta)) / (2 * quadratic[0]))),
		minirt->camera->xyz);
	if (!point_in_cylinder(cy, intersec))
		return (-1);
	// get_bases_cy(cy, &base1, &base2);
	// b1 = intersec_plan(minirt, pixel, base1);
	// b2 = intersec_plan(minirt, pixel, base2);
	// if (b1 < 0)
	// 	b1 = 1e10;
	// if (b2 < 0)
	// 	b2 = 1e10;
	return (/*get_min(b2, get_min(b1, */get_min((-quadratic[1] + sqrt(delta)) / (2 * quadratic[0]),
		(-quadratic[1] - sqrt(delta)) / (2 * quadratic[0])))/*))*/;
}

