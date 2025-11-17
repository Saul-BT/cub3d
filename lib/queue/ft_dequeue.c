#include "queue.h"

void    *ft_dequeue(t_queue *queue)
{
    t_list *node;
    void *content;

    if (!queue->front)
        return NULL;
    node = queue->front;
    content = node->content;
    queue->front = queue->front->next;

    if (!queue->front)
        queue->rear = NULL;

    free(node);

    return content;
}