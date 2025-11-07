/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanani <jmanani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:15:25 by jmanani           #+#    #+#             */
/*   Updated: 2025/11/07 19:41:49 by jmanani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// char	*ft_substr(char *s, unsigned int start, size_t len)
// {
// 	char	*res;
// 	size_t	i;
// 	size_t	s_len;

// 	if (!s)
// 		return (NULL);
// 	s_len = ft_strlen(s);
// 	if (start >= s_len)
// 		return (free(s), ft_strdup(""));
// 	if (len > s_len - start)
// 		len = s_len - start;
// 	res = (char *)malloc(len + 1);
// 	if (!res)
// 		return (free(s), NULL);
// 	i = 0;
// 	while (i < len && s[start + i])
// 	{
// 		res[i] = s[start + i];
// 		i++;
// 	}
// 	res[i] = '\0';
// 	free(s);
// 	return (res);
// }

// size_t	ft_strlen(const char *s)
// {
// 	size_t	count;

// 	count = 0;
// 	if (!s)
// 		return (count);
// 	while (s[count] != '\0')
// 		count++;
// 	return (count);
// }

// char	*ft_strjoin(char *s1, char const *s2)
// {
// 	int		len;
// 	char	*new_str;
// 	char	*temp;

// 	temp = s1;
// 	if (!s1 && !s2)
// 		return (NULL);
// 	if (!s1)
// 		return (ft_strdup(s2));
// 	if (!s2)
// 		return (s1);
// 	len = ft_strlen(s1) + ft_strlen(s2);
// 	new_str = (char *)malloc(sizeof(char) * (len + 1));
// 	if (!new_str)
// 		return (free(temp), NULL);
// 	while (*s1 != '\0')
// 		*(new_str++) = *(s1++);
// 	while (*s2 != '\0')
// 		*(new_str++) = *(s2++);
// 	*new_str = '\0';
// 	free(temp);
// 	return (new_str - len);
// }

// char	*ft_strdup(const char *src)
// {
// 	int		len;
// 	char	*dup;
// 	int		i;

// 	if (!src)
// 		return (NULL);
// 	len = ft_strlen(src);
// 	dup = (char *)malloc(len + 1);
// 	if (!dup)
// 		return (NULL);
// 	i = -1;
// 	while (++i < len)
// 		dup[i] = src[i];
// 	dup[i] = '\0';
// 	return (dup);
// }

// char	*ft_strchr(const char *s, int c)
// {
// 	if (!s)
// 		return (NULL);
// 	while (*s)
// 	{
// 		if (*s == (char)c)
// 			return ((char *)(s));
// 		s++;
// 	}
// 	if (*s == '\0' && (char)c != '\0')
// 		return (NULL);
// 	return ((char *)s);
// }

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
	return (dest + 1);
}

void	update_buffer(char *buff)
{
	char	*ptr;

	ptr = ft_strchr(buff, '\n');
	if (ptr && *(ptr + 1))
		ft_memmove(buff, ptr + 1, ft_strlen(ptr + 1) + 1);
	else
		*buff = '\0';
}

char	*clean_return(char *line, char *buff)
{
	if (line)
		free(line);
	if (buff)
		*buff = '\0';
	return (NULL);
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
			return (clean_return(line, buff));
		buff[size_read] = '\0';
		line = ft_strjoin(line, buff);
		if (!line)
			return (NULL);
	}
	if (size_read == 0 && *line == '\0')
		return (free(line), NULL);
	if (ft_strchr(line, '\n'))
		line = ft_substr(line, 0, ft_strchr(line, '\n') - line + 1);
	update_buffer(buff);
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
// 	// printf("FD Close and starting again\n");
// 	// fd = open("test.txt", O_RDONLY);
// 	// printf("Our FD is: %d\n", fd);
// 	// nl = get_next_line(fd);
// 	// while (nl != NULL)
// 	// {
// 	// 	printf("%s", nl);
// 	// 	free(nl);
// 	// 	nl = get_next_line(fd);
// 	// 	break ;
// 	// }
// 	// free(nl);
// 	// close(fd);
// 	return (0);
// }
