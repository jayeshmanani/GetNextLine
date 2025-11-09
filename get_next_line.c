/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jay <jay@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:15:25 by jmanani           #+#    #+#             */
/*   Updated: 2025/11/09 01:29:24 by jay              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	if (dest < src)
	{
		while (i++ < n)
			*(char *)dest++ = *(char *)src++;
		return ((void *)(dest - n));
	}
	else if (dest > src)
	{
		while (n--)
			((char *)dest)[n] = ((char *)src)[n];
	}
	return (dest);
}

char	*clean_return(char *line, char *buff)
{
	if (line)
		free(line);
	if (buff)
		*buff = '\0';
	return (NULL);
}

char	*create_line(char **line, char *buff, int size_read, int fd)
{
	char	*nl_found;

	nl_found = NULL;
	nl_found = ft_strchr(*line, '\n');
	while (nl_found == NULL && size_read > 0)
	{
		size_read = read(fd, buff, BUFFER_SIZE);
		if (size_read < 0)
			return (clean_return(*line, buff));
		buff[size_read] = '\0';
		*line = ft_strjoin(*line, buff);
		if (!*line)
			return (NULL);
		nl_found = ft_strchr(*line, '\n');
	}
	if ((size_read == 0) && **line == '\0' && *buff == '\0')
		return (clean_return(*line, buff));
	if (nl_found)
	{
		ft_memmove(buff, nl_found + 1, ft_strlen(nl_found + 1) + 1);
		*line = ft_substr(*line, 0, nl_found - *line + 1);
	}
	else
		*buff = '\0';
	return (*line);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*line;
	int			size_read;

	if ((fd < 0) || (BUFFER_SIZE <= 0))
		return (NULL);
	size_read = 1;
	line = ft_strjoin(NULL, buff);
	line = create_line(&line, buff, size_read, fd);
	if (!line)
		return (NULL);
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*nl;

// 	nl = NULL;
// 	fd = -1;
// 	fd = open("test.txt", O_RDONLY);
// 	printf("Our FD is: %d\n", fd);
// 	nl = get_next_line(fd);
// 	while (nl != NULL)
// 	{
// 		printf("%s", nl);
// 		free(nl);
// 		nl = get_next_line(fd);
// 	}
// 	free(nl);
// 	close(fd);
// 	return (0);
// }
