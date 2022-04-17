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

        void print()
        {
            for(int i = 0; i < length ; i++)
            {
                cout<<this->list[i]<< " ";
            }

            cout<<endl;
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

void readArraysFromFile(Array& p1, Array& p2)
{
    std::ifstream input(fileName);
    std::string line;
    Array* arr[] = {&p1, &p2};

    for(int i = 0; i < 2; i++)
    {
        getline(input, line);
        istringstream iss(line);

        int element;
        while(iss >> element)
        {
            arr[i]->add(element);
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

void shellSort(Array& array)
{
    for (int gap = array.length/2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < array.length; i += 1)
        {
            int temp = array.list[i];
 
            int j;           
            for (j = i; j >= gap && array.list[j - gap] > temp; j -= gap)
                array.list[j] = array.list[j - gap];
            
            array.list[j] = temp;
        }
    }
}

void showMenu()
{
    cout << "Izberete:"<<endl;
    cout << "1. Procheti danni ot fail."<<endl;
    cout << "2. Zapis na danni vuv fail." << endl;
    cout << "3. Sortirane na po metoda na Shell." << endl;
    cout << "4. Printirane na spisucite." << endl;
    cout << "Izberete q za izhod." << endl;

}

int main()
{
    Array p1;
    Array p2;

    showMenu();
    char input;
    cin>>input;

    while(input != 'q' && input != 'Q')
    {
        switch( input )
        {
            case '1' : 
            {
                readArraysFromFile(p1, p2);
                break;
            }
            case '2' : 
            {
                writeDataToFile(p1, p2);
                break;
            }
            case '3' :
            {
                shellSort(p1);
                shellSort(p2);
                break;
            }
            case '4':
            {
                p1.print();
                p2.print();
                break;
            }
            default: 
            {
                cout<<"Vuvedete validna opciq ot 1 do 4"<<endl;
                break;
            }
        }

        cin >> input;
        showMenu();
    }
}