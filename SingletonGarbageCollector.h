#include <iostream>
#include <thread>
#include <pthread.h>
#include <chrono>
#include "BinaryTree.h"


using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds

//It's a thread function
class SingletonGarbageCollector {

public:
    static SingletonGarbageCollector& getInstance(){
        static SingletonGarbageCollector instance;
        return instance;
    }

private:
    //int totalNodes;
    BinaryTree *memoryCollectionTree;

    SingletonGarbageCollector(){
        //totalNodes = 0;
        memoryCollectionTree = new BinaryTree();
    }

    ~SingletonGarbageCollector() = default;

    SingletonGarbageCollector(const SingletonGarbageCollector&) = delete;
    SingletonGarbageCollector& operator=(const SingletonGarbageCollector&) = delete;


public:

    void addObject(MyObject* node){
        memoryCollectionTree->totalNodes +=1;
        node->id = memoryCollectionTree->totalNodes;
        getInstance().memoryCollectionTree->insertNode(node->id, node);
    }

    void deleteObject(int idToDelete){
        getInstance().memoryCollectionTree->deleteNode(idToDelete);
    }

    /**
     * Mark phase.
     */
    void mark() {
        getInstance().memoryCollectionTree->traverseInOrder(true);
    }

    /**
     * Sweep phase.
     * */
    void sweep(){
        getInstance().memoryCollectionTree->traverseInOrder(false);
    }

    
    static void garbageCollection(){
        for (int i =0; i<10; i++){
            cout << "New GC action" << endl;
            getInstance().mark();
            getInstance().sweep();
            sleep_until(system_clock::now() + 1s);
        }
    }
};
