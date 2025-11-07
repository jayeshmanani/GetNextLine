/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanani <jmanani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:15:25 by jmanani           #+#    #+#             */
/*   Updated: 2025/11/07 17:46:19 by jmanani          ###   ########.fr       */
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

char	*ft_strjoin(char *s1, char const *s2)
{
	int		len;
	char	*new_str;
	char	*temp;

	temp = s1;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2 || !*s2)
		return (s1);
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!len)
		return (NULL);
	new_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	while (*s1 != '\0')
		*(new_str++) = *(s1++);
	while (*s2 != '\0')
		*(new_str++) = *(s2++);
	*new_str = '\0';
	free(temp);
	return (new_str - len);
}

char	*ft_strdup(const char *src)
{
	int		len;
	char	*dup;
	int		i;

	len = ft_strlen(src);
	// if(len == 0)
	// 	return (NULL);
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

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest == 0 && src == 0)
		return (NULL);
	if (dest <= src)
	{
		while (i++ < n)
			*(char *)dest++ = *(char *)src++;
		return ((void *)(dest - n));
	}
	else if (dest > src)
	{
		dest += n - 1;
		src += n - 1;
		while (i++ < n)
			*(char *)dest-- = *(char *)src--;
	}
	return (dest + 1);
}

void	update_buffer(char *buff)
{
	char	*ptr;

	ptr = ft_strchr(buff, '\n');
	if (ptr && *(ptr + 1))
		ft_memmove(buff, ptr, ft_strlen(ptr));
	else
		*buff = '\0';
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
	while (ft_strchr(line, '\n') == NULL && size_read > 0)
	{
		size_read = read(fd, buff, BUFFER_SIZE);
		if (size_read < 0)
			return (free(line), (NULL));
		buff[size_read] = '\0';
		line = ft_strjoin(line, buff);
		if (!line || !*line)
			return (free(line), NULL);
	}
	if (size_read == 0 && *line == '\0')
		return (free(line), NULL);
	if (ft_strchr(line, '\n'))
		line = ft_substr(line, 0, ft_strchr(line, '\n') - line + 1);
	update_buffer(buff);
	return (line);
}

int	main(void)
{
	int		fd;
	char	*nl;

	nl = NULL;
	fd = -1;
	fd = open("test.txt", O_RDONLY);
	printf("Our FD is: %d\n", fd);
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
