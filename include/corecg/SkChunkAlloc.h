/* include/corecg/SkChunkAlloc.h
**
** Copyright 2006, Google Inc.
**
** Licensed under the Apache License, Version 2.0 (the "License"); 
** you may not use this file except in compliance with the License. 
** You may obtain a copy of the License at 
**
**     http://www.apache.org/licenses/LICENSE-2.0 
**
** Unless required by applicable law or agreed to in writing, software 
** distributed under the License is distributed on an "AS IS" BASIS, 
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
** See the License for the specific language governing permissions and 
** limitations under the License.
*/

#ifndef SkChunkAlloc_DEFINED
#define SkChunkAlloc_DEFINED

#include "SkTypes.h"

class SkChunkAlloc : SkNoncopyable {
public:
    SkChunkAlloc(size_t minSize);
    ~SkChunkAlloc();

    /** Free up all allocated blocks. This invalidates all returned
        pointers.
    */
    void reset();

    /** Reuse all allocated blocks. This invalidates all returned
        pointers (like reset) but doesn't necessarily free up all
        of the privately allocated blocks. This is more efficient
        if you plan to reuse the allocator multiple times.
    */
    void reuse();

    enum AllocFailType {
        kReturnNil_AllocFailType,
        kThrow_AllocFailType
    };
    
    void* alloc(size_t bytes, AllocFailType);
    void* allocThrow(size_t bytes) {
        return this->alloc(bytes, kThrow_AllocFailType);
    }
    
    size_t totalCapacity() const { return fTotalCapacity; }
    
private:
    struct Block;
    Block*  fBlock;
    size_t  fMinSize;
    Block*  fPool;
    size_t  fTotalCapacity;

    Block* newBlock(size_t bytes, AllocFailType ftype);
};

#endif
