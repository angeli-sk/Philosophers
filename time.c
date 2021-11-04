#include "philo.h"
#include <sys/time.h> /*int gettimeofday */
#include <unistd.h> /*usleep*/
#include <stdio.h> /*printf*/


unsigned long	get_time(void)
{
	long long		t;
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (ERROR);
	t = tv.tv_sec * 1000;
	t += tv.tv_usec / 1000;
	return (t);
}

void	isleepy(unsigned long ms)
{
	unsigned long	entry;

	entry = get_time();
	while ((get_time() - entry) < ms)
		usleep(150);
}

static int	death_thread_ate_enough_check(t_philo_boi *philo_bois)
{
	if (philo_bois->data->diet != 0 && philo_bois->alive_print == true \
		&& philo_bois->times_it_has_eaten == philo_bois->data->diet)
	{
		printf("[%lu] Philo %d ate enough_______\n", \
			(get_time() - philo_bois->data->start_time), philo_bois->num_philo);
		philo_bois->data->full_philo_counter++;
		philo_bois->alive_print = false;
	}
	if (philo_bois->data->diet != 0 && philo_bois->data->full_philo_counter \
		== philo_bois->data->num_of_philo \
			)
	{
		philo_bois->data->alive = false;
		return (EXIT);
	}
	return (SUCCES);
}

static int	death_thread_last_ate_check(t_philo_boi *philo_bois)
{
	if (((long)get_time() - (long)philo_bois->time_last_ate) \
			>= philo_bois->data->deathsies)
	{
		usleep (500);
		pthread_mutex_lock(&philo_bois->data->print);
		if (philo_bois->data->alive == true)
			printf("[%lu] Philo %d died XXXXX\n", \
			(get_time() - philo_bois->data->start_time), philo_bois->num_philo);
		pthread_mutex_unlock(&philo_bois->data->print);
		philo_bois->data->alive = false;
		return (EXIT);
	}
	return (SUCCES);
}

void	*death_thread(void *boi)
{
	t_philo_boi	*philo_bois;

	philo_bois = boi;
	while (1)
	{
		usleep(1500);
		pthread_mutex_lock(&philo_bois->data->alive_check_lock);
		if (death_thread_ate_enough_check(philo_bois) == EXIT)
		{
			pthread_mutex_unlock(&philo_bois->data->alive_check_lock);
			return (NULL);
		}
		if (death_thread_last_ate_check(philo_bois) == EXIT)
		{
			pthread_mutex_unlock(&philo_bois->data->alive_check_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&philo_bois->data->alive_check_lock);
	}
}
