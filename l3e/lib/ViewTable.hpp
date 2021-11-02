#include <iostream>
#ifndef LAB3_VIEW_TABLE_H
#define LAB3_VIEW_TABLE_H

namespace Table{
    struct TableElement{
        bool busy;
        int key;

        char *value;

        TableElement():busy(false), key(0), value(nullptr){} //

        friend std::ostream& operator <<(std::ostream& cout, const TableElement &el);
    };

    class ViewedTable{
    private:
        size_t currentSize;//
        size_t capacity;   //+2
        TableElement *elements;


    public:
        ViewedTable() :currentSize(0), capacity(0), elements(nullptr) {};

        explicit ViewedTable(TableElement *elements, size_t count = 1)
            : currentSize(0), capacity(0), elements(nullptr)
                { add(elements, count); }

        ViewedTable(int *keys, const char **values, size_t count)
            : currentSize(0), capacity(0), elements(nullptr)
                { add(keys, values, count); }

        ViewedTable(const ViewedTable &tab)
            : currentSize(0), capacity(0), elements(nullptr)
                { if (tab.currentSize) add(tab.elements, tab.currentSize);};

        ViewedTable(ViewedTable &&tab) noexcept
            : currentSize(tab.currentSize), capacity(tab.capacity), elements(tab.elements)
                { tab.elements = nullptr; tab.currentSize = 0; };

        ViewedTable& operator =(const ViewedTable &tab);
        ViewedTable& operator =(ViewedTable &&tab) noexcept ;

        ~ViewedTable(){
            for(int i = 0; i < currentSize; ++i)
                delete[] elements[i].value;
            delete[] elements;
        };

        [[nodiscard]] size_t size() const { return currentSize; };
        [[nodiscard]] size_t maxSize() const { return capacity; };

        ViewedTable& add(const TableElement *el, size_t count = 1);
        ViewedTable& add(const int *keys, const char **values, size_t count);
        ViewedTable& add(int key, const char *value);

        [[nodiscard]] const TableElement *find(int key) const;
        [[nodiscard]] const TableElement& getItem(int key) const;
        [[nodiscard]] const char *getValue(int key) const;

        void remove(int key);
        void garbageCollect(size_t freeSpaceCount = 0);

        std::istream& in(std::istream& cin, bool prompt = false);
        std::ostream& out(std::ostream& cout) const;
        std::ostream& out(std::ostream& cout, int key) const;

        const TableElement& operator [](int key) const;
        ViewedTable operator !() const; // задание: после выполнения вернуть копию объекта после вызова garbageCollect()

        friend std::istream& operator >>(std::istream& cin, ViewedTable& tab);
        friend std::ostream& operator <<(std::ostream& cout, const ViewedTable& tab);
    };
}

#endif
