#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <pthread.h>

typedef enum s_vibe
{
	ERROR =		-1,
	LEFT =		0,
	RIGHT =		1,
	DEATH =		2,
	SLEEP =		3,
	EAT =		5,
	THINK =		6,
	SUCCES =	0,
	EXIT =		-1
}	t_vibe;

typedef struct s_general
{
	int				num_of_philo;
	int				deathsies;
	int				breaksies;
	int				sleepsies;
	int				diet;
	int				full_philo_counter;
	// int				*colors;
	unsigned long	start_time;
	pthread_mutex_t	*fork;
	bool			alive;
	pthread_mutex_t	alive_check_lock;
	pthread_mutex_t	print;
}				t_general;

/*deathsies --> time_to_die*/
/*breaksies --> time_to_eat*/
/*sleepsies --> time_to_sleep*/
/*diet --> number_of_times_each_philosopher_must_eat*/

typedef struct s_philo_boi
{
	t_general		*data;
	pthread_mutex_t	**fork_lr;
	pthread_t		philo_id;
	pthread_t		death_thread_id;
	int				num_philo;
	int				times_it_has_eaten;
	unsigned long	time_last_ate;
	unsigned long	current_time;
	bool			alive_print;
}				t_philo_boi;

/*philo.c*/
int				vibe_check(t_philo_boi *philo_bois);

/*init.c*/
int				init(int argc, char **argv, t_philo_boi *philo_bois);

/*time.c*/
unsigned long	get_time(void);
void			*death_thread(void *boi);
void			isleepy(unsigned long ms);

/*libft_files.c*/
int				ft_atoi(const char *str);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_calloc(size_t count, size_t size);
char		*ft_itoa(int n);

/*print.c*/
void			print_start(t_philo_boi *philo_bois);
int				print_actions(t_philo_boi *philo_bois, int mood);

/*thread.c*/
void			*philo_thread(void *boi);
int	eating(t_philo_boi *philo_bois);
int	sleeping(t_philo_boi *philo_bois);
int	thinking(t_philo_boi *philo_bois);

#endif
