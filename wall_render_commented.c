
#include "cub3d.h" // Include the main header file for the project, which likely contains global definitions, structures, and function prototypes.

/* This function below is in working progress, still needs many tests */
void	ft_wall_render(t_data *d, t_rays *rc, int ray_num)
{
    double	win_x; // Variable to store the starting x-coordinate of the wall slice on the screen.
    double	col_width; // Variable to store the width of each column (or ray slice) on the screen.
    int		end_x; // Variable to store the ending x-coordinate of the wall slice on the screen.

    col_width = (double)WIDTH / N_RAYS; // Calculate the width of each column based on the screen width and the number of rays.
    if (ray_num == 0)
        win_x = 0; // If this is the first ray, the start x-coordinate is 0.
    else
        win_x = round(ray_num * col_width); // Otherwise, calculate the start x-coordinate based on the ray number and column width.
    if (ray_num == N_RAYS - 1)
        end_x = WIDTH; // If this is the last ray, the end x-coordinate is the screen width.
    else
        end_x = round((ray_num + 1) * col_width) - 1; // Otherwise, calculate the end x-coordinate for this slice.

    rc->wall_dist = ft_wall_distance(d, rc); // Calculate the distance to the wall hit by this ray.
    rc->wall_height = ft_wall_heigth(rc->wall_dist, PP); // Calculate the height of the wall slice on the screen based on the distance.
    ft_draw_wall(d, rc, win_x, (end_x - win_x) + 1); // Draw the wall slice from win_x to end_x.
}

float	ft_wall_distance(t_data *d, t_rays *rc)
{
    // Calculate and return the distance from the player to the wall hit by the ray using the Pythagorean theorem.
    return (sqrt(pow(rc->ray_x - d->ply.x, 2) + pow(rc->ray_y - d->ply.y, 2)));
}

int	ft_wall_heigth(float distance, float plane)
{
    // This function is intended to calculate and return the height of the wall slice on the screen.
    // The actual calculation is not shown, but it likely involves the distance to the wall, the player's view plane, and possibly perspective correction.
}

// This function is responsible for drawing a vertical slice of a wall on the screen.
void ft_draw_wall(t_data *d, t_rays *rc, int win_x, int col_width)
{
    int	start; // Variable to store the starting y-coordinate of the wall slice on the screen.
    int	end; // Variable to store the ending y-coordinate of the wall slice on the screen.
    int	y; // Loop variable for the y-coordinate.
    int	x; // Loop variable for the x-coordinate.

    // Calculate the middle of the window (vertically) to help center the wall slice.
    d->tx.mid_win = HEIGTH / 2;
    // Calculate the starting y-coordinate of the wall slice. It's centered around the middle of the window.
    start = d->tx.mid_win - (int)(rc->wall_height / 2);
    // If the calculated start is above the top of the screen, reset it to 0.
    if (start < 0) 
        start = 0;
    // Calculate the ending y-coordinate based on the start and the height of the wall slice.
    end = start + (int)rc->wall_height;
    // If the calculated end is below the bottom of the screen, reset it to the maximum height of the window.
    if (end >= HEIGTH)
        end = HEIGTH - 1;

    // Initialize the wall texture for rendering. This might involve setting up texture coordinates.
    ft_wall_tex_init(d, rc, start);

    // Loop through each x-coordinate in the wall slice, from the start to the end of its width.
    x = win_x;
    while (x < (win_x + col_width))
    {
        // For each column (x-coordinate), loop through each y-coordinate from the start to the end of the wall slice height.
        y = start;
        while (y < end)
        {
            // Paint the pixel at (x, y) with the appropriate texture color.
            ft_wall_paint(d, &d->tx, x, y);
            y++; // Move to the next pixel down in the current column.
        }
        x++; // Move to the next column in the wall slice.
    }
}

// This function selects the appropriate texture for the wall based on the ray's direction.
void ft_texture_select(t_data *d)
{
    // Check if the wall direction is vertical (1) or horizontal (0).
    if (d->rc.wall_dir == 1)
    {
        // For vertical walls, select texture based on the y-direction of the ray.
        if (d->rc.dir_y == 1)
            d->tx.tex_ptr = d->imgs.so_texture; // Ray facing north, use south texture.
        else
            d->tx.tex_ptr = d->imgs.no_texture; // Ray facing south, use north texture.
    }
    else
    {
        // For horizontal walls, select texture based on the x-direction of the ray.
        if (d->rc.dir_x == 1)
            d->tx.tex_ptr = d->imgs.ea_texture; // Ray facing east, use east texture.
        else
            d->tx.tex_ptr = d->imgs.we_texture; // Ray facing west, use west texture.
    }
}

// This function initializes the texture mapping for a wall slice.
void ft_wall_tex_init(t_data *d, t_rays *rc, int start)
{
    double wall_x; // Variable to store the exact hit position on the wall.

    // Select the appropriate texture based on the ray's direction.
    ft_texture_select(d);

    // Determine the exact position on the wall where the ray hits.
    if (rc->wall_dir == 0) // For horizontal walls, use the y-coordinate of the ray.
        wall_x = fmod(rc->ray_y, 1.0);
    else // For vertical walls, use the x-coordinate of the ray.
        wall_x = fmod(rc->ray_x, 1.0);

    // Ensure wall_x is positive; if not, adjust it to be within [0,1).
    if (wall_x < 0)
        wall_x += 1.0;

    // Calculate the texture's x-coordinate (tex_x) based on wall_x and the texture's width.
    d->tx.tex_x = (int)(wall_x * (double)(d->tx.tex_ptr->width));

    // If the ray is facing a certain direction, adjust tex_x to mirror the texture.
    if ((rc->wall_dir == 0 && rc->ray_x > 0) || (rc->wall_dir == 1 && rc->ray_y < 0))
        d->tx.tex_x = d->tx.tex_ptr->width - d->tx.tex_x - 1;

    // Calculate the step in texture coordinates for each pixel drawn on the screen.
    d->tx.tex_step = 1.0 * d->tx.tex_ptr->height / d->rc.wall_height;

    // Calculate the starting texture y-coordinate (tex_pos) for the slice.
    d->tx.tex_pos = (start - d->tx.mid_win + (d->rc.wall_height / 2)) * d->tx.tex_step;
}

// This function paints a single pixel of the wall with the correct texture color.
void ft_wall_paint(t_data *d, t_render *tx, int x, int y)
{
    // Calculate the texture's y-coordinate using the current texture position.
    // The bitwise AND with (texture height - 1) ensures wrapping for textures whose height is a power of 2.
    tx->tex_y = (int)tx->tex_pos & (tx->tex_ptr->height - 1);
    // Retrieve the color of the texture at the calculated x and y coordinates.
    tx->tex_color = ft_get_pix_color(tx->tex_ptr, tx->tex_x, tx->tex_y);
    // Increment the texture position by the step to move to the next pixel in the texture.
    tx->tex_pos += tx->tex_step;
    // Paint the pixel at (x, y) on the game view with the retrieved texture color.
    mlx_put_pixel(d->imgs.game_view, x, y, tx->tex_color);
}

// This function retrieves the color of a pixel from a texture.
unsigned int ft_get_pix_color(mlx_texture_t *tex, int x, int y)
{
    unsigned int pos; // Position of the pixel in the texture's pixel array.
    int r, g, b, a; // Variables to store the red, green, blue, and alpha components of the color.

    // Calculate the position of the pixel in the texture's pixel array.
    pos = 4 * x + (4 * y * tex->width);
    // Ensure the position is within the bounds of the texture's pixel data.
    if (pos <= tex->height * tex->width * tex->bytes_per_pixel)
    {
        // Extract the color components from the texture's pixel data.
        r = tex->pixels[pos];
        g = tex->pixels[pos + 1];
        b = tex->pixels[pos + 2];
        a = tex->pixels[pos + 3];
        // Combine the color components into a single unsigned integer and return it.
        return (r << 24 | g << 16 | b << 8 | a);
    }
    // If the position is out of bounds, return 0 (transparent color).
    return (0);
}
