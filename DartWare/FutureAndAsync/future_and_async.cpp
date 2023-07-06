#include <iostream>
#include <thread>
#include <chrono>
#include "future"


using namespace std;


void generate_value(const int32_t delay){

    for (int i = 0; i < 100; ++i) {
        cout<<".";
        this_thread::sleep_for(chrono::milliseconds(10));

        
    }
    srand(time(nullptr));
    return rand()%numeric_limits<int32_t>::max();
}

int main(){

    int32_t value;


    generate_value();

    // 2 режима async и deffered
    // по умолчанию само выбирает (обычно async)
    future<void> simple_future = async(launch::async,generate_value, 10);
    // async вызывается мгновенно при создании simple_future
    // deffered откладывает запуск до get


    for (int i = 0; i < 100; ++i) {
        cout<<"_";
        this_thread::sleep_for(chrono::milliseconds(10));


    }

    // возвращает класс future

    // надо синхронизировать с главным потоком, который быстрее
    // надо чтобы он ждал
    simple_future.wait();
//    simple_future.wait_for(chrono::milliseconds(10));
//    simple_future.wait_until(chrono::high_resolution::now()+chrono::milliseconds(10));



    cout<<"Value: "<<value<<endl;

    return EXIT_SUCCESS;
}
