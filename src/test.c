#include "./ft_split.c"
#include <stdio.h>
#include <stdlib.h>

//static int	total_len(char const *str, char c)
//{
//	int	i;
//	int	count;
//	char quote;

//	count = 0;
//	i = 0;
//	while (str[i])
//	{
//		if (str[i] == '\"' || str[i] == '\'')
//		{
//			quote = str[i++];
//			while (str[i] != quote)
//				i++;
//			count++;
//		}
//		while (str[i] && str[i] == c)
//			i++;
//		if (str[i])
//			count++;
//		while (str[i] && str[i] != c)
//			i++;
//	}
//	return (count);
//}

//static char	*get_word(char const *str, int len)
//{
//	char	*ret;
//	int		i;

//	i = 0;
//	ret = (char *)malloc(sizeof(char) * (len + 1));
//	if (!ret)
//		return (NULL);
//	while (i < len)
//	{
//		ret[i] = str[i];
//		i++;
//	}
//	ret[i] = 0;
//	return (ret);
//}

//static int	word_count(char const *str, char c)
//{
//	int	len;
//	char quote;

//	len = 0;
//	while (str[len])
//	{
//		if (str[len] == '\"' || str[len] == '\'')
//		{
//			quote = str[len++];
//			while (str[len] != quote)
//				len++;
//		}
//		if (str[len] != c)
//		len++;
//	}
//	return (len);
//}

//static char	**ft_split_free(char **ret, int i)
//{
//	while (i)
//		free(ret[--i]);
//	free(ret);
//	return (0);
//}

//char	**ft_split(char const *s, char c)
//{
//	int		t_len;
//	char	**ret;
//	int		i;
//	int		count;

//	i = 0;
//	t_len = total_len(s, c);
//	ret = (char **)malloc(sizeof(char *) * (t_len + 1));
//	if (!ret)
//		return (0);
//	ret[t_len] = 0;
//	while (*s && i < t_len)
//	{
//		while (*s && *s == c)
//			s++;
//		if (*s)
//		{
//			count = word_count(s, c);
//			ret[i] = get_word(s, count);
//			if (!ret[i++])
//				return (ft_split_free(ret, i));
//			s += count;
//		}
//	}
//	return (ret);
//}


int main()
{
	char **ret;
	char *line = "'ls'' -al'";
	int i;

	i = 0;
	ret = ft_split(line, ' ');
	while (i < 2)
	{
		printf("[%d] is %s\n", i, ret[i]);
		i++;
	}
}