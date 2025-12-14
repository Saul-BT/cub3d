/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 21:27:04 by gade-oli          #+#    #+#             */
/*   Updated: 2025/12/14 18:17:41 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// from gabri
// TODO: activate parser
int main(int argc, char **argv) {
  t_cub cub;
  int error;

  // from saul
  if (argc != 2)
    return (ft_error("usage: ./cub3d mapfile.cub"));
  if (!cub_init(argv[1], &cub))
    return (ERROR);

  if (!is_map_valid(cub.map) || !set_valid_textures(cub.texture, cub.win)) {
    cub_free(&cub);
    return (ERROR);
  }
  // end of saul

  // from gabri
  mlx_key_hook(cub.win->mlx, &key_hook, &cub);
  init_player(cub.player, cub.map.raw, cub.map.height);
  //draw_minimap(&cub);
  raycast(&cub);
  mlx_loop(cub.win->mlx);
  cub_free(&cub);
  // end of gabri
  return (SUCCESS);
}
// end of gabri
