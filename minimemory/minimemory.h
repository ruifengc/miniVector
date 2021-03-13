#ifndef __MINIMEMORY__
#define __MINIMEMORY__
#include<cstddef>
#include<string>
#include<iostream>
using std::string;
using std::cout;
class allocator{
private:
    struct  obj
    {
        struct obj* next;
    };
public:
    void *allocate(size_t size);
    void deallocate(void *deadobj,size_t size);
// 方便测试,暂时public
obj *head = nullptr;
obj *freeStore = nullptr;
private:
    
    int CHUNK = 2;
    
    // 返回一大块内存的首地址
    obj* __allocate__freeStore(size_t size);
    void* memcpy(void* dst, const void* src, int count);
};
allocator myAlloc;
#endif