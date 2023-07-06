#include <iostream>
#include <thread>

// класс thread это всегда move, копирования нет

// ЛУЧШЕ ПЕРЕДАВАТЬ ПО возможности ПО ЗНАЧЕНИЮ const std::vector<int32_t> collection
// далее представлено объяснение
int32_t process(const std::vector<int32_t>& collection){
    // более длительное по времени, поэтому гарантируется, что этот поток закончиться позже главного

    srand(time(nullptr));

    for (const auto& item:collection){
        std::this_thread::sleep_for(std::chrono::microseconds(10));

        std::cout<<item<<std::endl;

        std::cout<<std::this_thread::get_id()<<std::endl;

        if(item < 0){
            throw std::exception("Must be > 0");
        }
    }
    return rand()%1000;
};

int32_t main(){

    std::vector<int32_t> v{2,5,78,94,22,1,6,79,3};

    int32_t result;
    std::thread simple_thread([v,&result](){
        result = process(v);

    })
//    std::thread simple_thread(process,std::ref(v));// передача параметра функции
    // можно использовать lambda func

    // ВАЖНО по ссылке только через ref можно поток передавать
    // Но вообще не очень безопасно передавать по ссылке в многопоточности, так как
    // в ходе исполнения потока мб в оригинале изменение, влияющая на ход действия потока



    for(int32_t item: {1,2,3,8,4,5}){
        std::cout<<item<<std::endl;

        std::this_thread::sleep_for(std::chrono::microseconds(10));

        std::cout<< std::this_thread::get_id()<<std::endl;;

        // Такой код вызывет exception, поэтому лучше передавать по значению
//        if(item == 8){
//          v[7] = -1;
//        }
    }


    for (int i = 0; i < 100; ++i) {

    }

    // сообщаем главному потоку, что необходимо дождаться другого потока
    simple_thread.join();// месторасположение важно (поток process дольше по времени)


    // можно вызвать только один метод
    if(!simple_thread.joinable()){
        std::cout<<"уже был вызван ранее, поэтому больше нельзя";
    }
    return EXIT_SUCCESS;
}
