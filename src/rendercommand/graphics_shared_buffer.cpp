#include "graphics_render_command.h"

using namespace Graphics;


GSharedBuffer::GSharedBuffer() 
{
    fBuffer = nullptr;
    fRefCount = nullptr;
    fSizeInBytes = 0;
    fElementCount = 0;
}

GSharedBuffer::GSharedBuffer(const GSharedBuffer& other) 
{
    fBuffer = other.fBuffer;
    fRefCount = other.fRefCount;
    fSizeInBytes = other.fSizeInBytes;
    fElementCount = other.fElementCount;
    if (!IsNull())
    {
        (*fRefCount)++;
    }
}

void GSharedBuffer::operator=(const GSharedBuffer& other) 
{
    fBuffer = other.fBuffer;
    fRefCount = other.fRefCount;
    fSizeInBytes = other.fSizeInBytes;
    fElementCount = other.fElementCount;
    if (!IsNull())
    {
        (*fRefCount)++;
    }
}


GSharedBuffer::~GSharedBuffer() 
{
    Dispose();
}

size_t GSharedBuffer::GetElementCount() const
{
    return fElementCount;
}

size_t GSharedBuffer::GetSizeInByte() const
{
    return fSizeInBytes;
}

bool GSharedBuffer::IsNull() const
{
    return !fBuffer || !fRefCount;
}

void GSharedBuffer::Dispose() 
{
    if (!IsNull())
    {
        (*fRefCount)--;
        if ((*fRefCount) == 0)
        {
            fBuffer->Delete();

            delete fRefCount;
            delete fBuffer;

            fBuffer = nullptr;
            fRefCount = nullptr;
        }
    }
}

