#include <iostream>
#include <thread>
#include <queue>
#include <random>
#include <mutex>
#include <condition_variable>




using namespace std;

const int32_t max_counter = 20;

queue<int32_t> collection;
mutex simple_mutex;

int32_t counter;

condition_variable condition;
// condition_variable_any - может работать со всеми mutex подобными классами


void prepare_data(){
    default_random_engine random_engine(rand()%10);
    uniform_int_distribution<int32_t> int_distribution(10,1000);
    int32_t value = int_distribution(random_engine);
    unique_lock<mutex> lock(simple_mutex);

    collection.push(value);
    condition.notify_one(); // если больше 1 потока notify_all


    this_thread::sleep_for(chrono::milliseconds(value));
    lock.unlock();

    ++counter;

    if(counter >= max_counter){
        return;
    }

    prepare_data();



}

void extract_data(){
//    // непотокобезопасно
//    while (collection.empty()){
//    }


    unique_lock<mutex>lock(simple_mutex);

    condition.wait(lock, []{
        return !collection.empty();
    })
//    condition.wait_for(lock,chrono::milliseconds(1000), []{
//        return !collection.empty();
//    })
    condition.wait_until(lock,chrono::high_resolution_clock::now()+chrono::milliseconds(1000), []{
        return !collection.empty();
    })

    cout << "Value: " << collection.back();

    collection.pop();
    lock.unlock();


    if(counter >= max_counter){
        return;
    }
    extract_data();
}

int main(){

    thread prepare_thread(prepare_data);
    thread extract_thread(extract_data);

    prepare_thread.join();
    extract_thread.join();

    return EXIT_SUCCESS;
}
