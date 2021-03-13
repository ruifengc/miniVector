#include "minimemory.h"

void *allocator::allocate(size_t size){
    allocator::obj *p;
    if(!freeStore){
        // 内存池为空
        head = __allocate__freeStore(size);
    }
    // 本内存池只剩最后一个位置了，开始扩容 扩容策略暂定为2倍扩容
    if(!freeStore->next){
        auto new_head = __allocate__freeStore(size);     
        freeStore = (allocator::obj*)memcpy(new_head,head,size*(CHUNK/4-1));
        free(head);
        // freeStore = ((obj*)((char*)new_head+size*(CHUNK/4-1)));
        head = new_head;
    }
    p = freeStore;
    // 他这里相当于只维护了freeStore,整个allocator中只存了一个头还有一个分配数量
    freeStore = freeStore->next;
    cout<<"分配："<<std::hex<<p<<std::endl;
    return p;
}
void allocator::deallocate(void *deadobj,size_t size){
        cout<<"回收："<<std::hex<<deadobj<<std::endl;
        ((allocator::obj*)deadobj)->next = freeStore;
        freeStore = (allocator::obj*)deadobj;
}
// 返回一大块内存的首地址
allocator::obj* allocator::__allocate__freeStore(size_t size){
    allocator::obj *p;
    size_t chunk = CHUNK*size;
    cout<<"分配内存池子"<<std::hex<<chunk<<std::endl;
    freeStore = p = (allocator::obj*)malloc(chunk);
    for(int i=0;i<(CHUNK-1);++i){
        p->next = (allocator::obj*)((char*)p+size);
        p = p->next;
    }
    p->next = nullptr;
    CHUNK = CHUNK*2;
    return freeStore;
}
void* allocator::memcpy(void* dst, const void* src, int count)
{
    void* ret = dst;
    while(count--)
    {
        *(char*)dst = *(char*)src;
        cout<<std::hex<<"dst "<<dst<<"<- src "<<src<<std::endl;
        dst=(char*)dst+1;
        src=(char*)src+1;
    }
    cout<<"return"<<std::hex<<dst<<std::endl;
    return dst;
}
