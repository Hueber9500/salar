#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
using namespace std;

const int initialCapacity = 2;
const char* fileName="./data.txt";

struct Array
{
    public:
        int* list;
        int length;
        int capacity;
    
    // Constructor Deconstructor
    public:
        Array()
        {
            length = 0;
            capacity = initialCapacity;
            list = new int[capacity];
        }

        ~Array()
        {
            cout<<"Deconstructor"<<endl;

            clearMemory();    
        }

    public:
        void add(int element)
        {
            /// Resize array capacity
            if(length == capacity)
            {
                resize();
            }

            list[length++] = element;
        }

        void clearMemory()
        {
            if(list != nullptr)
            {
                delete[] list;
                list = nullptr;
                length = 0;
            }
        }

    private:
        void resize()
        {
            int newCapacity = static_cast<int>(capacity * 1.5);
            int* newList = new int[newCapacity];

            for(int i = 0; i < length; i++)
            {
                newList[i] = list[i];
            }

            capacity = newCapacity;
            delete[] list;
            list = newList;
            newList = nullptr;
        }
};


void readArraysFromFile(Array* &p1, Array* &p2)
{
    std::ifstream input(fileName);
    std::string line;
    Array** arr[] = {&p1, &p2};

    for(int i = 0; i < 2; i++)
    {
        Array** pArr = arr[i];
        *pArr = new Array;
        getline(input, line);
        istringstream iss(line);

        int element;
        while(iss >> element)
        {
            (*pArr)->add(element);
        }
    }

    input.close();
}

void writeDataToFile(const Array& arr1, const Array& arr2)
{
    const Array* arr[] = {&arr1, &arr2};
    std::ofstream output(fileName, ios::out | ios::trunc);

    for(int i = 0; i < 2; i++)
    {
        const Array* pArr = arr[i];
        for(int j = 0; j < pArr->length; j++)
        {
            output << pArr->list[j] << " ";
        }
        output << endl;
    }
}

int main()
{
    Array p1;
    p1.add(100);
    p1.add(200);

    writeDataToFile(p1, p1);
}