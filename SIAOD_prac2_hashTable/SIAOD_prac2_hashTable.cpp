#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <time.h>
#include <vector>
#include <sstream>
#include <chrono>
#include <windows.h>
#pragma warning(disable : 4996)
using namespace std;
static int CompareQuantity = 0;
struct Node
{
    Node* next;
    string founder;
    string name;
    int license_number;
    Node(int license_number, string name, string founder) : license_number(license_number), name(name), founder(founder), next(nullptr) {}
};
struct list
{
    Node* first;
    Node* last;
    list() : first(nullptr), last(nullptr) {}
    bool is_empty() {
        return first == nullptr;
    }
    void push_back(int license_number, string name, string founder) {
        Node* p = new Node(license_number, name, founder);
        if (is_empty()) {
            first = p;
            last = p;
            return;
        }
        last->next = p;
        last = p;
    }
    Node* find(int license_number)
    {
        Node* p = first;
        while (p != nullptr)
        {
            CompareQuantity++;
            if (p->license_number == license_number)
            {
                return p;
            }
            p = p->next;
        }
        return nullptr;
    }
    void remove_first() {
        if (is_empty()) return;
        Node* p = first;
        first = p->next;
        delete p;
    }
    void remove_last() {
        if (is_empty()) return;
        if (first == last) {
            remove_first();
            return;
        }
        Node* p = first;
        while (p->next != last) p = p->next;
        p->next = nullptr;
        delete last;
        last = p;
    }

    void remove(int license_number) {
        if (is_empty()) return;
        if (first->license_number == license_number) {
            remove_first();
            return;
        }
        else if (last->license_number == license_number) {
            remove_last();
            return;
        }
        Node* slow = first;
        Node* fast = first->next;
        while (fast && fast->license_number != license_number) {
            fast = fast->next;
            slow = slow->next;
        }
        if (!fast) {
            std::cout << "This element does not exist" << endl;
            return;
        }
        slow->next = fast->next;
        delete fast;
    }
    void print()
    {
        Node* p = first;
        if (is_empty()) return;
        while (p) { // p != nullptr
            if (p != nullptr)
            {
                std::cout << "|" << p->license_number << " " << p->name << " " << p->founder << "| ---> ";
                p = p->next;
            }
        }
        std::cout << endl;
    }
};
int hash_function(int key, int L)
{
    return key % L;
}
void extend_array(list*& array, int& size)
{
    list* newArray = new list[size * 2];
    for (int i = 0; i < size; i++)
    {
        newArray[i] = array[i];
    }
    delete[] array;
    array = newArray;
    size *= 2;
}
void rehash_function(list*& array, int& size)
{
    Node* p;
    Node* buf = nullptr;
    extend_array(array, size);
    for (int i = 0; i < size; i++)
    {
        p = nullptr;
        if (array[i].first != nullptr)
        {
            p = array[i].first;
        }
        while (p != nullptr)
        {
            if (i != hash_function(p->license_number,size))
            {
                array[(hash_function(p->license_number, size))].push_back(p->license_number, p->name, p->founder);
                buf = p->next;
                array[i].remove(p->license_number);
                p = buf;
            }
            else 
            {
                p = p->next;
            }
        }
    }
}
void remove_from_file(string path, int license_number)
{
    vector<std::string> vec;
    string str;
    ifstream fin;
    fin.open(path);
    if (fin.is_open())
    {
        while (!fin.eof())
        {
            getline(fin, str);
            vec.push_back(str);
        }
    }
    fin.close();
    for (int i = 0; i < vec.size(); i++)
    {
        string buf(vec[i].begin(), find(vec[i].begin(), vec[i].end(), ' '));
        if (stoi(buf) == license_number)
        {
            vec.erase(vec.begin() + i);
        }
    }
    ofstream fout;
    fout.open(path);
    if (fout.is_open())
    {
        for (int i = 0; i < vec.size(); i++)
        {
            if (i == vec.size() - 1)
            {
                fout << vec[i];
            }
            else
            {
                fout << vec[i] << endl;
            }
        }
    }
    fout.close();
}
void add_in_file(string path, string str)
{
    ofstream fout;
    fout.open(path, ios::app);
    if (fout.is_open())
    {
        fout << endl << str;
    }
    fout.close();
}
int main()
{
    string path = "C:\\Новая папка\\random_uinc.txt"; // путь к файлу myFile.txt
    ifstream fin;
    int hash_table_size = 10;
    float counter = 0;
    float k = 0;
    list* hash_table = new list[hash_table_size];
    int license_number;
    string name;
    string founder;
    int y = 0;
    fin.open(path);
    if (fin.is_open())
    {
        while (!fin.eof())
        {
            counter++;
            k = counter / hash_table_size;
            if (k > 2.5)
            {
                rehash_function(hash_table, hash_table_size);
            }
            getline(fin, name);
            char* str = new char[name.length() + 1];
            strcpy(str, name.c_str());
            char* pch = strtok(str, " ");
            do
            {
                switch (y)
                {
                case 0:
                    license_number = atoi(pch);
                    break;
                case 1:
                    name = pch;
                    break;
                case 2:
                    founder = pch;
                    break;
                default:
                    break;
                }
                y++;
                pch = strtok(NULL, " ");
            } while (pch != NULL);
            y = 0;
            hash_table[hash_function(license_number, hash_table_size)].push_back(license_number, name, founder);
        }
    }
    fin.close();
    int key;
    Node* example;
    clock_t start, end;
    double seconds;
    for (int i = 0; i < 1; i++)
    {
        cin >> license_number;
        key = hash_function(license_number, hash_table_size);
        auto start = chrono::high_resolution_clock::now();
        //int start = GetTickCount();
        //double start = clock();
        example = hash_table[key].find(license_number);
        //double end = clock();
        //int end = GetTickCount();
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
        std::cout << example->license_number << " " << example->name << " " << example->founder << " Search time: " << duration.count() <<" nanoseconds"<< endl;
    }
    //cout << "Input license number you want to delete: ";
    //cin >> license_number;
    //string ex;
    //remove_from_file(path, license_number);
    //cout << "Removal completed!" << endl << "Input note you want to add in file: ";
    //cin.ignore();
    //cin >> license_number >> name >> founder;
    //stringstream ss;
   // ss << license_number;
    //ex = ss.str() + " " + name + " " + founder;
    //add_in_file(path, ex);
    //cout << "Addition completed!" << endl;
   // hash_table[hash_function(license_number, hash_table_size)].push_back(license_number, name, founder);
    for (int i = 0; i < hash_table_size; i++)
    {
        std::cout << i << " ";
        if (hash_table[i].is_empty())
        {
            cout << endl;
        }
        hash_table[i].print();
    }
    //hash_table[hash_function(license_number, hash_table_size)].remove(license_number);
    for (int i = 0; i < hash_table_size; i++)
    {
        std::cout << i << " ";
        if (hash_table[i].is_empty())
        {
            cout << endl;
        }
        hash_table[i].print();
    }
    cout << CompareQuantity << "\n";
    return 0;
}