#include "philo.h"
#include <stdlib.h> /*malloc & free*/
#include <stdbool.h> /*bool true/false*/

static void	init_assign_forks(t_philo_boi *philo_bois, \
	t_general *data_struct, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		if (i == 0)
			philo_bois[i].fork_lr[LEFT] = &data_struct->fork[num - 1];
		else
			philo_bois[i].fork_lr[LEFT] = &data_struct->fork[i - 1];
		philo_bois[i].fork_lr[RIGHT] = &data_struct->fork[i];
		i++;
	}
}

static int	init_loop(t_philo_boi *philo_bois, t_general *data_struct, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		philo_bois[i].data = data_struct;
		philo_bois[i].fork_lr = malloc (sizeof(pthread_mutex_t *) * 2);
		if (!philo_bois[i].fork_lr)
		{
			free (philo_bois[i].fork_lr);
			return (ERROR);
		}
		philo_bois[i].num_philo = i;
		if (pthread_mutex_init(&data_struct->fork[i], NULL))
			return (ERROR);
		philo_bois[i].current_time = 0;
		philo_bois[i].times_it_has_eaten = 0;
		philo_bois[i].time_last_ate = 0;
		philo_bois[i].alive_print = true;
		i++;
	}

	init_assign_forks(philo_bois, data_struct, num);
	return (0);
}

static void	init_general_data_struct(int argc, char **argv, \
	t_general *data_struct, int num)
{
	// int i;

	// i = 0;
	data_struct->num_of_philo = num;
	data_struct->deathsies = ft_atoi(argv[2]);
	data_struct->breaksies = ft_atoi(argv[3]);
	data_struct->sleepsies = ft_atoi(argv[4]);
	if (argc == 6)
		data_struct->diet = ft_atoi(argv[5]);
	else
		data_struct->diet = 0;
	data_struct->alive = true;
	data_struct->full_philo_counter = 0;
	data_struct->start_time = 0;
	// data_struct->colors = malloc(sizeof (int) * num);
	// while (i < num)
	// {
	// 	data_struct->colors[i] = i * 5 + 116 % 232;
	// 	i++;
	// }
}

static int	init_mutexes(t_philo_boi *philo_bois, t_general	*data_struct,
	int	num)
{
	if (pthread_mutex_init(&data_struct->alive_check_lock, NULL))
		return (ERROR);
	if (pthread_mutex_init(&data_struct->print, NULL))
		return (ERROR);
	if (init_loop(philo_bois, data_struct, num) == ERROR)
		return (ERROR);
	return (0);
}

int	init(int argc, char **argv, t_philo_boi *philo_bois)
{
	int				num;
	t_general		*data_struct;
	pthread_mutex_t	*forks;

	num = ft_atoi(argv[1]);
	data_struct = malloc(sizeof(t_general));
	forks = malloc(sizeof(pthread_mutex_t) * num);
	if (!data_struct || !forks || !philo_bois)
	{
		free(data_struct);
		free (forks);
		free (philo_bois);
		return (ERROR);
	}
	init_general_data_struct(argc, argv, data_struct, num);
	data_struct->fork = forks;
	if (init_mutexes(philo_bois, data_struct, num) == ERROR)
		return (ERROR);
	return (0);
}
