/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:38:28 by jgo               #+#    #+#             */
/*   Updated: 2023/01/28 17:06:49 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DECLARATION_H
# define DECLARATION_H

# define LOOP TRUE
# define MY_PROMPT "> "

/* enum typedef */

typedef enum e_token_type t_token_type;
typedef enum e_rdr_type t_rdr_type;

/* struct typedef */

typedef struct s_meta t_meta;
typedef struct s_tree t_tree;
typedef struct s_cmd t_cmd;
typedef struct s_rdr t_rdr;
typedef struct s_pipe t_pipe;
typedef struct s_token t_token;
typedef struct s_simple_cmd t_simple_cmd;

/* union typedef */

typedef union u_cmd t_ucmd;

enum e_token_type
{
	RDR = 0,
	PIPE = 1,
	CMD = 2,
	WORD = 3
};

enum e_rdr_type
{
	IN = 0,
	OUT = 1,
	APPEND = 2,
	HEREDOC = 3
};

struct s_meta  // 모든 구조체를 담을 부모구조체
{
	int		err;
	t_list *envp;
	t_list *unlink_lst; // here_doc의 예외처리를 위한 list
	// t_history;
};

// union 활용 버전
union u_cmd
{
	t_simple_cmd	*simple_cmd;
	t_rdr			*rdr_type;
	t_pipe			*pipe_type;
};

struct s_token
{
	t_token_type	type;
	t_ucmd u_cmd;
};

struct s_simple_cmd
{
	char	*cmd;
	char	**args;
};

struct s_rdr
{
	t_rdr_type rdr_type;
	char	*file;
	t_rdr *next;
};

struct s_pipe
{
	int	fd[2];
};

struct s_tree {
	void			*value;
	struct s_tree	*left;
	struct s_tree	*right;
};

#endif