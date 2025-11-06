/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanani <jmanani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:15:25 by jmanani           #+#    #+#             */
/*   Updated: 2025/11/06 21:21:54 by jmanani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_str;
	size_t	str_len;
	size_t	actual_len;
	size_t	i;

	actual_len = len;
	i = 0;
	str_len = ft_strlen(s);
	actual_len = str_len - start;
	if (!*s || str_len < actual_len || start > str_len || len == 0
		|| actual_len == 0)
		return (ft_strdup(""));
	if (actual_len > len)
		actual_len = len;
	new_str = (char *)malloc(sizeof(char) * (actual_len + 1));
	if (!new_str)
		return (0);
	while (*(s + start) && i < actual_len)
		*new_str++ = *(s + start + (i++));
	*new_str = '\0';
	return (new_str - actual_len);
}

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (s[count] != '\0')
		count++;
	return (count);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*new_str;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!len)
		return (ft_strdup(""));
	new_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	while (*s1)
		*(new_str++) = *(s1++);
	while (*s2)
		*(new_str++) = *(s2++);
	*new_str = '\0';
	return (new_str - len);
}

char	*ft_strdup(const char *src)
{
	int		len;
	char	*dup;
	int		i;

	len = ft_strlen(src);
	dup = (char *)malloc(len + 1);
	if (!dup)
		return (0);
	i = -1;
	while (++i < len)
		dup[i] = src[i];
	dup[i] = '\0';
	return (dup);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s++ == (char)c)
			return ((char *)(s - 1));
	}
	if (*s == '\0' && (char)c != '\0')
		return (NULL);
	return ((char *)s);
}

char	*read_data(int fd)
{
	char	*buff;
	int		size_read;

	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	size_read = read(fd, buff, BUFFER_SIZE);
	if (size_read <= 0)
	{
		free(buff);
		return (NULL);
	}
	buff[size_read] = '\0';
	return (buff);
}

char	*create_new_str(char *op, char *buff, char c)
{
	char	*temp;
	char	*addr_found;

	temp = op;
	op = ft_strjoin(op, buff);
	free(buff);
	free(temp);
	return (op);
}

char	*get_next_line(int fd)
{
	static char	*op;
	int			size_read;
	char		*buff;
	char		*line;
	char		*temp;
	char		*nl_found;
	char		*eof;

	if (fd < 0 && BUFFER_SIZE <= 0)
		return (NULL);
	buff = read_data(fd);
	if (NULL == buff && NULL == op)
		return (NULL);
	else if (NULL == buff && *op)
	{
		temp = op;
		eof = ft_strchr(op, '\n');
		if (eof == NULL)
			eof = ft_strchr(op, '\0');
		line = ft_substr(op, 0, eof - op + 1);
		op = ft_strdup(++eof);
		if (*op == '\0')
		{
			free(op);
			op = NULL;
		}
		free(temp);
		return (line);
	}
	if (!op)
		op = ft_strdup("");
	op = create_new_str(op, buff, '\n');
	nl_found = ft_strchr(op, '\n');
	while (!nl_found)
	{
		buff = read_data(fd);
		if (NULL == buff)
			break ;
		op = create_new_str(op, buff, '\n');
		nl_found = ft_strchr(op, '\n');
	}
	if (nl_found)
	{
		temp = op;
		line = ft_substr(op, 0, nl_found - op + 1);
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
