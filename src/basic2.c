/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edwin <edwin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 01:06:09 by jungyeok          #+#    #+#             */
/*   Updated: 2023/04/21 16:30:10 by edwin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inlcudes/minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ret;
	int		i;
	int		j;

	ret = ft_calloc(1, _strlen(s1) + _strlen(s2) + 1);
	i = 0;
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		ret[i + j] = s2[j];
		j++;
	}
	return (ret);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
		i++;
	}
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int	i;
	int	j;

	i = 0;
	if (needle[i] == 0)
		return ((char *)haystack);
	while (haystack[i] && len)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && len - j)
		{
			if (needle[j + 1] == '\0')
				return ((char *)&haystack[i]);
			j++;
		}
		i++;
		len--;
	}
	return (0);
}

char	*ft_strnstr_but_next(const char *haystack, const char *needle, size_t len)
{
	int	i;
	int	j;

	i = 0;
	if (needle[i] == 0)
		return ((char *)haystack);
	while (haystack[i] && len)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && len - j)
		{
			if (needle[j + 1] == '\0')
				return ((char *)&haystack[i + j + 1]);
			j++;
		}
		i++;
		len--;
	}
	return (0);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dest;
	unsigned char	*soruce;

	dest = dst;
	soruce = (unsigned char *)src;
	if (dest == soruce || len == 0)
		return (dest);
	if (dest > soruce && len)
	{
		dest += len - 1;
		soruce += len - 1;
		while (len--)
			*dest-- = *soruce--;
	}
	if (dest < soruce && len)
		while (len--)
			*dest++ = *soruce++;
	return (dst);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int	i;

	i = 0;
	while (src[i])
		i++;
	if (dstsize == 0)
		return (i);
	while (dstsize-- > 1 && *src)
		*dst++ = *src++;
	*dst = 0;
	return (i);
}