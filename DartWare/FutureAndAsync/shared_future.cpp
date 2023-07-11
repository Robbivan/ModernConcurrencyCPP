#include <iostream>
#include <thread>
#include <chrono>
#include <future>


using namespace std;


int32_t generate_value(const int32_t delay){

    for (int i = 0; i < 100; ++i) {
        cout<<".";
        this_thread::sleep_for(chrono::milliseconds(10));


    }
    srand(time(nullptr));
    return rand()%numeric_limits<int32_t>::max();
}


void value_processing(shared_future<int32_t> simple_future){
    cout << "Begin val processing" << endl;
    int32_t value = simple_future.get();

    cout << value << "val"<< endl;
    cout << "End val processing" << endl;
}

void save_value_to_file(shared_future<int32_t> simple_future){
    cout << "Begin val saving" << endl;
    int32_t value = simple_future.get(); // так как shared_future, то можно вызывать несколько раз

    cout << value << "val"<< endl;
    cout << "End val saving" << endl;
}

int main(){

    int32_t value;

    // 2 режима async и deffered
    // по умолчанию само выбирает (обычно async)
    shared_future<int32_t> simple_future = async(launch::async,generate_value, 10);
    // async вызывается мгновенно при создании simple_future
    // deffered откладывает запуск до get

    thread processing_thread(value_processing, simple_future);
    thread save_thread(save_value_to_file,simple_future);

    processing_thread.join();
    save_thread.join();


    return EXIT_SUCCESS;
}
