#include "queue.h"

void    ft_enqueue(t_queue *queue, void *content)
{
    t_list *node;

    node = ft_lstnew(content);
    if (!node)
        return;
    if (!queue->front)
    {
        queue->front = node;
        queue->rear = node;
        return;
    }
    queue->rear->next = node;
    queue->rear = node;
}