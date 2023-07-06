#include <iostream>
#include <thread>
#include <chrono>

using namespace std;



// Race condition
// так как нет атомарности
namespace Bad_decision{
    // Неопределенное поведение UB
    void print_count(int32_t& counter){
        cout<<"Counter "<<counter<<endl;
        ++counter;
    }
}
///////// Исправляем
namespace Not_Good_decision{
    bool is_worked;

    void print_count(int32_t& counter){

        while (is_worked){
        }

        is_worked = true;


        cout<<"Counter "<<counter<<endl;
        ++counter;

        is_worked = false;
    }
}

/////


namespace Good_decision{
//    mutex simple_mutex; //лучше не создавать глобальную переменную

    void print_count(int32_t& counter, mutex& simple_mutex){ //mutex только по ссылке, так как нереализована
        // семантика копирования
        simple_mutex.lock();

        cout<<"Counter "<<counter<<endl;
        ++counter;
        // throw мб, то есть придется оборачивать в try catch

        simple_mutex.unlock(); //можно легко забыть
    }
}

//////

namespace Best_decision{
    void print_count(int32_t& counter, mutex& simple_mutex){ //mutex только по ссылке, так как нереализована
        // семантика копирования
        lock_guard<mutex> lockGuard(simple_mutex);

        cout<<"Counter "<<counter<<endl;
        ++counter;


    }
}


//// хотим больше контроля, когда нужно ограничить mutex


namespace More_control_decision{
    void print_count(int32_t& counter, mutex& simple_mutex){ //mutex только по ссылке, так как нереализована
        // семантика копирования
        unique_lock<mutex> lockGuard(simple_mutex,defer_lock); // unique lock может нарушать единственность lock, через
        // добавление defer_lock, после этого будет работать lockGuard.lock();

        // тут долго ждем
        this_thread::sleep_for(chrono::seconds(3));

        lockGuard.lock();
//      lockGuard.try_lock(); в отличие от простого lock возращает статус bool: удача или неудача
//      используется для while(!lockGuard.try_lock()){}
//      метод mutex() возвращает указатель на mutex

        cout<<"Counter "<<counter<<endl;
        ++counter;

        lockGuard.unlock();
        this_thread::sleep_for(chrono::seconds(2));

    }
}

int main(){
    chrono::time_point<chrono::steady_clock> start;
    chrono::time_point<chrono::steady_clock> end;

    chrono::duration<float> duration;

    start = chrono::high_resolution_clock::now();





    int32_t counter = 0;


    mutex simple_mutex;

    std::thread first_thread(More_control_decision::print_count, ref(counter), ref(simple_mutex));
    std::thread second_thread(More_control_decision::print_count, ref(counter),ref(simple_mutex));
    std::thread third_thread(More_control_decision::print_count, ref(counter),ref(simple_mutex));

    first_thread.join();
    second_thread.join();
    third_thread.join();


    end = chrono::high_resolution_clock::now();

    duration = end - start;

    cout<<duration.count()<<endl;
//    print_count(counter);

    return EXIT_SUCCESS;
}
