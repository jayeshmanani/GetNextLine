/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jay <jay@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:15:37 by jmanani           #+#    #+#             */
/*   Updated: 2025/11/08 02:34:06 by jay              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*new_str;
	size_t	str_len;
	size_t	actual_len;
	size_t	i;

	actual_len = len;
	i = 0;
	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	if (start >= str_len)
		return (free(s), ft_strdup(""));
	actual_len = str_len - start;
	if (actual_len > len)
		actual_len = len;
	new_str = (char *)malloc(sizeof(char) * (actual_len + 1));
	if (!new_str)
		return (free(s), NULL);
	while (*(s + start) && i < actual_len)
		*new_str++ = *(s + start + (i++));
	*new_str = '\0';
	free(s);
	return (new_str - actual_len);
}

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	if (!s)
		return (count);
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
	if (!s2)
		return (s1);
	len = ft_strlen(s1) + ft_strlen(s2);
	new_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (free(temp), NULL);
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

	if (!src)
		return (NULL);
	len = ft_strlen(src);
	dup = (char *)malloc(len + 1);
	if (!dup)
		return (NULL);
	i = -1;
	while (++i < len)
		dup[i] = src[i];
	dup[i] = '\0';
	return (dup);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s != '\0')
	{
		if (*s++ == (char)c)
			return ((char *)(s - 1));
	}
	if (*s == '\0' && (char)c != '\0')
		return (NULL);
	return ((char *)s);
}
