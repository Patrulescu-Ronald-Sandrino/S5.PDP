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
    auto updateFinished = [&i](){ finished = i >= min(v1.size(), v2.size()); };

    updateFinished();
    while (!finished) {
        unique_lock<mutex> lock(mtx);

        result = v1[i] * v2[i];
        ready = true;

        i++;
        updateFinished();

        lock.unlock();
        cv.notify_one();
    }
}

void consumerWorker() {
    int sum = 0;

    unique_lock<mutex> lock(mtx);
    while (!finished) {
        while (!ready) {
            cv.wait(lock);
        }
        sum += result;
        printf("Consuming %d, sum is now %d\n", result, sum);
    }
//    lock.unlock(); // TODO: maybe this isn't necessary OR it may lead to problems
    printf("Final sum is %d\n", sum);
}


int main() {
    srand(time(nullptr));
    
    v1 = generateRandomVector(VECTOR_SIZE);
    v2 = generateRandomVector(VECTOR_SIZE);

    printVector(v1);
    printVector(v2);

    thread consumerThread(&consumerWorker);
    thread producerThread(&producerWorker);

    consumerThread.join();
    producerThread.join();

    return 0;
}
