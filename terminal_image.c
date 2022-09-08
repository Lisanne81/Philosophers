/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   terminal_image.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/21 20:52:37 by lisannehouk   #+#    #+#                 */
/*   Updated: 2022/09/08 19:58:55 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

static void	printline(char *line, int no)
{
	int	index;

	index = 0;
	while (index < no)
	{
		ft_putstr_fd(" ", 1);
		index++;
	}
	ft_putstr_fd(line, 1);
	ft_putchar_fd('\n', 1);
}

static void	philo_banner(int create_line)
{
	char	*line[3];
	int		index;

	line[0] = G40"    ┌─┐┬ ┬┬┬  ┌─┐┌─┐┌─┐┌─┐┬ ┬┌─┐┬─┐┌─┐";
	line[1] = G41"    ├─┘├─┤││  │ │└─┐│ │├─┘├─┤├┤ ├┬┘└─┐";
	line[2] = G42"    ┴  ┴ ┴┴┴─┘└─┘└─┘└─┘┴  ┴ ┴└─┘┴└─└─┘";

	index = 0;
	while (index < 3)
	{
		printline(line[index], create_line);
		index++;
	}
}	

static void	eat_sleep_think_banner(int create_line)
{
	char	*line[3];
	int		index;

	line[0] = R124" \n┌─┐┌─┐┌┬┐  ┌─┐┬  ┌─┐┌─┐┌─┐  ┌┬┐┬ ┬┬┌┐┌┬┌─";
	line[1] = B17"├┤ ├─┤ │   └─┐│  ├┤ ├┤ ├─┘   │ ├─┤││││├┴┐";
	line[2] = B18"└─┘┴ ┴ ┴   └─┘┴─┘└─┘└─┘┴     ┴ ┴ ┴┴┘└┘┴ ┴";
	index = 0;
	while (index < 3)
	{
		printline(line[index], create_line);
		index++;
	}
}

// static void	over_banner(int create_line)
// {
// 	char	*line[6];
// 	int		index;

// 	line[0] = B20" ██████╗ ██╗   ██╗███████╗██████╗ ";
// 	line[1] = B19"██╔═══██╗██║   ██║██╔════╝██╔══██╗";
// 	line[2] = B18"██║   ██║██║   ██║█████╗  ██████╔╝";
// 	line[3] = B17"██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗";
// 	line[4] = R124"╚██████╔╝ ╚████╔╝ ███████╗██║  ██║";
// 	line[5] = RESET" ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝";
// 	index = 0;
// 	while (index < 6)
// 	{
// 		printline(line[index], create_line);
// 		index++;
// 	}
// }

int	ft_print_banner(int num)
{
	int	index;

	index = 0;
	if (num == 1)
	{
		while (index < 1)
		{
			philo_banner(index);
			eat_sleep_think_banner(index);
			index++;
		}
	}
	// else if (num == 2)
	// {
	// 	while (index < 1)
	// 	{
	// 		keen_banner(index);
	// 		index++;
	// 	}
	// }
	return (0);
}
