#include <iostream>
#include <thread>

using namespace std;

// ВАЖНО тип recursive_mutex
void print_count(int32_t& counter, recursive_mutex& simple_mutex){ //mutex только по ссылке, так как нереализована
    unique_lock<recursive_mutex> lockGuard(simple_mutex);

    cout<<"Counter "<<counter<<endl;
    ++counter;

    if(counter >=15){
        return;
    }
    print_count(counter,simple_mutex);
}
int main(){
    int32_t counter = 0;

    recursive_mutex simple_mutex;

    std::thread first_thread(print_count, ref(counter), ref(simple_mutex));

    first_thread.join();

    return EXIT_SUCCESS;
}