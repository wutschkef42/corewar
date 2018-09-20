/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwutschk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 21:30:51 by fwutschk          #+#    #+#             */
/*   Updated: 2017/12/23 16:22:56 by wutschkef        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

static t_feed	*get_feed(t_feed *first, int fd)
{
	t_feed	*feed;

	feed = first;
	while (feed && feed->fd != fd)
		feed = feed->next;
	if (!feed)
	{
		if (!(feed = malloc(sizeof(t_feed))) ||
			!(feed->store = ft_strnew(0)))
			return (0);
		feed->fd = fd;
		feed->next = NULL;
		while (first && first->next)
			first = first->next;
		if (first)
			first->next = feed;
	}
	return (feed);
}

static int		process_feed(t_feed *feed, char **line)
{
	char	*tmp;
	char	*new;

	if (!(tmp = ft_strdup(feed->store)))
		return (-1);
	free(feed->store);
	if (*tmp == '\n')
	{
		if (!(feed->store = ft_strdup(tmp + 1)) ||
			!(*line = ft_strnew(0)))
			return (-1);
		free(tmp);
		return (1);
	}
	if (!(feed->store = ft_strchr(tmp, '\n') ?
		ft_strdup(ft_strchr(tmp, '\n') + 1) : ft_strnew(0)))
		return (-1);
	if (ft_strchr(tmp, '\n'))
		*ft_strchr(tmp, '\n') = '\0';
	if (!(new = *tmp ? tmp : ft_strnew(0)))
		return (-1);
	*line = new;
	if (new != tmp)
		free(tmp);
	return (*new ? 1 : 0);
}

int				get_next_line(const int fd, char **line)
{
	static t_feed	*first;
	t_feed			*feed;
	int				nread;
	char			buff[BUFF_SIZE + 1];
	char			*tmp;

	if (!line || !(feed = get_feed(first, fd)))
		return (-1);
	first = first ? first : feed;
	while ((nread = read(fd, buff, BUFF_SIZE)) && nread != -1)
	{
		buff[nread] = '\0';
		tmp = ft_strjoin(feed->store, buff);
		free(feed->store);
		feed->store = tmp;
		if (ft_strchr(feed->store, '\n'))
			return (process_feed(feed, line));
	}
	return (nread == -1 ? -1 : process_feed(feed, line));
}
