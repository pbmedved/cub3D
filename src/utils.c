/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iadrien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 10:52:42 by iadrien           #+#    #+#             */
/*   Updated: 2020/10/17 13:18:17 by iadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char			*ft_strdup(const char *str)
{
	char		*dup;
	size_t		size;
	size_t		i;
	size_t		d;

	i = ft_strlen(str);
	size = i + 1;
	d = 0;
	if (!(dup = malloc(sizeof(char) * size)))
		error_exit("malloc error");
	while (size > 1 && *str != '\0')
	{
		dup[d] = *str++;
		d++;
		size--;
	}
	if (size)
		dup[d] = '\0';
	return (dup);
}

char			*ft_strdup_size(const char *str, size_t size)
{
	char		*dup;
	size_t		i;
	size_t		d;

	i = ft_strlen(str);
	d = 0;
	if (!(dup = malloc(sizeof(char) * size)))
		error_exit("malloc error");
	while (*str != '\0' && size > 1)
	{
		dup[d] = *str++;
		d++;
		size--;
	}
	if (size)
	{
		dup[d] = '\0';
		d++;
		size--;
	}
	return (dup);
}

int				get_next_line(char **line, int fd, int i)
{
	char		*store;
	char		buff;
	int			bytes;

	if (!line || !(store = malloc(10000)))
		error_exit("gnl error");
	while ((bytes = read(fd, &buff, 1)))
	{
		if (bytes < 0)
			error_exit("gnl read error");
		if (ft_strchr("\n\0", buff))
		{
			*line = i ? ft_strdup(store) : ft_strdup("");
			free(store);
			store = NULL;
			return (1);
		}
		store[i++] = buff;
		store[i] = '\0';
	}
	store[0] = i ? store[0] : 0;
	*line = ft_strdup(store);
	free(store);
	return (0);
}

int				ft_simple_atoi(char *store)
{
	long		n;

	n = 0;
	while (*store < '0' || *store > '9')
		store++;
	while (*store >= '0' && *store <= '9' && n < 9999)
	{
		n = n * 10 + (*store - '0');
		store++;
	}
	return ((int)n);
}
