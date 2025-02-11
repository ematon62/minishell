/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:39:23 by ematon            #+#    #+#             */
/*   Updated: 2025/02/11 10:35:50 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <linux/limits.h>

typedef enum e_token
{
	CMD,
	CLA,
	PIPE
} token;
