/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dinner_time.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/27 11:24:21 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/12/02 15:57:25 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

bool	grab_single_fork(t_philo *philosopher, t_fork *fork)
{
	(pthread_mutex_lock(&fork->fork[philosopher->right_fork]));
	status(philosopher, "has taken a fork", "🍴");
	spend_time(philosopher, current_time(), philosopher->time_to_die + 200);
	return (false);
}

bool	grabbed_a_fork(t_fork *fork, t_philo *philosopher)
{
	if (philosopher->left_fork == philosopher->right_fork)
		return (grab_single_fork(philosopher, fork));
	if (philosopher->id_philosopher % 2 == 0)
	{
		(pthread_mutex_lock(&fork->fork[philosopher->right_fork]));
		status(philosopher, "has taken a fork", "🍴");
		(pthread_mutex_lock(&fork->fork[philosopher->left_fork]));
		status(philosopher, "has taken a fork", "🍴");
	}
	else
	{
		(pthread_mutex_lock(&fork->fork[philosopher->left_fork]));
		status(philosopher, "has taken a fork", "🍴");
		(pthread_mutex_lock(&fork->fork[philosopher->right_fork]));
		status(philosopher, "has taken a fork", "🍴");
	}
	return (true);
}

bool	are_you_being_served(t_philo *philosopher)
{
	pthread_mutex_lock(&philosopher->philo_lock);
	philosopher->eat_count++;
	pthread_mutex_unlock(&philosopher->philo_lock);
	if (philosopher->eat_count == philosopher->data->number_of_times_to_eat)
	{
		pthread_mutex_lock(&philosopher->data->sim_lock);
		philosopher->data->philos_eat_count++;
		pthread_mutex_unlock(&philosopher->data->sim_lock);
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
		philosopher->last_meal = time_goes_by(philosopher->data);
		pthread_mutex_unlock(&philosopher->philo_lock);
		status(philosopher, "is eating", "🥣");
		pthread_mutex_lock(&philosopher->philo_lock);
		pthread_mutex_unlock(&philosopher->philo_lock);
		still_alive = spend_time(philosopher, current_time(), \
			philosopher->eat_time);
		pthread_mutex_unlock(&fork->fork[philosopher->right_fork]);
		pthread_mutex_unlock(&fork->fork[philosopher->left_fork]);
	}
	if (still_alive)
		are_you_being_served(philosopher);
	return (still_alive);
}
