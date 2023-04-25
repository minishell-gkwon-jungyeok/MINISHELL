#include "../includes/minishell.h"

/*
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct s_command{
	bool	builtin;
	char	**program;
	char	*input;
	char	*output;
	char	*delimiter;
	char	*output_append;
}t_command;
*/

void	_printf(t_command *c){
	char *boool;
	if (c->built_in)
		boool = "true\0";
	else
		boool = "false\0";
	printf("builtn = %s\n", boool);
	for (int i = 0; c->program[i]; i++)
		printf("progrm[%d] = %s\n", i, c->program[i]);
	printf("input  = %s\n", c->input);
	printf("output = %s\n", c->output);
	printf("delimi = %s\n", c->delimiter);
	printf("outapd = %s\n", c->output_append);
}

char	*_strdup(char *s){
	int size = 0;
	while (s[size] && s[size] != ' ')
		size++;
	char *ret = calloc(1, size + 1);
	for (int i = 0; s[i] && s[i] != ' '; i++)
		ret[i] = s[i];
	return (ret);
}

void	rem_s(char **inn, char *s){
	char *in = *inn;
	int s_len = strlen(s);
	int	size = strlen(in) - s_len - 2;
	int	i;
	for (i = 0; in[i]; i++){
		if (in[i] == s[0])
			break;
	}
	if (s_len == 2)
		i++;
	i+= 2;
	int j = 0;
	while (in[i + j]){
		if (in[i + j] == ' ')
			break ;
		j++;
	}

	size -= j;

	int	k = 0;
	int flag = 1;
	char *ret = calloc(1, size + 1);
//	printf("in in rem_s = %s\n", in);
	for (i = 0; in[i]; i++){
		if (in[i] == s[0] && s_len == 1 && flag){
			i += 3 + j;
			flag = 0;
		}
		else if (in[i] == s[0] && s_len == 2 && flag){
			i += 4 + j;
			flag = 0;
		}
		ret[k] = in[i];
		k++;
	}

//	free(in);
	*inn = ret;
}

char	**_split(char *s, char c){
	int size = 0;
	for (int i = 0; s[i]; i++)
		if (s[i] == c)
			size++;

	char **ret = calloc(8, size + 2);

	int	j;
	int	k = 0;
	for (int i = 0; s[i] && s[i] != '|'; i++){
		if (s[i] != c){
			for (j = 0; s[i + j] && s[i + j] != c; j++);
			ret[k] = _strdup(s + i);
			i += j;
			k++;
		}
	}
	return (ret);
}

char	*_strchr(char *s, int d){
	char c = (char)d;
	for (int i = 0; s[i] && s[i] != '|'; i++)
		if (s[i] == c)
			return (s + i);
	return (NULL);
}

int main(int i, char **av, char **envp){
	if (i == 1 || i > 2)
		return (1);

	int npipe = 0;
	for (i = 0; av[1][i]; i++)
		if (av[1][i] == '|')
			npipe++;
	
	t_command *c;

	c = calloc(sizeof(t_command), npipe + 2);

	char    *in = strdup(av[1]);

	int ether = npipe;
	for (int ii = 0; ii <= npipe; ii++){

//		printf("\nin at start c[%d] = \"%s\"\n", ii, in);
		char	*dl = _strchr(in, 60);
		char	*dr = _strchr(in, 62);

		if (dl && dl[1] == 60)
		{
			for (i = 2; dl[i] == ' '; i++);
			c[ii].delimiter = _strdup(dl + i);
			rem_s(&in, "<<\0");
		}
		else if (dl)
		{
			for (i = 1; dl[i] == ' '; i++);
			c[ii].input = _strdup(dl + i);
			rem_s(&in, "<\0");
		}
		if (dr && dr[1] == 62)
		{
			for (i = 2; dr[i] == ' '; i++);
			c[ii].output_append = _strdup(dr + i);
			rem_s(&in, ">>\0");
		}
		else if (dr)
		{
			for (i = 1; dr[i] == ' '; i++);
			c[ii].output = _strdup(dr + i);
			rem_s(&in, ">\0");
		}
		
		c[ii].program = _split(in, ' ');
	
		if (!strcmp(c[ii].program[0], "echo\0") ||
				!strcmp(c[ii].program[0], "cd\0") ||
				!strcmp(c[ii].program[0], "pwd\0") ||
				!strcmp(c[ii].program[0], "export\0") ||
				!strcmp(c[ii].program[0], "unset\0") ||
				!strcmp(c[ii].program[0], "env\0") ||
				!strcmp(c[ii].program[0], "exit\0"))
			c[ii].built_in = true;

//		_printf(c + ii);

//		printf("in after _printf = %s\n", in);
		
		if (ether){
			int	jj;
			for (jj = 0; in[jj]; jj++)
				if (in[jj] == '|')
					break ;
			in += jj + 2;
			ether--;
//			printf("in at final = %s\n", in);
		}
	}
		
	_jungyeok(&c, envp);

//	printf("in at final = %s\n", in);
	for (int j = 0; j <= npipe; j++){
		for (i = 0; c[j].program[i]; i++)
			free(c[j].program[i]);
		free(c[j].program);
		if (c[j].input)
			free(c[j].input);
		if (c[j].output)
			free(c[j].output);
		if (c[j].delimiter)
			free(c[j].delimiter);
		if (c[j].output_append)
			free(c[j].output_append);
	}
	free(c);

//	system("leaks minishell");
}
