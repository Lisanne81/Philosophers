/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/27 11:24:21 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/11/29 21:04:06 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

void	printer(t_philo *philosopher, char *str, char *emoji)
{
	pthread_mutex_lock(&philosopher->data->write_lock);
	if (philosopher->state_of_mind == ALIVE || !strncmp(str, "died", 4))//let op moet ft_functie zijn
		printf("%-5lu Philosopher %-5d %-20s %s\n",
			timer(philosopher->start), philosopher->id_philosopher, str, emoji);
	pthread_mutex_unlock(&philosopher->data->write_lock);
}

bool	grab_single_fork(t_philo *philosopher, t_fork *fork)
{
	(pthread_mutex_lock(&fork->fork[philosopher->right_fork]));
	printer(philosopher, "has taken a fork", "🍽️");
	spend_time(philosopher, current_time(), philosopher->time_to_die + 200);
	return (false);
	//timer till death unlock mutex;
}

bool	grabbed_a_fork(t_fork *fork, t_philo *philosopher)
{
	if (philosopher->left_fork == philosopher->right_fork)
		return (grab_single_fork(philosopher, fork));
	if (philosopher->id_philosopher % 2 == 0)
	{
		(pthread_mutex_lock(&fork->fork[philosopher->right_fork]));
		printer(philosopher, "has taken a fork", "🍽️");
		(pthread_mutex_lock(&fork->fork[philosopher->left_fork]));
		printer(philosopher, "has taken a fork", "🍽️");
	}
	else
	{
		(pthread_mutex_lock(&fork->fork[philosopher->left_fork]));
		printer(philosopher, "has taken a fork", "🍽️");
		(pthread_mutex_lock(&fork->fork[philosopher->right_fork]));
		printer(philosopher, "has taken a fork", "🍽️");
	}
	return (true);
}

bool	dinner_time(t_fork *fork, t_philo *philosopher)
{
	bool	still_alive;

	still_alive = (grabbed_a_fork(fork, philosopher));
	if (philosopher->left_fork == philosopher->right_fork)
		pthread_mutex_unlock(&fork->fork[philosopher->right_fork]);
	else
	{
		pthread_mutex_lock(&philosopher->philo_lock);
		philosopher->last_meal = timer(philosopher->start);
		pthread_mutex_unlock(&philosopher->philo_lock);
		printer(philosopher, "is eating", "🍝");
		pthread_mutex_lock(&philosopher->philo_lock);
		philosopher->eat_count--;
		pthread_mutex_unlock(&philosopher->philo_lock);
		still_alive = spend_time(philosopher, current_time(), philosopher->eat_time);// 
		pthread_mutex_unlock(&fork->fork[philosopher->right_fork]);
		pthread_mutex_unlock(&fork->fork[philosopher->left_fork]);
	}
	return (still_alive);
}
