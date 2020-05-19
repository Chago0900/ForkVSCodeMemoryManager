#include <typeinfo>
#include <ostream>
#include <iostream>
#include <cstring>
#include <utility>
#include <thread>


using namespace std;

template <typename T>
class VSPtr : public MyObject {

private:

    T* attribute;

public:

    T& operator *() {
        return *attribute;
    }; 

    /*T& operator &() {
        return &attribute;
    };*/

    //Copy assignment operator
    VSPtr<T>& operator =(const VSPtr<T>& copy) {
        if (this != &copy){
            delete attribute;
            attribute = nullptr;
            attribute = copy.attribute;
            
        }
        return *this;
    }; 

    //Move assignment operator
    VSPtr<T>& operator =(const VSPtr<T>&& copy){
        if (&copy != this){
            delete attribute;
            attribute = copy.attribute;
            copy.attribute = nullptr;
        }
        return *this;
    }

    //Constructor
    explicit VSPtr<T>(){ 
        attribute = nullptr;
        attribute = new T();
    };

    //Copy Constructor
    VSPtr<T>(const VSPtr<T>& copy){
        attribute = copy.attribute;

    };

    //Move constructor
    VSPtr<T>(const VSPtr<T>&& copy) {
        attribute = copy.attribute;
        copy.attribute = nullptr;
    }

    //Destructor
    void Destructor(){ 
        SingletonGarbageCollector &Collector = SingletonGarbageCollector::getInstance();
        Collector.deleteObject(this->id);
        this->attribute = nullptr;
        delete attribute;
    };

    static VSPtr<T>& New(){
        SingletonGarbageCollector &Collector = SingletonGarbageCollector::getInstance();
        VSPtr<T> *tmp = new VSPtr<T>();
        Collector.addObject(tmp);
        return *tmp;
    };

    void Delete(){
        //~VSPtr<T>();
        this->Destructor();
    }

    int getId(){
        return id;
    }

};