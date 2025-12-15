/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dequeue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 18:40:15 by sblanco-          #+#    #+#             */
/*   Updated: 2025/12/15 18:41:25 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"

void	*ft_dequeue(t_queue *queue)
{
	t_list	*node;
	void	*content;

	if (!queue->front)
		return (NULL);
	node = queue->front;
	content = node->content;
	queue->front = queue->front->next;
	if (!queue->front)
		queue->rear = NULL;
	free(node);
	return (content);
}
