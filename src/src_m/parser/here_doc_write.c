/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_write.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:20:14 by sanghwal          #+#    #+#             */
/*   Updated: 2023/03/10 18:11:25 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "parser.h"
#include "utils.h"
#include "data_structure.h"
#include "meta_command.h"
#include "expander.h"
#include "signal_controller.h"
#include "error.h"

void	write_util(int fd, char *line, t_bool	expand)
{
	char	*tmp;

	if (!line)
		prt_sc_err(write(fd, "\n", 1));
	else
	{
		if (expand)
			line = here_doc_expand(line);
		tmp = ft_strjoin(line, "\n");
		prt_sc_err(write(fd, tmp, ft_strlen(line) + 1));
		free(tmp);
		free(line);
	}
}

void	here_doc_write(int fd, char *delimter, t_bool expand)
{
	const int	del_len = ft_strlen(delimter);
	char	*line;
	char	*tmp;
	int		len;

	printf("del : %s", delimter);
	while (1)
	{
		line = readline("> ");
		len = ft_strlen(line);
		printf("line %s\n", line);

		if ((ft_strncmp(line, delimter, len) == 0 && \
			len == del_len))
			break ;
		write_util(fd, line, expand);
	}
	free(line);
}


void	write_to_file(t_list **tk_list, t_deque *dque, int fd)
{
	t_tokenize	*token;
	char		*delimter;
	char		*new_delimter;
	t_bool	expand;

	token = ((t_list *)(dque->pop_front(dque)))->content;
	delimter = token->str;
	new_delimter = NULL;
	expand = !validation_delimter(delimter, &new_delimter);
	here_doc_write(fd, new_delimter, expand);
	free(new_delimter);
	delete_lst_node(tk_list, token);
}