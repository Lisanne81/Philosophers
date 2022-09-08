/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/08 19:09:58 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/09/08 19:51:36 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/*------COLORS--------------*/
# define R124 "\e[38;5;196m"
# define B17 "\e[38;5;202m"
# define B18 "\e[38;5;209m"
# define B19 "\e[38;5;214m"
# define B20 "\e[38;5;216m"
# define B21 "\e[38;5;21m"
# define G22 "\e[38;5;22m"
# define B23 "\e[38;5;23m"
# define Y185 "\e[38;5;185m"
# define G40 "\e[38;5;40m"
# define G41 "\e[38;5;41m"
# define G42 "\e[38;5;42m"
# define G43 "\e[38;5;43m"
# define G46 "\e[38;5;46m"
# define G47 "\e[38;5;47m"
# define G48 "\e[38;5;48m"
# define G49 "\e[38;5;49m"
# define G50 "\e[38;5;50m"
# define RESET "\e[0m"

/*------LIBRARIES--------------*/
# include "../libft/libft.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <time.h>
# include <fcntl.h>
# include <stdbool.h>

/*------STRUCTS----------------*/

// typedef struct s_philo
// {
//     /* data */
// };  t_philo


/*------FUNCTIONS--------------*/

int	ft_print_banner(int num);


#endif