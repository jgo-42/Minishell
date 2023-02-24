/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:15:15 by jgo               #+#    #+#             */
/*   Updated: 2023/02/24 17:41:16 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "envp_command.h"
#include "meta_command.h"
#include "error.h"
#include <errno.h>
// OLDPWD - option
// HOME default 
// cd sdfsd sdfs<- 무시하고 진행함. 

// cd에 인자가 주어져 있지 않은 경우 `$HOME`가 기본적으로 앞에 있는 것처럼 동작한다.
// 슬래시 `(/)`  가 첫번째 인자로 들어오면 절대경로로 동작한다. 
// 점 `(.) or (..)` 으로 시작하면 상대경로로 동작한다.

t_bool  exec_cd(char *cur_path)
{
    t_hash_elem *elem;
    char    *path;

    if (cur_path == NULL)
    {
        path = get_envp_elem("HOME")->val;
        if (path == NULL)
            return (print_built_in_err("cd","HOME", "not set"));
    }
    else if (ft_strncmp(cur_path, "-", ft_strlen(cur_path)) == 0)
    {
        path = get_envp_elem("OLDPWD")->val;
        if (path == NULL)
            return (print_built_in_err("cd", "OLDPWD","not set"));
    }
    else
        path = cur_path;
    if(chdir(path) == -1)
    {
        free(path);
        return (print_error(strerror(errno)));
    }
    free(path);
    return (FT_TRUE);
}

void ft_cd(t_simple_cmd *simple_cmd)
{
    t_hash_elem *pwd;
    char *cwd;

    if (exec_cd(simple_cmd->args[1]) == BUILT_IN_EXEC_OK)
    {
        pwd = get_envp_elem("PWD");
        set_envp_elem("OLDPWD", pwd->val);
        cwd = getcwd(NULL, 0);
        if (cwd == NULL)
            print_error(strerror(errno));
        set_envp_elem("PWD", cwd);
        set_exit_status(EXIT_SUCCESS);
    }
}