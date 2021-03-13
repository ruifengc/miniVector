#include "minimemory.h"

// 使用的时候就是套一层壳调用allocate
class Foo{
public:
    // long L;
    long long L;
    // string str;
    static allocator myAlloc;
public:
    Foo(long long l):L(l){}
    void *operator new(size_t size){
        return myAlloc.allocate(size);
    }
    void operator delete(void *pdead,size_t size){
        return myAlloc.deallocate(pdead,size);
    }
    ~Foo(){
        cout<<"触发del";
    }
};
allocator Foo::myAlloc;


int main(){
    for(int i=0;i<10;i++){
        // new Foo();
        cout<<std::hex<<new Foo(666-i)<<std::endl;
        // delete f;
    }
    // cout<<"size"<<sizeof(Foo)<<std::endl;
    for(int i=0;i<10;i++){
        cout<<std::dec<<reinterpret_cast<Foo*>(reinterpret_cast<char*>(Foo::myAlloc.head)+sizeof(Foo)*i)->L<<std::endl;
    }
    return 0;
}