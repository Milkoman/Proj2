#ifndef ARRAY_H
#define ARRAY_H

class OutOfBounds {};

using std::ostream;
template <class T>
class Array;
template <class T>
ostream &operator<< (ostream &, const Array<T> &);

template<class T>
class Array
{
private:
	T *data;
	int size;

public:
	Array() { data = nullptr; size = 0; }
	Array(int x) { data = new T[x]; size = x; }
	Array(Array<T> &);
	~Array() { delete[] data; }

	T getData(int x) const { return data[x]; }
	int getSize() const { return size; }

	const T operator=(const T &right)
	{
		return *this;
	}
	T& operator[](int index) { if (index >= 0 && index < size) return data[index]; else throw OutOfBounds(); }

	template <class T>
	friend ostream &operator<< (ostream &, const Array<T> &);

};

template<class U>
inline ostream & operator<<(ostream &strm, const Array<U>& obj)
{
	for (int i = 0; i < obj.getSize(); i++)
	{
		strm << obj.getData(i) << " ";
	}
	return strm;
}

template<class T>
inline Array<T>::Array(Array<T> & arr)
{
	size = arr.getSize();
	data = new T[size];
	for (int i = 0; i < size; i++) {
		data[i] = arr[i];
	}
}
#endif
