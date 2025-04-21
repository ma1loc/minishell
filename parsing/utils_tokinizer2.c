#include "tokenizer.h"
#include "../srcs/mini_shell.h"

t_token *add_token( t_token **head, char *value, t_token_type type, int quotes_type)
{
  t_token *new_token;
  t_token *current;

  new_token = malloc(sizeof(t_token));
  if(!new_token)
    return(NULL);
  new_token->value = strdup(value);  // copy the value
  new_token->type = type;
  new_token->next = NULL;
  new_token->quotes_info = malloc(sizeof(t_quotes_info));
  if(!new_token->quotes_info)
    return(free(new_token->value),free(new_token),NULL);
  new_token->quotes_info->quotes_type = quotes_type;
  if(*head == NULL)      // if list empty make this token the first in the list
  {
   *head = new_token;
   return(new_token);
  }
  current = *head;
  while(current->next != NULL)
  {
    current = current->next;
  }
  current->next = new_token;
  return(new_token);
}

void	process_quote_char(t_process_data *data, t_quotes_info *info)
{
	static int	in_dquote;
	static int	in_squote;

	if (data->str[data->i] == '"' && in_squote == 0)
	{
		if (in_dquote == 0)
		{
			in_dquote = 1;
			info->quotes_type = 2;
		}
		else
			in_dquote = 0;
	}
	else if (data->str[data->i] == '\'' && in_dquote == 0)
	{
		if (in_squote == 0)
		{
			in_squote = 1;
			info->quotes_type = 1;
		}
		else
			in_squote = 0;
	}
	else
		data->result[(data->j)++] = data->str[data->i];
	(data->i)++;
}

t_quotes_info check_just_quotes(t_process_data *data, t_quotes_info info, int len)
{

	if (data->j == 0 && len > 0)
		return(info);
	return(info);
}

t_quotes_info	strip_quotes(char *str)
{
	t_quotes_info	info;
	t_process_data	data;
	int				len;

	info.quotes_type = 0;
	len = strlen(str);
	data.result = malloc(len + 1);
	if (!data.result)
	{
		info.stripped_text = NULL;
		return (info);
	}
	data.str = str;
	data.i = 0;
	data.j = 0;
	while (data.i < len)
		process_quote_char(&data, &info);
	data.result[data.j] = '\0';
	info.stripped_text = data.result;
	check_just_quotes(&data,info,len);
	if (data.j == 0 && len == 0)
	{
		free(data.result);
		info.stripped_text = NULL;
	}
	return (info);
}
