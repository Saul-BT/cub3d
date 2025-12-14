#include "../megalibft/libft.h"

typedef struct s_queue
{
    t_list  *front;
    t_list  *rear;
} t_queue;

void    ft_queue_init(t_queue *queue);
void    ft_enqueue(t_queue *queue, void *content);
void    *ft_dequeue(t_queue *queue);
