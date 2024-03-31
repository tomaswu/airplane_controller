#ifndef BUFFER
#define BUFFER

typedef unsigned char uchar;

class CycleBuff{
    
public:

    CycleBuff(int mem_n){
        memory_size = mem_n;
        ptr = new uchar[memory_size];
    }

    ~CycleBuff(){
        delete[] ptr;
    }

    void push_back(uchar c){
        if(size<memory_size){
            ptr[_index(size)] = c;
            size++;
        }
    }
    
    void push_back(uchar *c,int len){
        for(int i=0;i<len;i++){
            push_back(c[i]);
        }
    }

    void moveEntry(int move_n){
        if(move_n>0){
            size-=move_n;
            size = size<0? 0:size;
        }
        entry = (entry+move_n);
        while (entry<0)
        {
            entry+=memory_size;
        }
        entry=entry%memory_size;
    }

    uchar operator[](int idx){
        if(idx<0){
            idx+=memory_size;
        }
        return ptr[_index(idx)];
    }

    int length(){
        return size;
    }


private:
    uchar *ptr;
    int memory_size{0};
    int size{0};
    int entry{0};
    
    int _index(int idx){
        int tmp = idx+entry;
        if(tmp>=memory_size) tmp-=memory_size;
        return tmp;
    }

};




#endif