/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_line_utilities.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/14 23:26:38 by rmeuzela      #+#    #+#                 */
/*   Updated: 2025/01/15 18:48:16 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "shapes.h"
#include "libft.h"

static void	swap_points(t_vector2dint *point_1, t_vector2dint *point_2)
{
	t_vector2dint	swap;

	ft_memcpy(&swap, point_1, sizeof(t_vector2dint));
	ft_memcpy(point_1, point_2, sizeof(t_vector2dint));
	ft_memcpy(point_2, &swap, sizeof(t_vector2dint));
}

static void	set_deltas(int *delta_x, int *delta_y, t_vector2dint point_1, \
			t_vector2dint point_2)
{
	*delta_x = point_2.x - point_1.x;
	*delta_y = point_2.y - point_1.y;
}

static void	set_direction(int *direction, int delta)
{
	*direction = 1;
	if (delta < 0)
	{
		*direction = -1;
	}
}

void	draw_line_horizontal(t_vector2dint point_1, t_vector2dint point_2, \
		mlx_image_t *image, uint32_t color)
{
	int				delta_x;
	int				delta_y;
	t_vector2dint	point;
	int				direction;
	int				parameter;

	if (point_1.x > point_2.x)
		swap_points(&point_1, &point_2);
	set_deltas(&delta_x, &delta_y, point_1, point_2);
	ft_memcpy(&point, &point_1, sizeof(t_vector2dint));
	set_direction(&direction, delta_y);
	delta_y *= direction;
	parameter = 2 * delta_y - delta_x;
	while (point.x <= point_2.x)
	{
		mlx_put_pixel(image, point.x, point.y, color);
		point.x++;
		if (parameter < 0)
			parameter = parameter + 2 * delta_y;
		else
		{
			parameter = parameter + 2 * delta_y - 2 * delta_x;
			point.y += direction;
		}
	}
}

void	draw_line_vertical(t_vector2dint point_1, t_vector2dint point_2, \
		mlx_image_t *image, uint32_t color)
{
	int				delta_x;
	int				delta_y;
	t_vector2dint	point;
	int				direction;
	int				parameter;

	if (point_1.y > point_2.y)
		swap_points(&point_1, &point_2);
	set_deltas(&delta_x, &delta_y, point_1, point_2);
	ft_memcpy(&point, &point_1, sizeof(t_vector2dint));
	set_direction(&direction, delta_x);
	delta_x *= direction;
	parameter = 2 * delta_x - delta_y;
	while (point.y <= point_2.y)
	{
		mlx_put_pixel(image, point.x, point.y, color);
		point.y++;
		if (parameter < 0)
			parameter = parameter + 2 * delta_x;
		else
		{
			parameter = parameter + 2 * delta_x - 2 * delta_y;
			point.x += direction;
		}
	}
}
