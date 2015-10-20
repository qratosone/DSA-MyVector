typedef int Rank;
#define DEFAULT_CAPACITY 3

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
template <typename T>class MyVector {
public:
    MyVector(int c = DEFAULT_CAPACITY) {
        _size = 0;
        _capacity = c;
        _elem = new T[_capacity];
    }


    MyVector(T const *A, Rank lo, Rank hi) {
        copyFrom(A, lo, hi);
    }
    MyVector(MyVector<T> const& V, Rank lo, Rank hi) {
        copyFrom(V._elem, lo, hi);
    }
    MyVector(MyVector<T> const& V) {
        copyFrom(V._elem, 0, V._size);
    }
    ~MyVector() { delete[] _elem; };

    void copyFrom(T const * A, Rank lo, Rank hi) {
        _elem = new T[_capacity = 2 * (hi - lo)];
        _size = 0;
        while (lo<hi)
        {
            _elem[_size++] = A[lo++];
        }
    };
    void expand() {
        if (_size < _capacity)return;
        if (_capacity < DEFAULT_CAPACITY)
        {
            _capacity = DEFAULT_CAPACITY;
        }
        T* oldElem = _elem;
        _capacity *= 2;
        _elem = new T[_capacity];
        for (int i = 0; i < _size; i++)
        {
            _elem[i] = oldElem[i];
        }
        delete oldElem;
    }
    void set(Rank i, T e) {
        _elem[i] = e;
    }
    Rank insert(Rank r, T const &e)
    {
        expand();
        for (int i = _size; i > r; i--)
        {
            _elem[i] = _elem[i - 1];
        }
        _elem[r] = e;
        _size++;
        return r;
    }
    Rank remove(Rank lo, Rank hi) {
        if (lo == hi)
        {
            return 0;
        }
        while (hi < _size)
        {
            _elem[lo++] = _elem[hi++];
        }
        _size = lo;
        return hi - lo;
    }
    Rank remove(Rank r) {
        T e = _elem[r];
        remove(r, r + 1);
        return e;
    }
    Rank find(T const & e, Rank lo, Rank hi) {
        for (Rank i = lo; i < hi; i++)
        {
            if (_elem[i] == e)
            {
                return i;
            }
        }
        return hi;
    }
    int deduplicate() {
        int oldsize = _size;
        for (Rank i = 1; i < _size; i++)
        {
            for (Rank j = 0; j < i; j++)
            {
                if (_elem[j] == _elem[i])
                {
                    remove(j);
                }
            }
        }

        return oldsize - _size;
    }

    Rank length() {
        return _size;
    }
    static void add(T& i) {
        i++;
    }
    void increase(MyVector<T> &V) {
        V.traverse(add);
    }
    int uniquify() {
        int oldsize = _size;
        int i = 0;
        while (i < _size - 1)
        {
            if (_elem[i] == _elem[i + 1])
            {
                remove(i + 1);
            }
            else
            {
                i++;
            }
        }
        return oldsize - _size;
    }
    int uniquifyImprove() {
        Rank i = 0, j = 0;
        while (++j < _size)
        {
            if (_elem[i] != _elem[j])
            {
                _elem[++i] = _elem[j];

            }
        }
        _size = ++i;
        return j - i;
    }
    Rank search(T const& e)
    {
        return (0 >= _size) ? -1 : search(e, 0, _size);
    }
    Rank search(T const & e, Rank lo, Rank hi) {
        return binSearch(_elem, e, lo, hi);
    }
    static Rank binSearch(T* A, T const&e, Rank lo, Rank hi) {
        while (lo < hi)
        {
            Rank mi = lo + ((hi - lo) >> 1);
            if (e < A[mi]) {
                hi = mi;
            }
            else
            {
                lo = mi + 1;
            }
        }
        return --lo;
    }
    T lastvalue() {
        return _elem[_size - 1];
    }


    void bubbleSort(Rank lo, Rank hi) { while (!bubble(lo, hi--)); }
    void bubbleSort2(Rank lo, Rank hi) { while (lo < (hi = bubble2(lo, hi))); }
    void quickSort(T R[], Rank left, Rank right)
    {
        Rank i = left, j = right; T temp = R[i];
        while (i<j) {
            while ((R[j]>temp) && (j>i)) j = j - 1;
            if (j>i) { R[i] = R[j]; i = i + 1; }
            while ((R[i] <= temp) && (j>i)) i = i + 1;
            if (i<j) { R[j] = R[i]; j = j - 1; }
        }
        R[i] = temp;
        if (left<i - 1) quickSort(R, left, i - 1);
        if (i + 1<right) quickSort(R, i + 1, right);
    }
    void qSort() {
        quickSort(_elem, 0, _size - 1);
    }
    bool bubble(Rank lo, Rank hi) {
        bool sorted = true;
        while (++lo<hi)
        {
            if (_elem[lo - 1] > _elem[lo]) {
                sorted = false;
                swap(_elem[lo - 1], _elem[lo]);
            }
        }
        return sorted;
    }
    Rank bubble2(Rank lo, Rank hi) {
        Rank last = lo;
        while (++lo<hi)
        {
            if (_elem[lo - 1] > _elem[lo]) {
                last = lo;
                swap(_elem[lo - 1], _elem[lo]);
            }
        }
        return last;
    }
    void mergeSort(Rank lo, Rank hi) {
        if (hi - lo < 2) return; //单元素区间自然有序，否则...
        int mi = (lo + hi) / 2; //以中点为界
        mergeSort(lo, mi); mergeSort(mi, hi); //分别排序
        merge(lo, mi, hi); //归并
    }
    void show() {
        for (int i = 0; i < _size; i++)
        {
            std::cout << _elem[i] << " ";
        }
        std::cout << std::endl;
    }
    void merge(Rank lo, Rank mi, Rank hi) {
        T* A = _elem + lo; //合并后的向量A[0, hi - lo) = _elem[lo, hi)
        int lb = mi - lo; T* B = new T[lb]; //前子向量B[0, lb) = _elem[lo, mi)
        for (Rank i = 0; i < lb; B[i] = A[i++]); //复制前子向量
        int lc = hi - mi; T* C = _elem + mi; //后子向量C[0, lc) = _elem[mi, hi)
        for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc); ) { //B[j]和C[k]中的小者续至A末尾
            if ((j < lb) && (!(k < lc) || (B[j] <= C[k]))) A[i++] = B[j++];
            if ((k < lc) && (!(j < lb) || (C[k] <  B[j]))) A[i++] = C[k++];
        }
        delete[] B; //释放临时空间B
    }
    T & operator[](Rank r) const { return _elem[r]; };
    void swap(T &a, T &b) {
        T temp = 0;
        if (a > b)
        {
            temp = b;
            b = a;
            a = temp;
        }
    }
    T* getElem() {
        return _elem;
    }
    Rank getSize() { return _size; };
private:
    Rank _size;
    int _capacity;
    T* _elem;
};
