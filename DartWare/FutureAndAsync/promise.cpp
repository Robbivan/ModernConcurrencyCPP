#include <iostream>
#include <thread>
#include <chrono>
#include <future>


//  int32_t value = simple_future.get(); //может возвращать исключения


using namespace std;


void generate_value(const int32_t delay, promise<int32_t>& simple_promise){

    for (int i = 0; i < 100; ++i) {
        cout<<".";
        this_thread::sleep_for(chrono::milliseconds(10));
    }
    srand(time(nullptr));

    this_thread::sleep_for(chrono::seconds(2));
    simple_promise.set_value(rand()%numeric_limits<int32_t>::max()); // установка в качестве результата

}


void value_processing(shared_future<int32_t> simple_future){
    cout << "Begin val processing" << endl;
    try{
        int32_t value = simple_future.get();

        cout << value << "val"<< endl;
    }catch(const exception& exception){
        cout<<exception.what()<<endl;
    }


    cout << "End val processing" << endl;
}

void save_value_to_file(shared_future<int32_t> simple_future){
    cout << "Begin val saving" << endl;
    try{
        int32_t value = simple_future.get(); //мо

        cout << value << "val"<< endl;
    }catch(const exception& exception){
        cout<<exception.what()<<endl;
    }
    cout << "End val saving" << endl;
}

int main(){

    int32_t value;

    promise<int32_t> simple_promise;

    // 2 режима async и deffered
    // по умолчанию само выбирает (обычно async)
    shared_future<int32_t> simple_future = simple_promise.get_future().share();
    // async вызывается мгновенно при создании simple_future
    // deffered откладывает запуск до get

    // придеться через thread делать async
    thread generate_thread(generate_value,10, ref(simple_promise));
    thread processing_thread(value_processing, simple_future);
    thread save_thread(save_value_to_file,simple_future);


    generate_thread.join();
    processing_thread.join();
    save_thread.join();


    return EXIT_SUCCESS;
}

