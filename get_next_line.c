/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanani <jmanani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:15:25 by jmanani           #+#    #+#             */
/*   Updated: 2025/11/06 20:09:33 by jmanani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*op;
	int			size_read;
	char		buff[BUFFER_SIZE + 1];
	char		*line;
	char		*temp;
	char		*nl_found;
	char		*eof;

	if (fd < 0 && BUFFER_SIZE <= 0)
		return (NULL);
	size_read = read(fd, buff, BUFFER_SIZE);
	if (size_read <= 0 && NULL == op)
		return (NULL);
	else if (size_read == 0 && *op){
		eof = ft_strchr(op, '\0');
		line = ft_substr(op, 0, eof - op - 1);
		free(op);
		op = NULL;
		return line;
	}
	if (!op)
		op = ft_strdup("");
	temp = op;
	op = ft_strjoin(op, buff);
	free(temp);
	nl_found = ft_strchr(op, '\n');
	while (!nl_found)
	{
		temp = op;
		size_read = read(fd, buff, BUFFER_SIZE);
		buff[size_read] = '\0';
		if (size_read <= 0)
			break ;
		op = ft_strjoin(op, buff);
		free(temp);
		nl_found = ft_strchr(op, '\n');
	}
	if (nl_found)
	{
		line = ft_substr(op, 0, nl_found - op + 1);
		temp = op;
		op = ft_strdup(++nl_found);
		free(temp);
	}
	else if (*op)
	{
		eof = ft_strchr(op, '\0');
		line = ft_substr(op, 0, eof - op + 1);
		free(op);
	}
	return (line);
}

int	main(void)
{
	int		fd;
	char	*nl;
	int		i;

	fd = -1;
	fd = open("test.txt", O_RDONLY);
	i = 0;
	printf("Our FD is: %d", fd);
	if (fd != -1)
		nl = get_next_line(fd);
	while (nl != NULL)
	{
		printf("%s", nl);
		free(nl);
		nl = get_next_line(fd);
	}
	free(nl);
	close(fd);
	return (0);
}
