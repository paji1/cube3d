/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-mouh <tel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 13:28:11 by tel-mouh          #+#    #+#             */
/*   Updated: 2023/02/12 15:59:53 by tel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cube3d.h"

/**
 * @brief function that take as parametr from mlx_hook
*/
int	exit_game(t_vars *vars)
{
	(void)vars;
	exit(0);
}
