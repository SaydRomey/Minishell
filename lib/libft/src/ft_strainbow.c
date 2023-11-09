/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strainbow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:13:50 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/02 19:03:51 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
converts a hex color to rgb
example: hex_to_rgb(0xFF0000) returns (255, 0, 0)
*/
static t_color	hex_to_rgb(int hex)
{
	t_color	rgb;

	rgb.r = (hex >> 16) & 0xFF;
	rgb.g = (hex >> 8) & 0xFF;
	rgb.b = hex & 0xFF;
	return (rgb);
}

/*
sets the rgb values of the color struct according to the color index
** also works without conversion
example: palette[0] = (t_color){255, 0, 0};
*/
static void	set_rgb_values(int color_index, t_color *color)
{
	t_color	palette[10];

	palette[0] = hex_to_rgb(0xFF0000);
	palette[1] = hex_to_rgb(0xFF7F00);
	palette[2] = hex_to_rgb(0xFFFF00);
	palette[3] = hex_to_rgb(0x7FFF00);
	palette[4] = hex_to_rgb(0x00FF00);
	palette[5] = hex_to_rgb(0x00FF7F);
	palette[6] = hex_to_rgb(0x00FFFF);
	palette[7] = hex_to_rgb(0x007FFF);
	palette[8] = hex_to_rgb(0x0000FF);
	palette[9] = hex_to_rgb(0x7F00FF);
	*color = palette[color_index];
}

/*
returns 'value' if it is below 'limit', else returns 'reset'
*/
static int	reset_at(int value, int limit, int reset)
{
	if (value >= limit)
		return (reset);
	return (value);
}

/*
prints 'str' in colors of the rainbow
new_line argument is a boolean to print a newline at the end
*/
void	ft_strainbow(char *str, int new_line)
{
	int		i;
	t_color	color;
	int		color_index;

	i = 0;
	color_index = 0;
	while (str[i] != '\0')
	{
		set_rgb_values(color_index, &color);
		ft_printf(RGB "%d;%d;%dm%c" RESET, color.r, color.g, color.b, str[i]);
		i++;
		color_index++;
		color_index = reset_at(color_index, 10, 0);
	}
	if (new_line)
		ft_printf("\n");
}

//

/*
use with ansi macros ex: RED, GREEN, etc
** must be freed *
*/
char	*color_str(char *str, char *color_code)
{
	char	*colored_str;

	colored_str = ft_strjoin_with(color_code, RESET, str);
	return (colored_str);
}
