typedef int Rank;
#define DEFAULT_CAPACITY 3
template <typename T>class MyVector
{
public:
	MyVector(int c = DEFAULT_CAPACITY){
		_size = 0;
		_capacity = c;
		_elem = new T[_capacity];
	}
	MyVector(T const *A,Rank lo,Rank hi){
		copyFrom(A, lo, hi);
	}
	MyVector(MyVector<T> const& V, Rank lo, Rank hi){
		copyFrom(V._elem, lo, hi);
	}
	MyVector(MyVector<T> const& V){
		copyFrom(V._elem, 0, V._size);
	}
	~MyVector(){ delete[] _elem; };
	void copyFrom(T const * A, Rank lo, Rank hi){
		_elem = new T[_capacity = 2 * (hi - lo)];
		_size = 0;
		for (int i = 0; i < (hi-lo); i++)
		{
			_elem[i] = A[lo];
			_size++;
			lo++;
		}
	};
	void expand(){
		if (_size < _capacity)return;
		if (_capacity<DEFAULT_CAPACITY)
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
	Rank insert(Rank r, T const &e)
	{
		expand();
		for (int i = _size; i >r; i--)
		{
			_elem[i] = _elem[i - 1];
		}
		_elem[r] = e;
		_size++;
		return r;
	}
	Rank remove(Rank lo, Rank hi){
		if (lo==hi)
		{
			return 0;
		}
		while (hi<_size)
		{
			_elem[lo++] = _elem[hi++];
		}
		_size = lo;
		return hi - lo;
	}
	Rank remove(Rank r){
		T e = _elem[r];
		remove(r, r + 1);
		return e;
	}
	Rank find(T const & e, Rank lo, Rank hi){
		for (Rank i = lo; i < hi; i++)
		{
			if (_elem[i]==e)
			{
				return i
			}
		}
		return hi;
	}
	int deduplicate(){
		int oldsize = _size;
		for (Rank i = 1; i < _size;i++)
		{
			for (Rank j = 0; j<i; j++)
			{
				if (_elem[j]==_elem[i])
				{
					remove(j);
				}
			}
		}
		
		return oldsize - _size;
	}
	void traverse(VST& visit){
		for (int i = 0; i < _size; i++)
		{
			visit(_elem[i]);
		}
	}
	void add(T& i){
		i++;
	}
	void increase(MyVector<T> &V){
		V.traverse(add);
	}
	int uniquify(){
		int oldsize = _size;
		int i = 0;
		while (i<_size-1)
		{
			if (_elem[i]==_elem[i+1])
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
	int uniquifyImprove(){
		Rank i = 0, j = 0;
		while (++j<_size)
		{
			if (_elem[i]!=_elem[j])
			{
				_elem[++i] = _elem[j];

			}
		}
		_size = ++i;
		return j - i;
	}
	Rank search(T const & e, Rank lo, Rank hi){
			binSearch(_elem, e, lo, hi);
	}//����ʧ���򷵻ز�����e������һ��Ԫ��
	static Rank binSearch(T* A, T const&e, Rank lo, Rank hi){
		while (lo<hi)
		{
			Rank mi = (lo + hi) / 2;
			if (e < A[mi]){
				hi = mi;
			}
			else if (e>A[mi])
			{
				lo = mi;
			}
			else
			{
				return mi;
			}
		}
		return -1;
	}
	void bubbleSort(Rank lo, Rank hi){
		for (Rank i = hi; i >lo; i--)
		{
			for (Rank j = 0; j<i; j++)
			{
				swap(_elem[j], _elem[j + 1]);
			}
		}		
	}
	void bubblesort2(Rank lo, Rank hi){
		while (!bubble(lo,hi--))
	}
	bool bubble(Rank lo, Rank hi){
		bool sorted = true;
		while (++lo<hi)
		{
			if (_elem[lo - 1] > _elem[lo]){
				sorted = false;
				swap(_elem[lo - 1], _elem[lo]);
			}
		}
		return sorted;
	}
	Rank bubble2(Rank lo, Rank hi){
		Rank last = lo;
		while (++lo<hi)
		{
			if (_elem[lo - 1] > _elem[lo]){
				last = lo;
				swap(_elem[lo - 1], _elem[lo]);
			}
		}
		return last;
	}
	void mergeSort(Rank lo, Rank hi) {
		if (hi - lo < 2) return;
		int mi = (lo + hi) / 2;
		mergeSort(lo, mi);
		mergeSort(mi, hi);
		merge(lo,hi,mi);

	}
	void merge(Rank lo, Rank mi, Rank hi) {
		T* A = _elem + lo;
		int lb = mi - lo;
		T* B=new T[lb];
		for(Rank i=0;i<lb;i++){
			B[i]=A[i];
		}
		int lc=hi-mi;
		T* C=_elem+mi;
		for(Rank i=0,j=0,k=0;j<lb;){
			if(lc<=k||B[j]<=C[k])A[i++]=B[j++];  //删去冗余逻辑，不用考虑j是否越界（若B提前完成则C原本就不用移动）
			if((k<lc)&&C[k]<B[j])A[i++]=C[k++];
		}
		delete B[];
	}
	T & operator[](Rank r) const { return _elem[r]; };
private:
	Rank _size;
	int _capacity;
	T* _elem;

	

};
template <typename T>



template <typename T>
void swap(T &a, T &b){
	T temp = 0;
	if (a>b)
	{
		temp = b;
		b = a;
		a = temp;
	}
}