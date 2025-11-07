/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jay <jay@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:15:25 by jmanani           #+#    #+#             */
/*   Updated: 2025/11/07 01:44:17 by jay              ###   ########.fr       */
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

char	*read_file(int fd)
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

char	*join_data(char *data, char *buff)
{
	char	*temp;

	temp = data;
	data = ft_strjoin(data, buff);
	free(buff);
	free(temp);
	return (data);
}


char    *ft_read_data(int fd, char *data)
{
    char    *buff;
	
    if (!data)
        data = ft_strdup("");
    while (!ft_strchr(data, '\n'))
    {
        buff = read_file(fd);
        if (!buff)
        {
            if (*data)
                return (data);
            free(data);
            return (NULL);
        }
        data = join_data(data, buff);
        if (!data)
            return (NULL);
    }
    return (data);
}

char    *ft_extract_nl(char **data)
{
    char    *line;
    char    *nl;
    char    *temp;

    if (!(*data))
        return (NULL);
    nl = ft_strchr(*data, '\n');
    if (!nl)
        nl = ft_strchr(*data, '\0');
    line = ft_substr(*data, 0, nl - *data + 1);
    temp = *data;
    // *data = NULL;
    if (*(nl + 1) != '\0')
        *data = ft_strdup(nl + 1);
    free(temp);
    return (line);
}


char	*get_next_line(int fd)
{
	static char	*data;
	char		*line;
	data = NULL;
	if (fd < 0 && BUFFER_SIZE <= 0)
		return (NULL);
	data = ft_read_data(fd, data);
    if (data == NULL)
        return (NULL);
    line = ft_extract_nl(&data);
	 if (!line)
        free(data);
	return (line);
}

int	main(void)
{
	int		fd;
	char	*nl;

	fd = -1;
	fd = open("test.txt", O_RDONLY);
	printf("Our FD is: %d", fd);
	if (fd != -1)
		nl = get_next_line(fd);
	while (nl != NULL)
	{
		printf("%s", nl);
		free(nl);
		nl = get_next_line(fd);
	}
	// free(nl);
	close(fd);
	return (0);
}
