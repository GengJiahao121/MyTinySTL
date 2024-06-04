

#include <list>

int main(int argc, char *argv[]){
    std::list<int> myList;

    myList.push_front(1);
    myList.push_back(2);

    myList.pop_front();
    myList.pop_back();

    myList.end();

    // ... 
}