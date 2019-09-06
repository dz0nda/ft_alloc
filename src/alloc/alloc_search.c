# include "alloc.h"

static t_node   *ft_alloc_search_first_fit(t_node *head, size_t size)
{
    t_node  *node;

    node = NULL;
    if ((node = head) == NULL)
        return (NULL);
    while (node->next != head)
    {
        if (node->size >= size && node->free == TRUE)
            break;
        node = node->next;
    }
    if (node->size >= size && node->free == TRUE)
        return (node);
    return (NULL);
}

t_node          *ft_alloc_search(t_node **head, size_t size)
{
    t_node *node;

    node = NULL;
    if (*head == NULL)
        return (NULL);
    if ((node = ft_alloc_search_first_fit(*head, size)) == NULL)
        return (NULL);
    return (node);
}