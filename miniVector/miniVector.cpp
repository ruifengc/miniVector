#include "../minimemory/minimemory.h"
#include <stdexcept>
template<typename D>
class data{
public:
    D d;
public:
    data(D data):d(data){}
    void *operator new(size_t size){
        return myAlloc.allocate(size);
    }
    void operator delete(void *pdead,size_t size){
        return myAlloc.deallocate(pdead,size);
    }
    ~data(){
    }
    
};




template<typename T>
class vector{
private:
    // allocator alloc;
public:
    vector(int num,T value){
        for(int i=0;i<num;i++)
            new data<T>(value);
    }
    void add(T value){
        new data<T>(value);
    }
    void del(size_t index){
        delete reinterpret_cast<data<T>*>(reinterpret_cast<char*>(myAlloc.head)+sizeof(T)*index);
    }
    data<T>* begin(){
        return reinterpret_cast<data<T>*>(myAlloc.head);
    }
    data<T>* end(){
        return reinterpret_cast<data<T>*>(myAlloc.freeStore);
    }
    T operator [](size_t size){
        if(reinterpret_cast<void*>(reinterpret_cast<char*>(myAlloc.head)+sizeof(T)*size)>=reinterpret_cast<void*>(myAlloc.freeStore)){
            throw std::out_of_range("vector越界");
        }
        return (*reinterpret_cast<data<T>*>(reinterpret_cast<char*>(myAlloc.head)+sizeof(T)*size)).d;
    }
};


int main(){
    vector<long long> vll(1,1);
    for(int i=2;i<12;i++){
        vll.add(i);
    }
    vll.del(2);
    vll.del(3);
    auto l = vll.begin();
    while(l!=vll.end()){
        cout<<(*l).d<<std::endl;
        l++;
    }
}

