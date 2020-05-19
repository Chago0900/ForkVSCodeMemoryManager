#include <iostream>
#include <ostream>
#include "SingletonGarbageCollector.h"
#include "VSPtr.h"
#include <thread>
#include <pthread.h>


using namespace std;

int main(int argc, char *argv[]) {

	
	VSPtr<int> myPtr = VSPtr<int>::New();
	*myPtr = 5;
	cout << "*Ptr: " << *myPtr << endl;
	cout << "&Ptr: " << &myPtr << endl;
	cout << "Ptr->id: " << myPtr.getId() << endl;

	VSPtr<int> myPtr2 = VSPtr<int>::New();
	*myPtr2 = 7;
	VSPtr<int> myPtr3 = VSPtr<int>::New();
	*myPtr3 = 5;
	VSPtr<int> myPtr4 = VSPtr<int>::New();
	*myPtr4 = 8;
	VSPtr<int> myPtr5 = VSPtr<int>::New();
	*myPtr5 = 10;

	cout << "*Ptr2: " << *myPtr2 << endl;
	cout << "&Ptr2: " << &myPtr2 << endl;
	cout << "Ptr2->id: " << myPtr2.getId() << endl;

	cout << "\n Before GC action: " << endl;
	SingletonGarbageCollector &collector = SingletonGarbageCollector::getInstance();
	collector.garbageCollection();

	collector.deleteObject(5);

	cout << "\n After GC action: " << endl;
	thread th2(SingletonGarbageCollector::garbageCollection);

	th2.join();
}