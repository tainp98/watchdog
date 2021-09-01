#ifndef WRAPPER_H
#define WRAPPER_H

template <typename T>
class Wrapper
{
public:
    Wrapper();

    template <typename T2>
    Wrapper<T2> next();
private:
    T objMonitor_;
};

template <typename T>
Wrapper<T>::Wrapper(){

}

template <typename T>
template <typename T2>
Wrapper<T2> Wrapper<T>::next(){
    return Wrapper<T2>();
}
#endif // WRAPPER_H
