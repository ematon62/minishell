/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cisse <cisse@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:41:58 by ematon            #+#    #+#             */
/*   Updated: 2025/02/26 01:47:42 by cisse            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executing.h"

// int	main(int argc, char **argv, char **envp)
// {
// 	char	*input;
// 	t_shell	*shell;
// 	t_cmds	*cmds;

// 	(void)argv;
// 	(void)argc;
// 	setup_signals();
// 	shell = init_shell(envp);
// 	while (1)
// 	{
// 		if (isatty(STDIN_FILENO) && isatty(STDERR_FILENO))
// 		{
// 			input = readline("$");
// 			if (!input)
// 				break ;
// 			add_history(input);
// 			cmds = parse(input, shell);
// 			if (!cmds)
// 				continue ;
// 			execute(cmds, shell);
// 			free(input);
// 		}
// 	}
// 	free_shell(shell);
// 	printf("exit\n");
// 	return (g_signal);
// }

static void	sigint_handler(int sig)
{
	(void)sig;
	if (g_signal == 0)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		write(1, "\n", 1);
	g_signal = 130;
}

static void	sigquit_handler(int sig)
{
	(void)sig;
	if (g_signal == 1)
        write(2, "Quit (core dumped)\n", 19);
	g_signal = 131;
}

// Fonction utilitaire pour créer une commande simple
t_cmd *create_cmd(char **args, t_redirections *redirs) {
    t_cmd *cmd = malloc(sizeof(t_cmd));
    cmd->args = args;
    cmd->redirs = redirs;
    return cmd;
}

// Fonction utilitaire pour créer une redirection
t_redirections *create_redir(t_type type, char *target) {
    t_redirections *redir = malloc(sizeof(t_redirections));
    redir->type = type;
    redir->target = target;
    redir->next = NULL;
    return redir;
}

// Fonction utilitaire pour initialiser l'environnement sous forme de liste chaînée
t_env_lst *init_env_list(char **envp) {
    t_env_lst *env = NULL;
    int i = 0;

    while (envp[i]) {
        char *key = strtok(strdup(envp[i]), "=");
        char *value = strtok(NULL, "");
        if (key && value)
            update_env_var(&env, key, value);
        i++;
    }
    return env;
}



int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
    // Initialisation du shell
    t_shell shell = {0};
    shell.env = init_env_list(envp);
    shell.exit_status = 0;

    // Configuration des signaux
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, sigquit_handler);

    // // Test 1 : Redirection simple > output.txt
    // printf("=== Test 1: Redirection simple ===\n");
    // char *args1[] = {"cat", NULL};
    // t_redirections *redirs1 = create_redir(IS_TRUNCAT, "output.txt");
    // t_cmds *cmds1 = malloc(sizeof(t_cmds));
    // cmds1->cmd = create_cmd(args1, redirs1);
    // cmds1->next = NULL;
    // execute(cmds1, &shell);

    // Test 2 : Heredoc << EOF
    printf("\n=== Test 2: Heredoc ===\n");
    char *args2[] = {"cat", NULL};
    t_redirections *redirs2 = create_redir(IS_HEREDOC, "1");
    t_cmds *cmds2 = malloc(sizeof(t_cmds));
    cmds2->cmd = create_cmd(args2, redirs2);
    cmds2->next = NULL;
    execute(cmds2, &shell);

    // // Test 3 : Pipes ls -l | grep ".c"
    // printf("\n=== Test 3: Pipes ===\n");
    // char *args3[] = {"ls", "-l", NULL};
    // char *args4[] = {"grep", ".c", NULL};
    // t_cmds *cmds3 = malloc(sizeof(t_cmds));
    // cmds3->cmd = create_cmd(args3, NULL);
    // cmds3->next = malloc(sizeof(t_cmds));
    // cmds3->next->cmd = create_cmd(args4, NULL);
    // cmds3->next->next = NULL;
    // execute(cmds3, &shell);

	// // Test 3BIS : Pipes ls -l | grep ".c"
    // printf("\n=== Test 3BIS: Pipes ===\n");
    // char *args3[] = {"cat", NULL};
    // char *args4[] = {"cat", NULL};
    // t_cmds *cmds3 = malloc(sizeof(t_cmds));
    // cmds3->cmd = create_cmd(args3, NULL);
    // cmds3->next = malloc(sizeof(t_cmds));
    // cmds3->next->cmd = create_cmd(args4, NULL);
    // cmds3->next->next = NULL;
    // execute(cmds3, &shell);

    // // Test 4 : Redirection complexe < input.txt > output.txt
    // printf("\n=== Test 4: Redirection complexe ===\n");
    // char *args5[] = {"cat", NULL};
    // t_redirections *redirs5 = create_redir(IS_INREDIR, "input.txt");
    // redirs5->next = create_redir(IS_TRUNCAT, "output.txt");
    // t_cmds *cmds4 = malloc(sizeof(t_cmds));
    // cmds4->cmd = create_cmd(args5, redirs5);
    // cmds4->next = NULL;
    // execute(cmds4, &shell);

    // // Test 5 : Append redirection >>
    // printf("\n=== Test 5: Append redirection ===\n");
    // char *args6[] = {"echo", "Appended text", NULL};
    // t_redirections *redirs6 = create_redir(IS_APPEND, "output.txt");
    // t_cmds *cmds5 = malloc(sizeof(t_cmds));
    // cmds5->cmd = create_cmd(args6, redirs6);
    // cmds5->next = NULL;
    // execute(cmds5, &shell);

    // // Test 6 : Multiple pipes echo "test" | cat | grep "test"
    // printf("\n=== Test 6: Multiple pipes ===\n");
    // char *args7[] = {"echo", "test", NULL};
    // char *args8[] = {"cat", NULL};
    // char *args9[] = {"grep", "test", NULL};
    // t_cmds *cmds6 = malloc(sizeof(t_cmds));
    // cmds6->cmd = create_cmd(args7, NULL);
    // cmds6->next = malloc(sizeof(t_cmds));
    // cmds6->next->cmd = create_cmd(args8, NULL);
    // cmds6->next->next = malloc(sizeof(t_cmds));
    // cmds6->next->next->cmd = create_cmd(args9, NULL);
    // cmds6->next->next->next = NULL;
    // execute(cmds6, &shell);

    // // Test 7 : Builtins cd /tmp && pwd
    // printf("\n=== Test 7: Builtins ===\n");
    // char *args10[] = {"cd", "/tmp", NULL};
    // t_cmds *cmds7 = malloc(sizeof(t_cmds));
    // cmds7->cmd = create_cmd(args10, NULL);
    // cmds7->next = NULL;
    // execute(cmds7, &shell);

    // // Test 8 : Redirection avec pipeline cat < input.txt | grep "hello"
    // printf("\n=== Test 8: Redirection avec pipeline ===\n");
    // char *args12[] = {"cat", NULL};
    // char *args13[] = {"grep", "hello", NULL};
    // t_redirections *redirs12 = create_redir(IS_INREDIR, "input.txt");
    // t_cmds *cmds8 = malloc(sizeof(t_cmds));
    // cmds8->cmd = create_cmd(args12, redirs12);
    // cmds8->next = malloc(sizeof(t_cmds));
    // cmds8->next->cmd = create_cmd(args13, NULL);
    // cmds8->next->next = NULL;
    // execute(cmds8, &shell);

    // // Test 9 : Heredoc avec pipeline cat << EOF | grep "world"
    // printf("\n=== Test 9: Heredoc avec pipeline ===\n");
    // char *args14[] = {"cat", NULL};
    // char *args15[] = {"grep", "world", NULL};
    // t_redirections *redirs14 = create_redir(IS_HEREDOC, "EOF");
    // t_cmds *cmds9 = malloc(sizeof(t_cmds));
    // cmds9->cmd = create_cmd(args14, redirs14);
    // cmds9->next = malloc(sizeof(t_cmds));
    // cmds9->next->cmd = create_cmd(args15, NULL);
    // cmds9->next->next = NULL;
    // execute(cmds9, &shell);

    // Test 10 : Commande externe avec redirection complexe
    // printf("\n=== Test 10: Commande externe avec redirection complexe ===\n");
    // char *args16[] = {"ls", "-l", NULL};
    // t_redirections *redirs16 = create_redir(IS_TRUNCAT, "output.txt");
    // redirs16->next = create_redir(IS_APPEND, "input.txt");
    // t_cmds *cmds10 = malloc(sizeof(t_cmds));
    // cmds10->cmd = create_cmd(args16, redirs16);
    // cmds10->next = NULL;
    // execute(cmds10, &shell);
    return 0;
}
