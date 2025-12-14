#include "queue.h"

void    ft_queue_init(t_queue *queue)
{
    queue->front = NULL;
    queue->rear = NULL;
}