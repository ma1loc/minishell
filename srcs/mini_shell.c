# include "mini_shell.h"
# include "../parsing/tokenizer.h"

// >>> minishell header
// >>> heredoc have to be form A-Z order
// adsf | ls | eadsf >>> test the exit status of it 
// < Makefile > 5
// < Makefile | cat >>> segv
// ls || cat >>> segv
// ls >
// < Makefile > 5 << l cat >>> delimiter problem
// echo $? >>> not working
// Makefile > cat
// export a="ls |cat"
// minishell$ cat << EOF | grep success | tee output.txt | wc -l >> log.txt
// export a+="hello_world" -> to fix later on
// ls   -la >>> command not found in tab char and newline
// is i have to update the SHLVL=1???
// env -i ./minishell
// echo yassin > a > b >c > /dev/stdout
// if the delimiter have qutes no expand
// parsing the qutes
// delemiter most check if there's qutes other wayse if it single or double just print it with it's qutes
// update input with it's env value
// >>> here i have to get the env key
// >>> but first thing i have to check it if valid or not, i mean the fist char
// >>> i have to split it
// >>> $->$		$$(skipe)	$$$->$
// >>> qutes in heredoc "$HOME"
// $HOME" '$HOME' '$HOME "$HOME $HOME' $HOME" "$HOME"
// >>>> to check it <<<<
// handel -> double $ signe
// handel -> $?
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// >>> Key must start with letter or underscore
// >>> bash: export: `5': not a valid identifier
// >>> bash: export: `h-ello': not a valid identifier
// minishell$ export PATH=/bin/
// minishell$ ls
// Command not found
// minishell$ 
// export a+="hello_world" >>> to handel it
// export a="" >>> to handel it
// export: `a++=l': not a valid identifier
// export: `a+l': not a valid identifier
// yanflous@e2r5p4:/home/yanflous$ export a+=+=+=l
// yanflous@e2r5p4:/home/yanflous$ export a+=+ =+=l
// bash: export: `=+=l': not a valid identifier
// export SHLVL=-198892983983928398293982838928392809878979878
// yanflous@e2r5p4:/home/yanflous$ export SHLVL=1000 
// yanflous@e2r5p4:/home/yanflous$ exit^C            
// yanflous@e2r5p4:/home/yanflous$ bash
// bash: warning: shell level (1001) too high, resetting to 1
// parsing the value of the exporot key to expand
//	'nothing'->0 '='->1 '+='->2 'error->-1'
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// minishell$ echo echo $HOME        $HOME      $?
// echo /home/yanflous /home/yanflous 0
// minishell$ exit
// exit
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// export a="$HOME $PATH $?"
// echo $HOME   $HOME

t_gc *gc = NULL;

int		main(int argc, char **argv, char **env)
{
    t_setup	*setup;

	gc = gc_init();
    setup = start_setup(argc, argv, env);
	if (!setup)
		return (1);
    while (true)
    {
        setup->input = readline("minishell$ ");
        if (setup->input == NULL)
            break ;  // >>> for segnal case to free litter on
        if (setup->input[0] == '\0')
            continue ;
		add_history(setup->input);
        setup->token = tokenize(setup);
        if (!setup->token || ft_strlen(setup->token->value) == 0)
			continue ;
		setup->cmd = pars_tokens(setup);
        setup->tree = build_tree_commande(setup->cmd);
		heredoc_process(setup, setup->tree);
        execution(setup->tree, setup);
		free(setup->input);
    }
	// gc_destroy(gc);
    return 0;
}
