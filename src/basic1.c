/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edwin <edwin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 00:31:22 by jungyeok          #+#    #+#             */
/*   Updated: 2023/05/09 13:16:44 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (s)
		while (s[i])
			i++;
	return (i);
}

void	*ft_memset(void *b, int c, int len)
{
	unsigned char	*ret;
	int				i;

	i = 0;
	ret = b;
	while (i < len)
	{
		ret[i] = (unsigned char)c;
		i++;
	}
	return (ret);
}

void	ft_err(char *s)
{
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	exit(1);
}

void	*ft_calloc(int count, int size)
{
	unsigned char	*ret;
	int				n;

	n = count * size;
	if (!n)
		n = 1;
	ret = malloc(n);
	if (!ret)
		ft_err("Error : Memory Allocation Failed");
	ft_memset(ret, 0, n);
	return (ret);
}

char	*ft_strdup(char *s)
{
	int		i;
	int		size;
	char	*ret;

	size = ft_strlen(s);
	ret = ft_calloc(1, size + 1);
	i = 0;
	while (i < size)
	{
		ret[i] = s[i];
		i++;
	}
	return (ret);
}
