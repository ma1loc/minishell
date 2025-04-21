#include "tokenizer.h"
#include "../srcs/mini_shell.h"

int check_syntax(char *input, int len, int *i)
{
	// int j;

	// j = 0;
	if (check_pipes(input, len, i))
		return (1);
	if (check_redirections(input, len, i))
		return (1);
	if (check_original_cases(input, len, i))
		return (1);
	return (0);
}

void check_unclosed_quotes(t_setup *setup, int *i, int *in_quotes, char *quotes_char)
{
	if ((setup->input[*i] == '"' || setup->input[*i] == '\'') &&
		(*quotes_char == setup->input[*i] || *in_quotes == 0))
	{
		if (!*in_quotes)
		{
			*in_quotes = 1;
			*quotes_char = setup->input[*i];
		}
		else
		{
			*in_quotes = 0;
			*quotes_char = 0;
		}
	}
}

int handle_syntax_error(t_setup *setup, int in_quotes)
{
	if (in_quotes)
	{
		ft_perror(setup, "syntax error near unexpected token\n", SYNTAX_ERROR);
		return (1);
	}
	return (0);
}

int check_original_cases(char *input, int len, int *i)
{
	if (input[len - 1] == '<' && input[len - 2] == '<')
		return (1);
	else if (input[0] == '<' && input[1] == '\0')
		return (1);
	else if (input[0] == '>' && input[1] == '>' && input[2] == '\0')
		return (1);
	else if (input[len - 1] == '>')
		return (1);
	else if (input[*i] == '>' && input[*i + 1] == '<')
		return (1);
	else if (input[0] == '<' && input[1] == '<' && input[2] == '<' && input[3] == '<')
		return (1);
	else if (input[0] == '>' && input[1] == '>' && input[3] == '>')
		return (1);
	else if (input[0] == '<' && input[1] == '<' && input[2] == '\0')
		return (1);
	return (0);
}
