#include "Toolbox.h"

DECOMP_SIZE_ASSERT(ToolboxChunks, 0x30)

// FUNCTION: GAME 0x005e3040
ToolboxChunks::ToolboxChunks(const std::allocator<ToolboxChunk> &allocation)
    : std::deque<ToolboxChunk>(allocation)
{
}
