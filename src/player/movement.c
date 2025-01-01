/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeuzela <rmeuzela@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/31 15:06:32 by rmeuzela      #+#    #+#                 */
/*   Updated: 2024/12/31 16:19:22 by rmeuzela      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "MLX42/MLX42.h"

void	move_player(void *param)
{
	mlx_t			*mlx;
	static double	pos = 0;

	mlx = (mlx_t *)param;
	printf("delta time: %f\n", mlx->delta_time);
	pos = pos * 2 * mlx->delta_time;
	printf("pos: %f\n", pos);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		printf("GO UP!\n");
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		printf("GO DOWN!\n");
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		printf("GO LEFT!\n");
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		printf("GO RIGHT!\n");
	}
}
