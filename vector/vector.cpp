// vector.cpp 
#include <iostream>


template<class T>
class Vector {
public:
    
  
    Vector(){ 
        std::cout << "const";
        pointer = new T[this->capacity];
    }
    template<class T1>
    Vector(std::initializer_list<T1> value) : capacity{value.size()} {
    
    if (value.size() == 0) {
        return;
    }
    else{ 
        pointer = new T[this->capacity];
        for (const T& ob : value) {
            pointer[size] = ob;
            ++size;
             }
        }
    }
 
    Vector(size_t size_of_vector) {
        capacity = size_of_vector;
        pointer = new T[this->capacity];
    }
    Vector(const Vector& copy) {
        pointer = new T[copy.capacity];
            for (decltype(size) i = 0; i < size; ++i) 
                {
                    this->pointer[i] = copy.pointer[i];
                }
            return *this;
            }
    Vector(Vector&& move)noexcept {
        this->pointer = move.pointer;
        this->size = move.size;
        this->capacity = move.capacity;
        move.pointer = nullptr;
        return *this;
    }

    Vector& operator=(const Vector& copy) {
        pointer = new T[copy.capacity];
            for (decltype(size) i = 0; i < size; ++i)
            {
                this->pointer[i] = copy.pointer[i];
            }
            return *this;
    }
    Vector& operator=(Vector&& move) noexcept {
        this->pointer = move.pointer;
        this->size = move.size;
        this->capacity = move.capacity;
        move.pointer = nullptr;
        return *this;
    }
        ~Vector() {
            delete[] pointer;
        }

        void push_back(T value) {
            if (capacity == 0)
                ++capacity;
             if(capacity > size ) {
                pointer[size] = value;
                ++size;
            }
            else {
                this->capacity *= 2;
                T* new_memory_vector = new T[this->capacity];
                for (decltype(size) i = 0; i < size; ++i) {
                    new_memory_vector[i] = pointer[i];
                }
                delete[] pointer;
                pointer = new_memory_vector;
                pointer[size] = value;
                ++size;
            }
        }
    
        T front() {
            if (size >= 0)
                return pointer[0];
            else 
                std::cout << "error";
        }

        T back() {
            if (size >= 0)
                return pointer[size-1];
            else 
                std::cout << "error";

        }
        T* begin() {
            return pointer;
        }
        T* end(){
            return (pointer+size-1);
        }

        void write() {
            std::cout << "vector =";
            for (decltype(size) i = 0; i < size; ++i) {
                std::cout << "  " << pointer[i] ;
            }
            std::cout << std::endl;
        }


        template< class Args >
        void emplace_back(Args&& value) {
            if (capacity > size) {
               new (pointer+size)  T(value);
                ++size;
            }
            else {
                this->capacity *= 2;
                T* new_memory_vector = new T[this->capacity];
                for (decltype(size) i = 0; i < size; ++i) {
                    new_memory_vector[i] = pointer[i];
                }
                delete[] pointer;
                pointer = new_memory_vector;
                new (pointer + size)  T(value);
                ++size;
            }
            
        }

        template< class... Args, class T1 >
        void emplace_back(T1 value, Args&& ...args) {
            if (capacity > size) {
                new (pointer + size) T(value);
                ++size;
                emplace_back(args...);
            }
            else {
                this->capacity *= 2;
                T* new_memory_vector = new T[this->capacity];
                for (decltype(size) i = 0; i < size; ++i) {
                    new_memory_vector[i] = pointer[i];
                }
                delete[] pointer;
                pointer = new_memory_vector;
                new (pointer + size)  T(value);
                ++size;
                emplace_back(args...);
            }
          
        }
        size_t size_() {
            return size;
        }
        size_t capacity_() {
            return capacity;
        }
        bool empty_() {
            if (size == 0)
                return true;
            else
                return false;
        }

        T* insert( T* it, T value) {
            if (size + 1 > capacity) {
                this->capacity *= 2;
                T* new_memory_vector = new T[this->capacity];
                for (decltype(size) i = 0; i < size; ++i) {
                    new_memory_vector[i] = pointer[i];
                }
                delete[] pointer;
                pointer = new_memory_vector;
            }
            T switch_;
            ++size;
            for (decltype(size) i = 0, k = 0; i < size; ++i) {
                if (pointer + i == it) {
                    switch_ = pointer[i];
                    pointer[i] = value;
                    ++i;
                    value = pointer[i];
                    for (; i < size; ++i) {
                        pointer[i] = switch_;
                        switch_= value;
                        value = pointer[i + 1];
                    }
                }
                   
            }
            return it;
        }

        T* erase(size_t pos) {

            T* it=pointer;

            if (pos > size)
                return it;
            --pos;
            for (decltype(size) i = 0; i < size; ++i) {
                if (i == pos) {
                    it = &pointer[i];
                    for (; i < size && (i - 1) != size; ++i)
                        pointer[i] = pointer[i + 1];
                }
            }
            --size;
            return it;
           
        }
        T erase(T* pos) {
            
            T it = *pointer;

            if (pos==0 )
                return it;
            for (decltype(size) i = 0; i < size; ++i) {
                if (pos == (pointer + i)) {
                    it = pointer[i];
                    for (; i < size && (i - 1) != size; ++i)
                        pointer[i] = pointer[i + 1];

                }
            }
            --size;
            return it;

        }
        
        T* erase(T* begin, T* end) {
            T* it = begin;
            int nsize = 0;
            if (begin < end) {
                nsize =  end - begin;
            }
            else
                return begin;
            
            std::cout << "size  " << nsize << "  "  << std::endl;
         
            for (decltype(size) i = 0; i < size; ++i) {
                if (begin == (pointer + i)) {
                    for (;  end <= &pointer[size]; ++i) {
                        pointer[i] = *end;
                        end++;
                    }
                }
            }

            
            size -= nsize;
            return begin;
        }

        void pop_back() {
            --size;
        }
        const T& operator[](size_t pos) const;
        T& operator[](size_t pos) {
            if (pos <= size) {
                return *(pointer + pos);
            }

            else
                return *(pointer);//exception
       }

        void resize(size_t count) {

        }
        void reserve(size_t new_cap) {
            if (new_cap <= capacity) {
                return;
            }
            T* new_memory_vector = new T[new_cap];
            capacity = new_cap;
            for (decltype(size) i = 0; i < size; ++i) {
                new_memory_vector[i] = pointer[i];
            }
            delete[] pointer;
            pointer = new_memory_vector;
        }



private:
    size_t size{ 0 };
    size_t capacity{ 0 };
    T* pointer ;

};

template<
    class T,
    class Container = Vector<T>
> class stack {
public:

    stack()  {}
    stack(size_t size) {
        Container.reserve(size);
    }
    template<class T1>
    stack(std::initializer_list<T1> value) {
        for (const T& ob : value) {
            Container.push_back(ob);
        }
    }

    stack(const stack& copy) {
        this->Container = copy.Container;
    }
    stack(stack&& move) {
        this->Container = std::move(move.Container);
    }

    stack& operator=(const stack& copy) {
    }
    stack& operator=( stack&& move)noexcept {
        this->Container = std::move(move.Container);
        return *this;
    }

    void push(T val) {
        Container.push_back(val);
    }
    T pop() {
       return (Container.erase(Container.end()));
    }
    T back() {
        return Container.back();
    }
    size_t size() {
        return Container.size();
    }
    bool empty() {
            return Container.empty_();
    
    }
      
private:
 
    Vector<T> Container{0};
};



class debug {
public:
    debug() { std::cout << "debug"<<std::endl; }
    ~debug() { std::cout << "~debug " << std::endl; }
    debug(int value) { std::cout << "debug int" << std::endl; }
    debug(const debug&) { std::cout << "debug const debug&" << std::endl; }
    debug(debug&&)noexcept { std::cout << "debug const debug&&" << std::endl; }
    debug& operator =(const debug&) { std::cout << " == const debug&" << std::endl; return *this; }
    debug& operator =(debug&&)noexcept { std::cout << " ==const debug&&" << std::endl; return *this; }
};

int main()
{
}