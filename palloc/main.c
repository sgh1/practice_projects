
/* Very simple pool/bump allocator. */

#include <stdio.h>


/* Fixed size chunk. */
struct palloc_chunk
{
	struct chunk* next_;
};

/* Backing memory for chunks. */
struct palloc_block
{
	/* Backing memory */
	void* blk_;
	
	/* Pointer to next free block */
	struct chunk* next_;
};



/* Allocate / deallocate backing memory. */
void palloc_block_init(struct palloc_block* blk);
void palloc_block_allocate(struct palloc_block* blk, unsigned nChunks, unsigned chunkSize);
unsigned palloc_block_get_free_chunks(struct palloc_block* blk);
void palloc_block_free(struct palloc_block* blk);

/* Allocate (and bump) / deallocate chunks. */
void *palloc_chunk_allocate(struct palloc_block* blk);
void palloc_chunk_deallocate(struct palloc_block* blk, struct palloc_chunk* chk);



void palloc_block_init(struct palloc_block* block)
{
	if(!block)
	{
		printf("NULL block specified.");
		return NULL;
	}

	block->blk_ = NULL;
	block->next_ = NULL;
}

void palloc_block_allocate(struct palloc_block* blk, unsigned nChunks, unsigned chunkSize)
{
	if(!block)
	{
		printf("NULL block specified.");
		return NULL;
	}
	
	if(block->blk_)
	{
		printf("Block is already allocated.");
		return NULL;
	}

	/* Allocate block. */
	block->blk_ = malloc(nChunks * chunkSize);
	
	/* Set up linked list of chunks. */	
	
	struct palloc_chunk* chunk = (palloc_chunk*) blk->blk_;
	
	for(unsigned i = 0; i < nChunks - 1; i++)
	{
		struct palloc_chunk* next_chunk = (palloc_chunk*) ((void*)chunk + chunkSize);
		
		chunk->next_ = next_chunk;
		chunk = next_chunk;
	}
	
	chunk->next_ = NULL;	
}

void palloc_block_free(struct palloc_block* block)
{
	if(!block)
	{
		printf("NULL block specified.");
		return NULL;
	}
	
	if(!block->blk_)
	{
		printf("Block is not allocated.");
		return NULL;
	}
		
	free(block->blk_);
	block->blk_ = NULL;
}

unsigned palloc_block_get_free_chunks(struct palloc_block* block)
{
	if(!block)
	{
		printf("NULL block specified.");
		return NULL;
	}
	
	if(!block->blk_)
	{
		printf("Block is not allocated.");
		return NULL;
	}

	unsigned n_free = 0;
	
	struct palloc_chunk* chunk = block->blk_;
	
	while(chunk)
	{
		n_free++;
		
		chunk = chunk->next_;
	}
	
	return n_free;
}

void* palloc_chunk_allocate(struct palloc_block* block)
{
	if(!block)
	{
		printf("NULL block specified.");
		return NULL;
	}
	
	if(!block->blk_)
	{
		printf("NULL block specified.");
		return NULL;	
	}

	struct palloc_chunk* chunk = block->next_;
	
	block->next_ = chunk->next_;	
	
	return (void*) chunk;
}

void palloc_chunk_deallocate(struct palloc_block* block, struct palloc_block* chunk)
{
	if(!block)
	{
		printf("NULL block specified.");
		return NULL;
	}
	
	if(!chnk)
	{
		printf("NULL chunk specified.");
		return NULL;	
	}
	
	/* Add chunk to front of list. */
	chunk->next_ = block->next_;	
	block->next_ = chunk; 
}





int main() 
{
    printf("Hello, World!\n");
















    return 0;
}
