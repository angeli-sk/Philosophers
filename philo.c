#include "philo.h"
#include <stdio.h> /*printf*/
#include <stdlib.h> /*malloc & free*/
#include <unistd.h> /*usleep*/

int	vibe_check(t_philo_boi *philo_bois)
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

static void	my_exit(t_philo_boi *philo_bois)
{
	int	i;

	i = 0;
	while (i < philo_bois->data->num_of_philo)
	{
		pthread_mutex_destroy(&philo_bois->data->fork[i]);
		free (philo_bois[i].fork_lr);
		i++;
	}
	pthread_mutex_destroy(&(philo_bois->data->alive_check_lock));
	pthread_mutex_destroy(&(philo_bois->data->print));
	free (philo_bois->data->fork);
	// free (philo_bois->data->colors);
	free (philo_bois->data);
	free (philo_bois);
}

static int	input_checker(int argc, char **argv)
{
	if (!(argc == 5 || argc == 6) || ft_atoi(argv[1]) < 1 || ft_atoi(argv[2]) \
		< 1 || ft_atoi(argv[4]) < 1 || ft_atoi(argv[3]) < 1 || (argc == 6 \
			&& ft_atoi(argv[5]) < 1))
	{
		printf("Use 4 or 5 arguments:\n1.number_of_philosophers\n");
		printf("2.time_to_die\n3.time_to_eat\n4.time_to_sleep\n");
		printf("5.number_of_times_each_philosopher_must_eat\n");
		return (ERROR);
	}
	return (0);
}

static int	philo(t_philo_boi	*philo_bois)
{
	int	i;

	i = 0;
	philo_bois->data->start_time = get_time();
	while (i < philo_bois->data->num_of_philo)
	{
		if (pthread_create(&philo_bois[i].philo_id, NULL, \
			&philo_thread, &philo_bois[i]))
			return (ERROR);
		i++;
	}
	i = 0;
	while (i < philo_bois->data->num_of_philo)
	{
		if (pthread_join(philo_bois[i].philo_id, NULL))
			return (ERROR);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo_boi	*philo_bois;

	if (input_checker(argc, argv) == ERROR)
		return (ERROR);
	philo_bois = malloc (sizeof(t_philo_boi) * ft_atoi(argv[1]));
	if (init(argc, argv, philo_bois) == ERROR)
		return (ERROR);
	print_start(philo_bois);
	if (philo(philo_bois) == ERROR)
		return (ERROR);
	printf("╚═════════════  💀  ═════════════╝");
	my_exit(philo_bois);
	return (0);
}
