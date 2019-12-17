/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <amagnan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:08:05 by amagnan           #+#    #+#             */
/*   Updated: 2019/12/16 16:18:00 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void				rt_main_thread_too(t_rt *rt, void *fun4)
{
	rt->thread[3].thread = SDL_CreateThread(fun4, "thread4", (void*)rt);
	SDL_WaitThread(rt->thread[3].thread, NULL);
}

void				rt_main_thread(t_rt *rt, void *fun1, void *fun2, void *fun3)
{
	rt->thread[0].thread = SDL_CreateThread(fun1, "thread1", (void*)rt);
	rt->thread[1].thread = SDL_CreateThread(fun2, "thread2", (void*)rt);
	rt->thread[2].thread = SDL_CreateThread(fun3, "thread3", (void*)rt);
	SDL_WaitThread(rt->thread[0].thread, NULL);
	SDL_WaitThread(rt->thread[1].thread, NULL);
	SDL_WaitThread(rt->thread[2].thread, NULL);
}

void				rt_render(t_rt *rt)
{
	rt_main_thread(rt, rt_thread_1, rt_thread_2, rt_thread_3);
	rt_main_thread_too(rt, rt_thread_4);
}
