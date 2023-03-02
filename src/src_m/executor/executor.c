/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 17:44:42 by jgo               #+#    #+#             */
/*   Updated: 2023/03/02 21:34:44 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "executor.h"
#include "built_in.h"
#include "meta_command.h"

void	executor_classify_token(t_tree_node	*node, t_executor *execute)
{
	const t_token_type type = check_token_type(node);

	if (type == PIPE)
		pipe_executor(node, execute);
}

t_bool	is_built_in(t_tree_node *root)
{
	const t_simple_cmd_type s_type = is_built_in_cmd(((t_simple_cmd *)((t_token *)(root->right->right->value))->cmd_val.simple_cmd)->cmd);

	if (s_type != FT_EXTERNAL)
		return (FT_TRUE);
	else
		return (FT_FALSE);
}

t_bool	is_single(t_tree_node *root)
{
	const t_token_type t_type = ((t_token *)(root->right->value))->type;

	if (t_type != PIPE)
		return (FT_TRUE);
	else
		return (FT_FALSE);
}
// S_CMD 실행시에만 fork를 떠보자. 
// 실행 이전에 처리해야 할 것들.
// 부모와 자식 signal 처리.
// abs_path가져오기.  // execve는 첫번째 인자로 absolute파일을 받는다. 
// 부모는 자식의 pid를 받고 wait, waitpid를 건다. 마지막 자식의 exit_status저장. 
// 그렇다면 pipe는 어떻게 저장할 것인가? -> pipe_lst? 와 같은 자료구조 중에 하나를 사용해서 전달해야할 fd값을 저장한다.
// 그 와중에 rdr이 있다면 handling을 해준다. abs_path를 가져와서 실행가능하다면 실행 아니면 command not found
// 실행 이후 처리해야 할 것들.
// 사용한 pipe의 fd는 close 
// rdr도 close

void	recursive_exec(t_tree_node *node, t_executor *execute)
{
	if (node == NULL)
		return ;
	executor_classify_token(node, execute);
	recursive_exec(node->right, execute);
}

// void	exec_cmd_helper(void)
// {
// 	if ( < 0)
// 		return ;
// 	while (wait(&g_minishell.pid) > 0)
// 		(void)g_minishell.pid;
// 	if (g_minishell.pid == 2)
// 		set_status(130);
// 	else if (g_minishell.pid == 3 || g_minishell.pid == 131)
// 		set_status(131);
// 	else
// 		set_status(WEXITSTATUS(g_minishell.pid));
// 	g_minishell.pid = 0;
// }

// list 로 pid 저장.
void    executor(t_tree *tree)
{
	t_executor	execute;
	t_bool	s_built;
	t_bool	s_single;
	
	if (tree == NULL || tree->root == NULL)
		return ;
	s_single = is_single(tree->root);
	if (s_single)
		s_built = is_built_in(tree->root);
	else
		s_built = FT_FALSE;
	execute.in_fd =  dup(STDIN_FILENO); // 이걸 먼저 dup하고 dup2하고다시 돌려놓으면 되지 않을까?
	execute.out_fd = dup(STDOUT_FILENO);
	ft_memset(&execute.cur_fd, -1, sizeof(int) * 2);
	ft_memset(&execute.prev_fd, -1, sizeof(int) * 2);
	execute.pipe_cnt[0] = 0;
	execute.pipe_cnt[1] = 0;
	/*
	while (!tree.empty())
	{
		while (다음 파이프까지)
		{
			tree.pop(); // 트리의 맨 끝을 팝
			// 커맨드들을 다 리스트던 문자열 배열이던 어딘가에 담습니다.
		}
	}
	*/
	if (s_built && s_single)
		s_built_in_exec(tree->root, &execute);
	else if (s_single)
	{
		cmd_executor(tree->root->right, &execute, RIGHT);
		// waitpid(pid, get_exit_status(), 0);
	}
	else
		recursive_exec(tree->root->right, &execute);
	rdr_restore(&execute);
	// exec_cmd_helper();
}
// rdr이 있으면 rdr우선으로 처리한다. (파이프 처리하지 않음.)
// 없다면 파이프기준 오른쪽 cmd는 pipe에서 읽어온다. 
// 마지막 노드는 표준 출력으로 dup2한다. 
// 우리의 minishell에서는 루트 pipe는 자식 프로세스를 생성하는 역할만 한다?!