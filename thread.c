/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thread.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lhoukes <lhoukes@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/24 18:46:12 by lhoukes       #+#    #+#                 */
/*   Updated: 2022/11/25 12:45:17 by lhoukes       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"
#include <sys/time.h>
#include <unistd.h>

void	status_report(t_general *data, int id, int status)
{
	long long	stamp;

	printf("in status report\n");
	pthread_mutex_lock(&data->log_info);
	stamp = start_the_clock() - data->start_eating;
	if (data->done_eating == 0 && data->dead == 0)
	{
		if (status == GRABBED_FORK)
			printf(B23"%-8lli Philosopher %i grabbed a fork\n", stamp, id + 1);
		if (status == EAT)
			printf(Y19"%-8lli Philosopher %i eats\n", stamp, id + 1);
		if (status == SLEEP)
			printf(G42"%-8lli Philosopher %i sleeps\n", stamp, id + 1);
		if (status == THINK)
			printf(P21"%-8lli Philosopher %i thinks\n", stamp, id + 1);
	}
	if (status == DIED)
		printf("%-8lli " R124 "Philosopher %i died, RIP\n" RESET, stamp, id + 1);
	if (status == DONE && data->dead == 0)
		printf("%-8lli " G42 "All philosophers all full, because they eat %i times.\n"
			RESET, stamp, data->number_of_times_to_eat);
	pthread_mutex_unlock(&data->log_info);
}

int	grab_a_fork(t_general *data, t_philo *philosopher)
{
	printf("in grabbed a fork\n");
	if (philosopher->right_fork == philosopher->left_fork)
	{
		status_report(data, philosopher->id_philosopher, GRABBED_FORK);
		return (1);
	}
	if (pthread_mutex_lock(&data->forks[philosopher->left_fork]))
		return (1);
	status_report(data, philosopher->id_philosopher, GRABBED_FORK);
	if (pthread_mutex_lock(&data->forks[philosopher->right_fork]))
		return (1);
	status_report(data, philosopher->id_philosopher, GRABBED_FORK);
	return (0);
}

void	time_for_bed(long long night_time)
{
	long long	time;
	long long	temp;

	time = start_the_clock() + night_time;
	temp = 0;
	while (temp < time)
	{
		temp = start_the_clock();
		usleep(50);
	}
}

int	dinner_time(t_general *data, t_philo *philosopher)
{
	printf("in dinner time\n");
	if (pthread_mutex_lock(&data->set_lock))
		return (1);
	status_report(data, philosopher->id_philosopher, EAT);
	philosopher->last_meal = start_the_clock();
	if (pthread_mutex_unlock(&data->set_lock))
		return (1);
	time_for_bed(data->eat_time);
	philosopher->eat_count++;
	if (pthread_mutex_unlock(&data->forks[philosopher->left_fork]))
		return (1);
	if (pthread_mutex_unlock(&data->forks[philosopher->right_fork]))
		return (1);
	return (0);
}

void	*daily_routine(void *arg)
{
	t_general	*data;
	t_philo		*philosopher;
	printf("in daily routine\n");
	philosopher = (t_philo *)arg;
	data = philosopher->data;
	while (!data->dead)
	{
		if (grab_a_fork(data, philosopher))
			break ;
		if (dinner_time(data, philosopher))
			break ;
		if (data->done_eating)
			break ;
		status_report(data, philosopher->id_philosopher, SLEEP);
		time_for_bed(data->sleep_time);
		status_report(data, philosopher->id_philosopher, THINK);
	}
	return (NULL);
}

void	check_philo(t_general *data, t_philo *philo, int i)
{
	if (start_the_clock() - philo[i].last_meal > data->time_to_die)
	{
		status_report(data, i, DIED);
		data->dead = 1;
	}
}

void	vitals_philosopher(t_general *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (!data->done_eating)
	{
		while (i < data->num_of_philos && !data->time_to_die)
		{
			pthread_mutex_lock(&data->set_lock);
			check_philo(data, philo, i);
			pthread_mutex_unlock(&data->set_lock);
			usleep(100);
			i++;
		}
		if (data->dead)
			break ;
		i = 0;
		while (data->number_of_times_to_eat != -1 && i < data->num_of_philos
			&& philo[i].eat_count >= data->number_of_times_to_eat)
			i++;
		if (i == data->num_of_philos)
		{	
			status_report(data, 0, DONE);
			data->done_eating = 1;
		}
	}
}

int	start_thread(t_philo *philosopher, t_general *data)
{
	int	index;

	printf(G50"in start thread\n"RESET);
	index = 0;
	while(data->num_of_philos > index)
	{
		printf("in while loop thread\n");
		if (pthread_create(&philosopher[index].thread, NULL, daily_routine, &philosopher[index]))
			return (1);
		philosopher[index].last_meal = start_the_clock();
		usleep(1000);
		index++;
	}
	vitals_philosopher(data, philosopher);
	index = 0;
	while(data->num_of_philos > index)
	{
		if (pthread_join(philosopher[index].thread, NULL))
			return (1);
		index++;
		printf("join index[%d]\n", index);
	}
	return (0);
}
