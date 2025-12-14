/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 21:27:04 by gade-oli          #+#    #+#             */
/*   Updated: 2025/12/14 17:46:29 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void debug(t_cub *cub) {
  size_t i;

  i = 0;
  printf("NO %s\n", cub->texture[NORTH]);
  printf("SO %s\n", cub->texture[SOUTH]);
  printf("WE %s\n", cub->texture[WEST]);
  printf("EA %s\n", cub->texture[EAST]);
  printf("\n");
  printf("F %lu, %lu, %lu\n", ((unsigned long)((cub->win->floor_color >> 24) & 0xFF),
         ((unsigned long)((cub->win->floor_color >> 16) & 0xFF)),
         ((unsigned long)((cub->win->floor_color >> 8) & 0xFF))));
  printf("C %lu, %lu, %lu\n", ((unsigned long)((cub->win->ceiling_color >> 24) & 0xFF),
         ((unsigned long)((cub->win->ceiling_color >> 16) & 0xFF)),
         ((unsigned long)((cub->win->ceiling_color >> 8) & 0xFF))));
  printf("\n");
  while (cub->map.raw[i])
    printf("%s\n", cub->map.raw[i++]);
  printf("\nMap size: %ld x %ld\n", cub->map.width, cub->map.height);
  // cub_free(cub);
}

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
  debug(&cub); // TODO: Check
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
