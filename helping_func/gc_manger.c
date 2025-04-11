# include "mini_shell.h"

t_gc	*gc_init()
{
    t_gc *gc = malloc(sizeof(t_gc));
    if (!gc)
        return NULL;
    
    gc->mem_list = NULL;
    gc->total_allocs = 0;
    gc->total_bytes = 0;
    
    return gc;
}

void *gc_malloc(t_gc *gc, size_t size)
{
    t_mem *node;
    void *ptr;

    if (!gc)
        return NULL;

    ptr = malloc(size);
    if (!ptr)
        return NULL;

    node = malloc(sizeof(t_mem));
    if (!node)
	{
        free(ptr);
        return NULL;
    }

    node->ptr = ptr;
    node->next = gc->mem_list;
    gc->mem_list = node;
    gc->total_allocs++;
    gc->total_bytes += size;

    return ptr;
}

void gc_free(t_gc *gc, void *ptr)
{
    if (!gc || !ptr)
        return;
    
    t_mem *curr;
    t_mem *prev;

	curr = gc->mem_list;
	prev = NULL;
    
    while (curr)
	{
        if (curr->ptr == ptr)
		{
            if (prev)
                prev->next = curr->next;
            else
                gc->mem_list = curr->next;
            free(ptr);
            free(curr);
			// >>> to remove it later
            gc->total_allocs--;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void	gc_cleanup(t_gc *gc)
{
    if (!gc)
        return;
    
    t_mem *curr;
    t_mem *next;

	next = NULL;
	curr = gc->mem_list;
    while (curr)
	{
        next = curr->next;
        free(curr->ptr);
        free(curr);
        curr = next;
    }
    gc->mem_list = NULL;
    gc->total_allocs = 0;
    gc->total_bytes = 0;
}

void	gc_destroy(t_gc *gc)
{
    if (!gc)
        return;
    
    gc_cleanup(gc);
    free(gc);
}


// void	gc_print_stats(t_gc *gc)
// {
//     if (!gc)
//         return;
    
//     printf("Memory usage:\n");
//     printf(">>> Total allocations: %d\n", gc->total_allocs);
//     printf(">>> Total bytes: %zu\n", gc->total_bytes);
// }
