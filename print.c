#include "philo.h"
#include <stdio.h> /*printf*/
#include <unistd.h> /*usleep*/

static int	alive_check_print(t_philo_boi *philo_bois)
{
	pthread_mutex_lock(&philo_bois->data->alive_check_lock);
	if (philo_bois->data->alive == false)
	{
		pthread_mutex_unlock(&philo_bois->data->alive_check_lock);
		return (DEATH);
	}
	pthread_mutex_unlock(&philo_bois->data->alive_check_lock);
	return (0);
}

int	print_actions(t_philo_boi *philo_bois, int mood)
{
	if (alive_check_print(philo_bois) == DEATH)
		return (DEATH);
	pthread_mutex_lock(&philo_bois->data->print);
	if (mood == EAT)
	{
		// printf("       \033[38;5;%dm[%ld]Philo %d took a fork\033[0m\n", \
		// 	philo_bois->data->colors[philo_bois->num_philo], \
		// 	get_time() - philo_bois->data->start_time, philo_bois->num_philo);
		// printf("       \033[38;5;%dm[%ld]Philo %d is eating\033[0m\n", \
		// 	philo_bois->data->colors[philo_bois->num_philo], \
		// 	get_time() - philo_bois->data->start_time, philo_bois->num_philo);
		printf("[%ld]Philo %d took fork\n", get_time() - philo_bois->data->start_time, \
		philo_bois->num_philo);
		printf("[%ld]Philo %d is eating\n", get_time() - philo_bois->data->start_time, philo_bois->num_philo);
	}
	else if (mood == SLEEP)
	{
		// printf("       \033[38;5;%dm[%ld]Philo %d is sleeping\033[0m\n", \
		// 	philo_bois->data->colors[philo_bois->num_philo], \
		// 	get_time() - philo_bois->data->start_time, philo_bois->num_philo);
		printf("[%ld]Philo %d is sleeping\n", get_time( )- philo_bois->data->start_time, philo_bois->num_philo);
	}
	else if (mood == THINK)
	{
		// printf("       \033[38;5;%dm[%ld]Philo %d is thinking\033[0m\n", \
		// 	philo_bois->data->colors[philo_bois->num_philo], \
		// 	get_time() - philo_bois->data->start_time, philo_bois->num_philo);
		printf("[%ld]Philo %d is sleeping\n", get_time( )- philo_bois->data->start_time, philo_bois->num_philo);
	}
	pthread_mutex_unlock(&philo_bois->data->print);
	return (0);
}

void	print_start(t_philo_boi *philo_bois)
{
	printf("Number of \e[1mphilo bois\e[0m: \e[32m%d\e[0m\n",
		philo_bois->data->num_of_philo);
	printf("\e[1mTime\e[0m for the bois \e[1mto die\e[0m is after: \
\e[31m%d\e[0m milliseconds\n", philo_bois->data->deathsies);
	printf("Breaksies \e[1mto eat\e[0m lasts: \e[33m%d\e[0m milliseconds\n",
		philo_bois->data->breaksies);
	printf("\e[1mSleepsies time\e[0m is after: \e[36m%d\e[0m milliseconds\n",
		philo_bois->data->sleepsies);
	if (philo_bois->data->diet > 0)
		printf("\e[3mEXTRA; They need to eat: \e[34m%d\e[0m\e[3m\
 amount of times then they can die in peace\e[0m\n"\
		, philo_bois->data->diet);
	printf("╔═════════════  🤔  ═════════════╗\n");
}

/*
		printf("       \033[38;5;%dm[%ld]Philo %d is eating\033[0m\n", \
			philo_bois->num_philo * 5 + 116 % 255, \
			philo_bois->elapsed_time, philo_bois->num_philo);
*/
