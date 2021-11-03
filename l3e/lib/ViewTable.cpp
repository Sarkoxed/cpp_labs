//    This is a personal academic project. Dear PVS-Studio, please check it.
//
//    PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <stdexcept>
#include <iostream>
#include <cstring>
#include <limits>

#include "ViewTable.hpp"

namespace Table{
    ViewedTable& ViewedTable::add(const TableElement *elementsArray, size_t count) {
        if (currentSize + count > capacity){
            size_t busyCount = 0;

            for (int i = 0; i < count; ++i)
                if (elementsArray[i].busy)
                    ++busyCount;

            garbageCollect(capacity + busyCount);
        }

        for (int i = 0; i < count; ++i) {
            if (elementsArray[i].busy)
                add(elementsArray[i].key, elementsArray[i].value); //changes current size!
        }

        return *this;
    }

    ViewedTable& ViewedTable::add(const int *keys, const char **values, size_t count) {
        if (currentSize + count > capacity) garbageCollect(capacity + count);

        for (int i = 0; i < count; ++i) {
            add(keys[i], values[i]);
        }

        return *this;
    }


    ViewedTable& ViewedTable::add(int key, const char *value) {
        //if (find(key)) throw std::runtime_error("Key duplicate in table");

        if (currentSize == capacity){
            garbageCollect(capacity + 1);
        }

        elements[currentSize].busy = true;
        elements[currentSize].key = key;

        size_t len = strlen(value);

        elements[currentSize].value = new char[len + 1];
        std::copy(value, value + len + 1, elements[currentSize].value);

        ++currentSize;

        return *this;
    }

    const TableElement *ViewedTable::find(int key) const{
        for (int i = 0; i < currentSize; ++i){
            if (elements[i].busy && elements[i].key == key) return &elements[i];
        }

        return nullptr;
    }

    [[nodiscard]] const TableElement& ViewedTable::getItem(int key) const{
        for (int i = 0; i < currentSize; ++i){
            if (elements[i].busy && elements[i].key == key) return elements[i];
        }

        throw std::runtime_error("Element not found");
    }

    const char *ViewedTable::getValue(int key) const{
        const TableElement *el = find(key);

        if (el) return el->value;
        else return nullptr;
    }

    void ViewedTable::remove(int key) {
        TableElement *el = nullptr;

        for (int i = 0; i < currentSize; ++i){
            if (elements[i].busy && elements[i].key == key) {
                el = &elements[i];
                break;
            }
        }

        if (el) {
            el->busy = false;
            delete[] el->value;
            el->value = nullptr;
        } else throw std::runtime_error("Unable to remove from table: key not found");
    }

    void ViewedTable::garbageCollect(size_t freeSpaceCount) {
        int busyCount = 0;
        size_t newSize = 0;

        for (int current = 0; current < currentSize; ++current)
            if (elements[current].busy) ++busyCount;

        auto *newElements = new TableElement[busyCount + freeSpaceCount];
        capacity = busyCount + freeSpaceCount;

        for (int current = 0; current < currentSize; ++current) {
            if (elements[current].busy) {
                newElements[newSize] = elements[current];
                ++newSize;
            }
        }

        delete[] elements;

        elements = newElements;
        currentSize = newSize;
    }


    std::istream& ViewedTable::in(std::istream &cin, bool prompt) {
        int key;

        if (prompt) std::cout << "Enter key: ";

        cin >> key;

        if (prompt) std::cout << "Enter value: ";

        cin >> std::ws;

        char buf[80];
        char *str = nullptr;

        size_t len = 0;
        std::streamsize readCount;

        do{
            cin.get(buf, sizeof buf);

            readCount = cin.gcount();

            if (cin.eof()){
                readCount = 0;
            }

            if (readCount > 0){
                char *newStr = new char[len + readCount + 1];
                std::copy(str, str + len, newStr);
                delete[] str;

                str = newStr;

                std::copy(buf, buf + readCount, str + len);
                len += readCount;
            } else {
                cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                cin.clear();
            }
        } while (readCount > 0);

        if (str) {
            str[len] = '\0';
        } else {
            str = new char[1] {'\0'};
        }

        if (cin.good()) {
            try {
                add(key, str);
            } catch (const std::runtime_error &ex){
                cin.setstate(std::ios::failbit);
            }
        }

        delete[] str;

        return cin;
    }

    std::ostream& ViewedTable::out(std::ostream& cout) const{
        cout << "Table of " << currentSize << " elements" << std::endl;

        for (int i = 0; i < currentSize; ++i) {
            if (elements[i].busy)
                cout << "key=" << elements[i].key << ", value=" << elements[i].value << std::endl;
        }


        return cout;
    }

    std::ostream& ViewedTable::out(std::ostream& cout, int key) const{
        const TableElement *el = find(key);

        if (el){
            cout << "key=" << el->key << ", value=" << el->value << std::endl;

        } else {
            cout << "Element not found" << std::endl;
        }

        return cout;
    }

    const TableElement& ViewedTable::operator [](int key) const{
        return getItem(key);
    }

    // задание: после выполнения вернуть киопию объекта после вызова garbageCollect()
    ViewedTable ViewedTable::operator !() const {
        ViewedTable tab(*this);
        tab.garbageCollect();

        return tab;
    }

    std::istream& operator >>(std::istream& cin, ViewedTable& tab){
        return tab.in(cin, true);
    }

    std::ostream& operator <<(std::ostream& cout, const ViewedTable& tab){
        return tab.out(cout);
    }

    std::ostream& operator <<(std::ostream& cout, const TableElement &el){
        cout << "busy=" << el.busy << ", key=" << el.key << ", value=" << el.value << std::endl;

        return cout;
    }

    ViewedTable& ViewedTable::operator =(const ViewedTable &tab){
        if (this != &tab) {
            delete[] elements;
            elements = nullptr;
            currentSize = 0;

            if (tab.currentSize){
                add(tab.elements, tab.currentSize);
            }
        }

        return *this;
    }

    ViewedTable& ViewedTable::operator =(ViewedTable &&tab) noexcept{
        std::swap(currentSize, tab.currentSize);
        std::swap(elements, tab.elements);

        return *this;
    }
}
