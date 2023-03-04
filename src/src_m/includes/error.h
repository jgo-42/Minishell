/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:38:31 by jgo               #+#    #+#             */
/*   Updated: 2023/03/04 16:13:38 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define ERR_ARGS "arg error: minishell dosen't take args"
# define ERR_INVALID_ARGS "Invalid argument"

# define ERR_NOT_SET "not set"
# define ERR_INVALID_IDENT "not a valid identifier"
# define ERR_CMD_NOT_FOUND "command not found"

//  File name too long 255 글자기준. 
# define ERR_SYN_RDR_OUT "syntax error: near unexpected token `>'"
# define ERR_SYN_RDR_NL "syntax error: near unexpected token `newline'"
# define ERR_SYN_RDR_IN "syntax error: near unexpected token `<'"
# define ERR_SYN_RDR_PIPE "syntax error: near unexpected token `|'"
# define ERR_SYN_HERE "syntax error near unexpected token `<<'"
# define ERR_SYN_APPEND "syntax error near unexpected token `>>'"
# define ERR_SYN_QUOTE "syntax error: unclosed quote"
# define ERR_SYN_ML "syntax error: not support multi-line"

t_bool prt_err(const char *str, int exit_status);
t_bool	prt_built_in_err(char *cmd, char *key, char *msg, int exit_status);
int		parsing_error(t_err_type err);
t_bool	prt_sc_err(int rv);

#endif