//Question 3 - pointers

// There is a memory leak in the code below, where is it?, what class/solution can you use to fix it while ensuring that the object will be deleted only once and only when it's not used by any consumer
// Task: Modify the code to address the issues above. Please explain the changes you made and how they solve the memory allocation/deletion issue  

// Do not remove any function or change threads dispatching order - you can(and should) change the functions body/signature


////two main problems withthe code: 1)the payloadneed to be deleted, i tried to change the dispacher to return pointer to the payload but it didnt secssed so i created a pointer p for that.
////2) i created a mutex lock so that the code will end only after the opetarors will finish.

#include <chrono>
#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include <mutex>
#include <condition_variable>

std::mutex m;
std::condition_variable cv;

struct Payload {

    Payload(uint64_t id_) :
            id(id_),
            veryLargeVector(1000*1000)
    {}

    uint64_t id;
    std::vector<int> veryLargeVector;
};

Payload *p;
bool flags[2] = {false,false};

void operation1(Payload* payload) {
    std::cout << "Performing operation1 on payload " << payload->id << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5 + (std::rand() % (12 - 5 + 1))));  //Simulate some heavy work
    std::cout << "Operation2 Performed" << std::endl;
    flags[0] = true;
    cv.notify_one();
}

void operation2(Payload* payload) {
    std::cout << "Performing operation2 on payload "  << payload->id << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(std::chrono::seconds(5 + (std::rand() % (12 - 5 + 1)))));  //Simulate some heavy work
    std::cout << "Operation2 Performed" << std::endl;
    flags[1] = true;
    cv.notify_one();
}

void dispacher_thread() {
    Payload* payload = new Payload(1);
    std::this_thread::sleep_for(std::chrono::seconds(2));  //Simulate some heavy work
    std::thread wt1(&operation1, payload);
    std::thread wt2(&operation2, payload);
    //Waiting for wt1 & wt2 to finish is not allowed, dispacher_thread should exit after creating wt1 and wt2
    wt1.detach();
    wt2.detach();
    p =  *(&payload);
    cv.notify_all();
    //return &payload);
}

int main(int argc, char** argv)
{
    std::cout << "Calling dispatcher thread" << std::endl;
    std::thread t(&dispacher_thread);
    delete p;

    std::unique_lock<std::mutex> lck(m);                 //this thread waits until operation1 will finish computing "sum" and then will start the process
    while(flags[0] == false && flags[1] == false) cv.wait(lck) ;
    t.join();

    std::cout << "Press enter to exit" << std::endl;
    getchar();
    return 0;
}
