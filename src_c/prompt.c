/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 23:54:58 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/07 17:14:09 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
creates the prompt string for readline,
by joining "PRMPT_PREFIX" and "PRMPT_SUFFIX"
with the value of the key "USER" in 'env' list
or with "PRMPT_DFLT" if "USER" is not found
** (must be freed) *
*/
static char	*setup_prompt(t_list *env)
{
	char	*user;
	char	*prompt;

	user = get_var_value(env, "USER");
	if (!user)
		user = PRMPT_DFLT;
	prompt = ft_strjoin_with(PRMPT_PREFIX, PRMPT_SUFFIX, user);
	return (prompt);
}

/*
updates the prompt string in t_info
*/
void	set_prompt(void)
{
	t_info	*info;

	info = call_info();
	if (info->prompt)
	{
		free(info->prompt);
		info->prompt = NULL;
	}
	info->prompt = setup_prompt(info->envlst);
}

/*
updates and returns the prompt string in t_info
*/
char	*get_prompt(void)
{
	t_info	*info;

	info = call_info();
	set_prompt();
	return (info->prompt);
}

/*
sets the ansi color code for the prompt
*/
static void	colorized_palette(int index, char **color)
{
	char	*palette[10];

	palette[0] = LAVENDER;
	palette[1] = MAGENTA;
	palette[2] = RED;
	palette[3] = ORANGE;
	palette[4] = YELLOW;
	palette[5] = GREEN;
	palette[6] = TURQUOISE;
	palette[7] = BLUE;
	palette[8] = INDIGO;
	palette[9] = VIOLET;
	*color = palette[index];
}

/*
sets the color of the prompt and the command line
uses the last digit of shlvl to choose which string to print
*/
void	colorized_prmpt(void)
{
	char	*shlvl_str;
	int		shlvl;
	int		last_digit;
	char	*color;

	shlvl_str = (get_var_value(get_envlist(), "SHLVL"));
	if (!shlvl_str || ft_str_isdigit(shlvl_str) == FALSE)
		shlvl = PRMPT_CLR_DFLT;
	else
		shlvl = ft_atoi(shlvl_str);
	last_digit = ft_abs(shlvl);
	last_digit %= 10;
	colorized_palette(last_digit, &color);
	ft_printf(color);
	ft_printf(BOLD);
	ft_printf(ITALIC);
}
