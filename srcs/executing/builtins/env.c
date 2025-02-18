/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adcisse <adcisse@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-18 15:32:35 by adcisse           #+#    #+#             */
/*   Updated: 2025-02-18 15:32:35 by adcisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/executing.h"

int	builtin_env(t_env_lst *env)
{
	while (env)
	{
		if (env->is_env && env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}

// // Fonction utilitaire pour créer un nouvel élément de la liste cc -Wall -Wextra -Werror -I../../../libft -L../../../libft -g env.c -lft
// t_env_lst *create_env_node(char *key, char *value, int is_env)
// {
//     t_env_lst *new_node = malloc(sizeof(t_env_lst));
//     if (!new_node)
//     {
//         perror("malloc");
//         exit(EXIT_FAILURE);
//     }
//     new_node->key = key;
//     new_node->value = value;
//     new_node->is_env = is_env;
//     new_node->next = NULL;
//     return new_node;
// }

// // Fonction principale pour tester builtin_env
// int main()
// {
//     // Création d'une liste chaînée simulée pour les variables d'environnement
//     t_env_lst *env_list = NULL;
//     t_env_lst *node1 = create_env_node("PATH", "/usr/bin:/bin", 1);
//     t_env_lst *node2 = create_env_node("HOME", "/home/user", 1);
//     t_env_lst *node3 = create_env_node("USER", "testuser", 1);
//     t_env_lst *node4 = create_env_node("INVALID", NULL, 0); // Variable invalide (pas affichée)

//     // Construction de la liste chaînée
//     env_list = node1;
//     node1->next = node2;
//     node2->next = node3;
//     node3->next = node4;

//     // Appel de la fonction builtin_env
//     printf("Affichage des variables d'environnement valides :\n");
//     builtin_env(env_list);

//     // Libération de la mémoire allouée
//     t_env_lst *current = env_list;
//     while (current)
//     {
//         t_env_lst *temp = current;
//         current = current->next;
//         free(temp);
//     }

//     return 0;
// }
