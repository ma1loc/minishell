#include "../srcs/mini_shell.h"
#include "tokenizer.h"

// // insert a new token at a specified position in the token list // fucn i use first and push it
// t_token	*insert_new_token(t_insert_info info, t_token *last_inserted)
// {
// 	t_token	*new_token;

// 	new_token = add_token_at_position(info.head, info.value, info.token_type,
// 			info.quotes_type);
// 	if (last_inserted == NULL)
// 	{
// 		new_token->next = *(info.head);
// 		*(info.head) = new_token;
// 	}
// 	else
// 	{
// 		new_token->next = last_inserted->next;
// 		last_inserted->next = new_token;
// 	}
// 	return (new_token);
// }

t_token	*setup_token(char *value, int token_type, int quotes_type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = strdup(value);
	new_token->type = token_type;
	new_token->is_split = 0;
	new_token->quotes_info = malloc(sizeof(t_quotes_info));
	if (!new_token->quotes_info)
		return (free(new_token->value), free(new_token), NULL);
	new_token->quotes_info->quotes_type = quotes_type;
	new_token->next = NULL;
	return (new_token);
}
// Insert a new token at the appropriate position
t_token	*insert_new_token(t_insert_info info, t_token *last_inserted)
{
	t_token	*new_token;

	new_token = setup_token(info.value, info.token_type, info.quotes_type);
	if (!new_token)
		return (NULL);
	if (last_inserted == NULL)
	{
		if (*(info.head) == NULL)
		{
			*(info.head) = new_token;
		}
		else
		{
			new_token->next = (*(info.head))->next;
			(*(info.head))->next = new_token;
		}
	}
	else
	{
		new_token->next = last_inserted->next;
		last_inserted->next = new_token;
	}
	return (new_token);
}
// t_token *insert_new_token(t_insert_info info, t_token *last_inserted)  // func i use it in 2 and time and works
// {
//     t_token *new_token;

//     new_token = malloc(sizeof(t_token));
//     if (!new_token)
//         return NULL;
//     // Setup the token
//     new_token->value = strdup(info.value);
//     new_token->type = info.token_type;
//     new_token->is_split = 0;
//     new_token->quotes_info = malloc(sizeof(t_quotes_info));
//     if (!new_token->quotes_info)
//         return(free(new_token->value), free(new_token), NULL);
//     new_token->quotes_info->quotes_type = info.quotes_type;
//     if (last_inserted == NULL) // Insert the token in the right place
//     {
//         if (*(info.head) == NULL) // This is the first token from a split, insert it at the SAME position as the original token, not at the head
//         {
//             // List was empty
//             new_token->next = NULL;
//             *(info.head) = new_token;
//         }
//         else
//         {
//             new_token->next = (*(info.head))->next;
//             (*(info.head))->next = new_token;
//             return new_token;
//         }
//     }
//     else
//     {
//         new_token->next = last_inserted->next;
//         last_inserted->next = new_token;
//     }
//     return new_token;
// }
// process a word and insert it as a new token
t_token	*process_word(t_insert_info info, char *buff, t_token *last_inserted)
{
	info.value = buff;
	return (insert_new_token(info, last_inserted));
}

// process a single token that needs to be split by spaces
t_token	*process_split_token(char *input, t_token **head,
		t_token *last_inserted, int quotes_type)
{
	int				i;
	char			buff[1024];
	t_insert_info	info;

	i = 0;
	info.head = head;
	info.token_type = TOKEN_WORD;
	info.quotes_type = quotes_type;
	while (input[i] != '\0')
	{
		if (input[i] == ' ' || input[i] == '\t')
		{
			i = skip_whitespace(input, i);
		}
		else
		{
			i = extract_word(input, i, buff);
			if (buff[0] != '\0')
				last_inserted = process_word(info, buff, last_inserted);
		}
	}
	return (last_inserted);
}

t_token	*handle_split_token(t_token *current, t_token *prev, t_token **head)
{
	t_token *last_inserted;
	t_token *next;

	last_inserted = set_last_inserted(prev);
	last_inserted = process_split_token(current->value, head, last_inserted,
			get_quotes_type(current));

	next = current->next;
	remove_token(head, current);
	return (next);
}

// t_token *add_token_at_position(t_token **head, char *value, t_token_type type, int quotes_type)
// {
//     t_token *new_token;

//     new_token = malloc(sizeof(t_token)); // Allocate memory for the new token
//     if (!new_token)
//         return NULL;

//     new_token->value = strdup(value); // Set up the new token
//     new_token->type = type;
//     new_token->is_split = 0; // set is_split to 0 for new tokens
//     new_token->quotes_info = malloc(sizeof(t_quotes_info));
//     if (!new_token->quotes_info)
//     {
//         free(new_token->value);
//         free(new_token);
//         return NULL;
//     }
//     new_token->quotes_info->quotes_type = quotes_type;
//     new_token->next = NULL;  // The new token will not link anywhere yet
//     if (*head == NULL)
//     {
//         *head = new_token;
//         return new_token;
//     }
//     return new_token;
// }
