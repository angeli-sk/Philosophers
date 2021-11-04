#include "philo.h"
#include <stdio.h> /*printf*/
#include <unistd.h> /*usleep*/

static int	eating_2(t_philo_boi *philo_bois)
{
	isleepy(philo_bois->data->breaksies);
	print_actions(philo_bois, EAT);
	if (vibe_check(philo_bois) == DEATH)
	{
		pthread_mutex_unlock(philo_bois->fork_lr[RIGHT]);
		pthread_mutex_unlock(philo_bois->fork_lr[LEFT]);
		return (DEATH);
	}
	return (SUCCES);
}

int	eating(t_philo_boi *philo_bois)
{
	int				num;
	unsigned long	time;

	time = 0;
	num = philo_bois->num_philo;
	if (vibe_check(philo_bois) == DEATH)
	{
		return (DEATH);
	}
	if (philo_bois->data->num_of_philo > 1)
		pthread_mutex_lock(philo_bois->fork_lr[LEFT]);
	else
	{
		return (DEATH);
	}
	if (vibe_check(philo_bois) == DEATH)
	{
		pthread_mutex_unlock(philo_bois->fork_lr[LEFT]);
		return (DEATH);
	}
	pthread_mutex_lock(philo_bois->fork_lr[RIGHT]);
	if (eating_2(philo_bois) == DEATH)
	{
		return (DEATH);
	}
	pthread_mutex_lock(&philo_bois->data->alive_check_lock);
	philo_bois->time_last_ate = get_time();
	philo_bois->times_it_has_eaten++;
	pthread_mutex_unlock(&philo_bois->data->alive_check_lock);
	pthread_mutex_unlock(philo_bois->fork_lr[RIGHT]);
	pthread_mutex_unlock(philo_bois->fork_lr[LEFT]);
	return (SUCCES);
}

int	sleeping(t_philo_boi *philo_bois)
{
	if (print_actions(philo_bois, SLEEP) == DEATH)
		return (DEATH);
	isleepy(philo_bois->data->sleepsies);
	return (SUCCES);
}

int	thinking(t_philo_boi *philo_bois)
{
	if (print_actions(philo_bois, THINK) == DEATH)
		return (DEATH);
	return (SUCCES);
}

void	*philo_thread(void *boi)
{
	t_philo_boi		*philo_boi;

	philo_boi = boi;
	if (philo_boi->num_philo % 2 == 0)
		usleep(800);
	philo_boi->time_last_ate = get_time();
	if (pthread_create(&philo_boi->death_thread_id, NULL, \
			&death_thread, philo_boi))
			return (NULL);
	while (1)
	{
		if (eating(philo_boi) == DEATH)
			break ;
		if (sleeping(philo_boi) == DEATH)
			break ;
		if (thinking(philo_boi) == DEATH)
			break ;
		usleep(500);
	}
	if (pthread_join(philo_boi->death_thread_id, NULL))
			return (NULL);
	return (NULL);
}
