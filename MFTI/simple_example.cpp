#include <iostream>
#include <thread>


void foo(){
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void bar(){

    std::this_thread::sleep_for(std::chrono::seconds(1));
}
int main() {
    std::cout<<"starting first helper\n";
    std::thread helper1(foo);

    std::cout<<"starting second helper\n";
    std::thread helper2(bar);

    std::cout<<"waiting for helpers\n";

    // Есть всегда главный поток, он будет ждать поток 1 и поток 2
    helper1.join();
    helper2.join();

    std::cout<<"done!\n";


    //...
    return 0;
}
