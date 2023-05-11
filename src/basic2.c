/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 01:06:09 by jungyeok          #+#    #+#             */
/*   Updated: 2023/05/11 16:49:10 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ret;
	int		i;
	int		j;

	ret = ft_calloc(1, ft_strlen(s1) + ft_strlen(s2) + 1);
	i = 0;
	while (s1 && s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		ret[i + j] = s2[j];
		j++;
	}
	free(s1);
	free(s2);
	return (ret);
}

bool	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (!s1)
		return (0);
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

// which is very different with standard strnstr;

int	ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int	i;
	int	j;

	i = 0;
	if (needle[i] == 0)
		return (-1);
	while (haystack[i] && len)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && len - j)
		{
			if (needle[j + 1] == '\0')
				return (i);
			j++;
		}
		i++;
		len--;
	}
	return (-1);
}

void	*ft_memmove(void *dst, void *src, size_t len)
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
