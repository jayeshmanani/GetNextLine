/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanani <jmanani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:15:37 by jmanani           #+#    #+#             */
/*   Updated: 2025/11/06 17:25:23 by jmanani          ###   ########.fr       */
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