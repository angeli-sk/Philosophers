#include "philo.h"
#include <stdlib.h> /*malloc & free*/

static char	*ft_calc(int n, char *num, int len)
{
	int res;

	res = 0;
	while (n > 0)
	{
		res = n % 10;
		num[len - 1] = res + '0';
		n = n / 10;
		len--;
	}
	return (num);
}

static int	ft_num_len(int n, int *sign)
{
	int len;

	len = 0;
	if (n == -2147483648)
		return (11);
	if (n == 0)
		return (1);
	if (n < 0)
	{
		*sign = -1;
		n = n * -1;
		len++;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char		*ft_itoa(int n)
{
	char	*num;
	int		sign;
	int		len;

	sign = 1;
	len = ft_num_len(n, &sign);
	num = (char *)malloc(sizeof(*num) * len + 1);
	if (num == 0)
		return (0);
	if (n == 0)
		num[0] = '0';
	if (n == -2147483648)
	{
		num[0] = '-';
		num[1] = '2';
		n = 147483648;
	}
	if (sign < 0)
	{
		num[0] = '-';
		n = n * -1;
	}
	num[len] = '\0';
	num = ft_calc(n, num, len);
	return (num);
}

static void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)b;
	while (i < len)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

static void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*s;

	s = malloc(size * count);
	if (s == 0)
		return (0);
	ft_bzero(s, count);
	return (s);
}

static	int	ft_pn_check(int pn)
{
	if (pn == 1)
		return (-1);
	else
		return (0);
}

static	long int	checker(const char *s, long int r, int *m, int *pn)
{
	if (*s >= '0' && *s <= '9')
		r = (*s - '0') + (r * 10);
	else if (*s <= 32 && *s != '\e' && (r != 0 || *m == 1))
		return (-1);
	else if (*s == '-' && r == 0 && *m == 0)
	{
		*m = 1;
		*pn = -1;
	}
	else if (*s == '+' && r == 0 && *m == 0)
		*m = 1;
	else if (*s > 32 || *s == '\e')
		return (-1);
	return (r);
}

int	ft_atoi(const char *str)
{
	long int	result;
	long int	prev;
	int			m;
	int			pn;
	long int	check;

	result = 0;
	m = 0;
	pn = 1;
	check = 0;
	while (*str != '\0')
	{
		prev = result;
		check = checker(str, result, &m, &pn);
		if (check == -1)
			break ;
		else
			result = check;
		if (prev > result)
			return (ft_pn_check(pn));
		str++;
	}
	result = (int)result;
	return (result * pn);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*d;

	i = 0;
	s = (unsigned char *)src;
	d = (unsigned char *)dst;
	if (d == 0 && s == 0)
		return (0);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}
