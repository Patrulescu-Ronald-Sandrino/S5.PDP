#include <iostream>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;


#define VECTOR_SIZE 10
#define MAX_NUM 10


mutex mtx;
bool ready = false;
bool finished = false;
condition_variable cv;
int result;
vector<int> v1;
vector<int> v2;


//region utils
vector<int> generateRandomVector(int size) {
    vector<int> v;

    for (int i = 0; i < size; ++i) {
        v.push_back(rand() % MAX_NUM);
    }

    return v;
}

void printVector(const vector<int> &v) {
    for (const auto &item: v) {
        cout << item << " ";
    }

    cout << "\n";
}
//endregion


void producerWorker() {
    int i = 0;
    bool looping = true;

    while (looping) {
        std::this_thread::sleep_for(0.01s);
        unique_lock<mutex> lock(mtx);

        result = i < min(v1.size(), v2.size()) ? v1[i] * v2[i] : -1;
        looping = result == -1;
        ready = true;

//        if (result == -1) {
//            lock.unlock();
//            cv.notify_one();
//            break;
//        }

        i++;

        lock.unlock();
        cv.notify_one();

        lock.lock();
        cv.wait(lock, [](){ return !ready; });
    }
}

void consumerWorker() {
    int sum = 0;

    while (!finished) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [](){ return ready; });

        if (result == -1) {
            lock.unlock();
            cv.notify_one();
            break;
        }

        sum += result;
        printf("Consuming %d, sum is now %d\n", result, sum);
        ready = false;
        lock.unlock();
        cv.notify_one();
    }
    printf("Final sum is %d\n", sum);
}


int main() {
    srand(time(nullptr));
    
    v1 = generateRandomVector(VECTOR_SIZE);
    v2 = generateRandomVector(VECTOR_SIZE);

    printVector(v1);
    printVector(v2);

    vector<thread> threads;
    threads.emplace_back(&consumerWorker);
    threads.emplace_back(&producerWorker);

    for (auto &item: threads) {
        item.join();
    }

    return 0;
}
