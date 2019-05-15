/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvandamm <pvandamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 15:10:20 by pvandamm          #+#    #+#             */
/*   Updated: 2018/11/13 16:55:52 by pvandamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_check(char **cpy, char **line, char **buf)
{
	char	*tmp;

	if (!(*buf = ft_strdup(ft_strchr(*cpy, '\n') + 1)))
		return (-1);
	if (!(tmp = ft_strdup(*line)))
		return (-1);
	free(*line);
	if (!(*line = ft_strsub(tmp, 0, ft_strchr(tmp, '\n') - tmp)))
		return (-1);
	free(*cpy);
	free(tmp);
	return (0);
}

static int	ft_read(int fd, char **line, char **buf, int *byt)
{
	char	*tmp;
	char	*cpy;

	if (!(cpy = ft_strnew(BUFF_SIZE)))
		return (-1);
	while ((*byt = read(fd, cpy, BUFF_SIZE)))
	{
		if (*byt == -1)
			return (-1);
		cpy[*byt] = '\0';
		if (!(tmp = ft_strdup(*line)))
			return (-1);
		free(*line);
		if (!(*line = ft_strjoin(tmp, cpy)))
			return (-1);
		free(tmp);
		if (ft_strchr(cpy, '\n'))
		{
			if ((ft_check(&cpy, &(*line), &(*buf))) == -1)
				return (-1);
			break ;
		}
	}
	return (*byt == 0 ? 0 : 1);
}

int			get_next_line(const int fd, char **line)
{
	static char	*buf;
	int			byt;

	if (!line || fd < 0 || BUFF_SIZE < 1)
		return (-1);
	if (!(*line = ft_strnew(0)))
		return (-1);
	byt = 0;
	if (buf)
	{
		if (ft_strchr(buf, '\n'))
		{
			if (!(*line = ft_strsub(buf, 0, ft_strchr(buf, '\n') - buf)))
				return (-1);
			buf = ft_strchr(buf, '\n') + 1;
			return (1);
		}
		if (!(*line = ft_strdup(buf)))
			return (-1);
		buf = NULL;
	}
	if (ft_read(fd, &(*line), &buf, &byt) == -1)
		return (-1);
	return (byt < 1 && !ft_strlen(*line) ? byt : 1);
}
