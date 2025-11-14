/* ************************************************************************** */
/*                                                                            */
/*                           cub3d - 2D Starter                              */
/*                     Minimap + Player + Raycasting                         */
/*                                                                            */
/* ************************************************************************** */

#include "lib/MLX42/include/MLX42/MLX42.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define TILE_SIZE 64
#define FOV 60  // Field of view in degrees
#define NUM_RAYS 60  // Number of rays to cast

// Map: 1 = wall, 0 = empty
int g_map[8][8] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1}
};

typedef struct s_player
{
    double  x;          // Position in grid coordinates (e.g., 3.5 = middle of tile 3)
    double  y;
    double  angle;      // Direction in radians
    double  fov;        // Field of view in radians
}   t_player;

typedef struct s_game
{
    mlx_t           *mlx;
    mlx_image_t     *image;
    t_player        player;
    int             map_width;
    int             map_height;
}   t_game;

// ============================================================================
//                              UTILITY FUNCTIONS
// ============================================================================

double  deg_to_rad(double degrees)
{
    return degrees * M_PI / 180.0;
}

void    my_put_pixel(mlx_image_t *img, int x, int y, uint32_t color)
{
    if (x >= 0 && x < (int)img->width && y >= 0 && y < (int)img->height)
        mlx_put_pixel(img, x, y, color);
}

// ============================================================================
//                              DRAWING FUNCTIONS
// ============================================================================

void    draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1, uint32_t color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;
    
    while (1)
    {
        my_put_pixel(img, x0, y0, color);
        
        if (x0 == x1 && y0 == y1)
            break;
        
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void    draw_rectangle(mlx_image_t *img, int x, int y, int width, int height, uint32_t color)
{
    for (int i = y; i < y + height; i++)
        for (int j = x; j < x + width; j++)
            my_put_pixel(img, j, i, color);
}

void    draw_circle(mlx_image_t *img, int cx, int cy, int radius, uint32_t color)
{
    for (int y = -radius; y <= radius; y++)
    {
        for (int x = -radius; x <= radius; x++)
        {
            if (x * x + y * y <= radius * radius)
                my_put_pixel(img, cx + x, cy + y, color);
        }
    }
}

// ============================================================================
//                              MAP DRAWING
// ============================================================================

void    draw_map(t_game *game)
{
    for (int y = 0; y < game->map_height; y++)
    {
        for (int x = 0; x < game->map_width; x++)
        {
            uint32_t color;
            
            if (g_map[y][x] == 1)
                color = 0x444444FF;  // Wall - dark gray
            else
                color = 0x222222FF;  // Floor - darker gray
            
            draw_rectangle(game->image,
                x * TILE_SIZE,
                y * TILE_SIZE,
                TILE_SIZE - 2,  // -2 for grid lines
                TILE_SIZE - 2,
                color);
        }
    }
}

// ============================================================================
//                              RAYCASTING
// ============================================================================

typedef struct s_ray_result
{
    int     hit;
    double  distance;
    int     map_x;
    int     map_y;
}   t_ray_result;

t_ray_result    cast_single_ray(t_game *game, double angle)
{
    t_ray_result result = {0, 0, 0, 0};
    
    double ray_x = game->player.x;
    double ray_y = game->player.y;
    double ray_dir_x = cos(angle);
    double ray_dir_y = sin(angle);
    
    // DDA setup
    int map_x = (int)ray_x;
    int map_y = (int)ray_y;
    
    double delta_dist_x = fabs(1.0 / ray_dir_x);
    double delta_dist_y = fabs(1.0 / ray_dir_y);
    
    int step_x = ray_dir_x < 0 ? -1 : 1;
    int step_y = ray_dir_y < 0 ? -1 : 1;
    
    double side_dist_x = ray_dir_x < 0 ?
        (ray_x - map_x) * delta_dist_x :
        (map_x + 1.0 - ray_x) * delta_dist_x;
    
    double side_dist_y = ray_dir_y < 0 ?
        (ray_y - map_y) * delta_dist_y :
        (map_y + 1.0 - ray_y) * delta_dist_y;
    
    // Perform DDA
    int hit = 0;
    int side = 0;
    
    while (!hit)
    {
        // Jump to next square
        if (side_dist_x < side_dist_y)
        {
            side_dist_x += delta_dist_x;
            map_x += step_x;
            side = 0;
        }
        else
        {
            side_dist_y += delta_dist_y;
            map_y += step_y;
            side = 1;
        }
        
        // Check bounds
        if (map_x < 0 || map_x >= game->map_width ||
            map_y < 0 || map_y >= game->map_height)
            break;
        
        // Check if hit wall
        if (g_map[map_y][map_x] == 1)
            hit = 1;
    }
    
    // Calculate distance
    double distance;
    if (side == 0)
        distance = (map_x - ray_x + (1 - step_x) / 2.0) / ray_dir_x;
    else
        distance = (map_y - ray_y + (1 - step_y) / 2.0) / ray_dir_y;
    
    result.hit = hit;
    result.distance = distance;
    result.map_x = map_x;
    result.map_y = map_y;
    
    return result;
}

void    draw_rays(t_game *game)
{
    double fov_half = game->player.fov / 2.0;
    double ray_angle_step = game->player.fov / NUM_RAYS;
    
    for (int i = 0; i < NUM_RAYS; i++)
    {
        double ray_angle = game->player.angle - fov_half + (i * ray_angle_step);
        
        t_ray_result result = cast_single_ray(game, ray_angle);
        
        if (result.hit)
        {
            // Calculate end point of ray for drawing
            double end_x = game->player.x + cos(ray_angle) * result.distance;
            double end_y = game->player.y + sin(ray_angle) * result.distance;
            
            // Draw the ray line
            draw_line(game->image,
                (int)(game->player.x * TILE_SIZE),
                (int)(game->player.y * TILE_SIZE),
                (int)(end_x * TILE_SIZE),
                (int)(end_y * TILE_SIZE),
                0xFF6B6B44);  // Semi-transparent red
        }
    }
}

void    draw_fov_cone(t_game *game)
{
    double fov_half = game->player.fov / 2.0;
    double ray_length = 10.0;  // Length for FOV visualization
    
    // Left edge of FOV
    double left_angle = game->player.angle - fov_half;
    int left_x = (int)(game->player.x * TILE_SIZE + cos(left_angle) * ray_length * TILE_SIZE);
    int left_y = (int)(game->player.y * TILE_SIZE + sin(left_angle) * ray_length * TILE_SIZE);
    
    // Right edge of FOV
    double right_angle = game->player.angle + fov_half;
    int right_x = (int)(game->player.x * TILE_SIZE + cos(right_angle) * ray_length * TILE_SIZE);
    int right_y = (int)(game->player.y * TILE_SIZE + sin(right_angle) * ray_length * TILE_SIZE);
    
    int px = (int)(game->player.x * TILE_SIZE);
    int py = (int)(game->player.y * TILE_SIZE);
    
    draw_line(game->image, px, py, left_x, left_y, 0x4ECDC4FF);   // Cyan
    draw_line(game->image, px, py, right_x, right_y, 0x4ECDC4FF); // Cyan
}

void    draw_player(t_game *game)
{
    int px = (int)(game->player.x * TILE_SIZE);
    int py = (int)(game->player.y * TILE_SIZE);
    
    // Draw player as circle
    draw_circle(game->image, px, py, 8, 0x4ECDC4FF);  // Cyan
    
    // Draw direction line
    int dir_x = px + (int)(cos(game->player.angle) * 20);
    int dir_y = py + (int)(sin(game->player.angle) * 20);
    draw_line(game->image, px, py, dir_x, dir_y, 0xFFFFFFFF);  // White
}

// ============================================================================
//                              PLAYER MOVEMENT
// ============================================================================

void    move_player(t_game *game, double dx, double dy)
{
    double new_x = game->player.x + dx;
    double new_y = game->player.y + dy;
    
    // Check collision with map boundaries
    if (new_x < 0 || new_x >= game->map_width ||
        new_y < 0 || new_y >= game->map_height)
        return;
    
    // Check collision with walls
    if (g_map[(int)new_y][(int)new_x] == 0)
    {
        game->player.x = new_x;
        game->player.y = new_y;
    }
}

void    handle_input(t_game *game)
{
    double move_speed = 0.05;
    double rot_speed = 0.03;
    
    // W - Move forward
    if (mlx_is_key_down(game->mlx, MLX_KEY_W))
    {
        double dx = cos(game->player.angle) * move_speed;
        double dy = sin(game->player.angle) * move_speed;
        move_player(game, dx, dy);
    }
    
    // S - Move backward
    if (mlx_is_key_down(game->mlx, MLX_KEY_S))
    {
        double dx = -cos(game->player.angle) * move_speed;
        double dy = -sin(game->player.angle) * move_speed;
        move_player(game, dx, dy);
    }
    
    // A - Strafe left
    if (mlx_is_key_down(game->mlx, MLX_KEY_A))
    {
        double dx = -sin(game->player.angle) * move_speed;
        double dy = cos(game->player.angle) * move_speed;
        move_player(game, dx, dy);
    }
    
    // D - Strafe right
    if (mlx_is_key_down(game->mlx, MLX_KEY_D))
    {
        double dx = sin(game->player.angle) * move_speed;
        double dy = -cos(game->player.angle) * move_speed;
        move_player(game, dx, dy);
    }
    
    // Left arrow - Rotate left
    if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
        game->player.angle -= rot_speed;
    
    // Right arrow - Rotate right
    if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
        game->player.angle += rot_speed;
    
    // ESC - Exit
    if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(game->mlx);
}

// ============================================================================
//                              MAIN GAME LOOP
// ============================================================================

void    game_loop(void *param)
{
    t_game *game = (t_game *)param;
    
    // Handle input
    handle_input(game);
    
    // Clear screen (fill with black)
    for (uint32_t y = 0; y < game->image->height; y++)
        for (uint32_t x = 0; x < game->image->width; x++)
            mlx_put_pixel(game->image, x, y, 0x000000FF);
    
    // Draw everything
    draw_map(game);
    draw_rays(game);
    draw_fov_cone(game);
    draw_player(game);
}

// ============================================================================
//                              INITIALIZATION
// ============================================================================

int main(void)
{
    t_game game;
    
    // Initialize map size
    game.map_width = 8;
    game.map_height = 8;
    
    // Initialize player
    game.player.x = 3.5;
    game.player.y = 3.5;
    game.player.angle = 0.0;  // Facing right
    game.player.fov = deg_to_rad(FOV);
    
    // Initialize MLX
    game.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d - 2D View", true);
    if (!game.mlx)
    {
        printf("Error: MLX initialization failed\n");
        return (1);
    }
    
    // Create image
    game.image = mlx_new_image(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!game.image)
    {
        printf("Error: Image creation failed\n");
        mlx_terminate(game.mlx);
        return (1);
    }
    
    // Display image
    if (mlx_image_to_window(game.mlx, game.image, 0, 0) < 0)
    {
        printf("Error: Failed to display image\n");
        mlx_terminate(game.mlx);
        return (1);
    }
    
    // Register game loop
    mlx_loop_hook(game.mlx, game_loop, &game);
    
    // Start the loop
    mlx_loop(game.mlx);
    
    // Cleanup
    mlx_terminate(game.mlx);
    
    return (0);
}

/* ************************************************************************** */
/*                              CONTROLS:                                    */
/*                                                                            */
/*   W/S - Move forward/backward                                             */
/*   A/D - Strafe left/right                                                 */
/*   LEFT/RIGHT arrows - Rotate view                                         */
/*   ESC - Exit                                                              */
/*                                                                            */
/* ************************************************************************** */
