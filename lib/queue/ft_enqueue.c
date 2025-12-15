/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_enqueue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 18:40:12 by sblanco-          #+#    #+#             */
/*   Updated: 2025/12/15 18:41:34 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"

void	ft_enqueue(t_queue *queue, void *content)
{
	t_list	*node;

	node = ft_lstnew(content);
	if (!node)
		return ;
	if (!queue->front)
	{
		queue->front = node;
		queue->rear = node;
		return ;
	}
	queue->rear->next = node;
	queue->rear = node;
}
