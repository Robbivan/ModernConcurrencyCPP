#include <iostream>
#include <thread>
#include <chrono>
#include <future>

using namespace std;

int32_t any_task(const int32_t delay){

    cout << "Begin task" << endl;

    for (int i = 0; i < 100; ++i) {
        cout<<".";
        this_thread::sleep_for(chrono::milliseconds(10));
        
    }

    cout<< endl;

    cout << "End task" <<endl;

    return 10;

}

int main(){
    packaged_task<int32_t (const int32_t)>task(any_task);

    future<int32_t> simple_future = task.get_future();
    thread task_thread(ref(task),10);

//    task(10); // функтор

    int32_t result = simple_future.get();

    task_thread.join();


    return EXIT_SUCCESS;
}