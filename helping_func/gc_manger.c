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

    node = malloc(sizeof(t_mem));  // Allocate a t_mem node
    if (!node) {
        free(ptr);
        return NULL;
    }

    node->ptr = ptr;
    node->next = gc->mem_list;  // Set the next pointer to the current list
    gc->mem_list = node;        // Add the node to the start of the list
    gc->total_allocs++;
    gc->total_bytes += size;

    return ptr;
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


void	gc_print_stats(t_gc *gc)
{
    if (!gc)
        return;
    
    printf("Memory usage:\n");
    printf("  Total allocations: %d\n", gc->total_allocs);
    printf("  Total bytes: %zu\n", gc->total_bytes);
}
