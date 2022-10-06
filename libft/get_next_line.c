/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchet <abouchet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 13:06:19 by abouchet          #+#    #+#             */
/*   Updated: 2022/03/20 08:37:43 by abouchet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	buf_init(char *buf, int fd)
{
	int	r;

	r = ft_strlen_gnl(buf);
	if (buf[0] == '\0')
	{
		r = read(fd, buf, BUFFER_SIZE);
		buf[r] = 0;
	}
	return (r);
}

static int	breakline(char *buf, int r)
{
	int	r_bline;

	r_bline = 0;
	while (r_bline < r)
	{
		if (buf[r_bline] == '\n' || buf[r_bline] == 0)
			return (r_bline);
		r_bline++;
	}
	return (r_bline);
}

static char	*buf_join_str(char *str, char *buf, int r_bline)
{
	char	*temp;

	temp = ft_substr_gnl(buf, 0, r_bline + 1);
	str = ft_strjoin_gnl(str, temp);
	free(temp);
	return (str);
}

static void	mv_char_buf(char *buf, unsigned int index)
{
	int	i;

	i = 0;
	while (buf[index + i])
	{
		buf[i] = buf[index + i];
		i++;
	}
	while (i < BUFFER_SIZE)
	{
		buf[i] = '\0';
		i++;
	}
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1] = {};
	int			r;
	int			r_bline;
	char		*str;

	if (fd < 0)
		return (NULL);
	r = buf_init(buf, fd);
	if (r <= 0)
		return (NULL);
	r_bline = breakline(buf, r);
	str = NULL;
	while (r_bline == r)
	{
		str = ft_strjoin_gnl(str, buf);
		r = read(fd, buf, BUFFER_SIZE);
		buf[r] = 0;
		if (r <= 0)
			return (str);
		r_bline = breakline(buf, r);
	}
	str = buf_join_str(str, buf, r_bline);
	mv_char_buf(buf, r_bline + 1);
	return (str);
}
