#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

struct Chopstics
{
public:
    std::mutex mu;
};

void start()
{
    printf("\n\n*******************************************************************\n");
    printf("\t\t\tDINNING PHILOSOPHER PROBLEM\n");
    printf("*******************************************************************\n");
}

void eat(Chopstics &left_chopstics, Chopstics &right_chopstics, int philosopher_number)
{
    // Lock is applied to left stic and right stic when philosopher enters
    // now if another philosopher trys to take that stic than that philosopher
    // have to wait until lock is free
    unique_lock<mutex> llock(left_chopstics.mu);
    unique_lock<mutex> rlock(right_chopstics.mu);

    cout << "Philosopher " << philosopher_number << " is eating" << endl;

    chrono::milliseconds timeout(1500);
    this_thread::sleep_for(timeout);

    cout << "Philosopher " << philosopher_number << " has finished eating" << endl;
}

int main()
{
    start();
    printf("--> Enter the number of philosophers :-- \n");
    printf("--> ");
    int no_of_philosophers = 20;
    cin >> no_of_philosophers;

    // create chopstics as the number of philosophers
    Chopstics chp[no_of_philosophers];

    // create philosophers i.e. created threads for each user
    thread philosopher[no_of_philosophers];

    // Philosophers Start reading
    cout << "Philosopher " << (0 + 1) << " is reading..." << endl;

    // Index 0 means first chopstic and no_of_philosophers - 1 means last chopstic
    philosopher[0] = thread(eat, ref(chp[0]), ref(chp[no_of_philosophers - 1]), (0 + 1));

    for (int i = 1; i < no_of_philosophers; ++i)
    {
        cout << "Philosopher " << (i + 1) << " is reading..." << endl;
        philosopher[i] = thread(eat, ref(chp[i]), ref(chp[i - 1]), (i + 1));
    }

    // Here treads are joined so that all threads will be executed before termination of the program
    for (auto &ph : philosopher)
    {
        ph.join();
    }

    printf("\n\n--> All philosophers have finished eating.\n");
    printf("\n PRESS ANY KEY TO END PROGRAM ...\n");
    char x;
    x = getchar();
    x = getchar();

    return 0;
}