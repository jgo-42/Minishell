/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_controller.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:56:45 by jgo               #+#    #+#             */
/*   Updated: 2023/03/12 17:43:50 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_CONTROLLER_H
# define SIGNAL_CONTROLLER_H

/* signal_init.c */
void	set_signal_init(int signum);
void	signal_init(struct sigaction *s_int, struct sigaction *s_quit);

/* signal)child.c */
void	signal_child(pid_t	pid);

/* signal_controller.c */
void	signal_controller(t_signal_flags flag, pid_t pid);

#endif