#pragma once

#include <iostream>

template<class T>
class vector
{

public:
	typedef T value_type;
	typedef value_type* pointer;
	typedef value_type* iterator;
	typedef value_type& reference;
	typedef size_t size_type;
	typedef value_type*& difference_type;

protected:
	iterator start;				//正在使用的空间首地址
	iterator finish;			//正在使用的空间尾地址
	iterator end_of_storage;	//目前可用的空间尾地址

public:
	vector():start(0), finish(0), end_of_storage(0) {}
	vector(int n, const T& value = T()) :start(0), finish(0), end_of_storage(0)
	{
		reserve(n);
		for (auto i = 0; i < n; ++i)
		{
			push_back(value);
		}
	}

	vector(vector &v) :start(0), finish(0), end_of_storage(0)
	{
		reserve(v.capacity());
		for (auto i = 0; i < v.size(); ++i)
		{
			*(start + i) = v[i];
		}

		finish = start + v.size();
		end_of_storage = start + v.capacity();
	}

	template<class InputIterator>
	vector(InputIterator first, InputIterator last)
	{
		reserve(last - first);
		while (first != last)
		{
			push_back(*first);
			++first;
		}
	}

	~vector() 
	{
		if (start)
		{
			delete[] start;
			start = finish = end_of_storage = nullptr;
		}
	}

	iterator begin() { return start; }
	iterator end() { return finish; }
	size_type size() const { return size_type(finish - start); }
	size_type capacity()const { return size_type(end_of_storage - start); }
	bool empty() { return start == finish; }
	reference operator[](size_type n) { return *(start + n); }

	reference front() { return *start; }
	reference back() { return *(finish - 1); }

	void reserve(size_type n)
	{
		if (n > capacity())
		{
			int sz = size();
			T* tmp = new T[n];
			
			if (start)
			{
				for (auto i = 0; i < sz; ++i)
				{
					tmp[i] = start[i];
				}
				delete[] start;
			}

			start = tmp;
			finish = start + sz;
			end_of_storage = start + n;
		}
	}

	void push_back(const T& value)
	{
		if (finish != end_of_storage)
		{
			*(finish++) = value;
		}
		else
		{
			int n = (size() == 0 ? 1 : 2 * size());
			reserve(n);
			*(finish++) = value;
		}
	}

	void pop_back()
	{
		--finish;
	}

	iterator erase(iterator position)
	{
		if (position + 1 != finish)
		{
			for (auto it = position + 1; it != finish; ++it)
			{
				*(it - 1) = *it;
			}
		}
		pop_back();
		return position;
	}

	iterator erase(iterator start, iterator end)
	{
		if (end != finish)
		{
			for (auto it = end; it != finish; ++it, ++start)
			{
				*start = *it;
			}
		}
		finish = start;

		return start;
	}

	void resize(size_type new_size, const T& value)
	{
		if (new_size < size())
			erase(begin() + new_size, end());
		else
		{
			int sz = size();
			for (auto i = 0; i < new_size - sz; ++i)
			{
				push_back(T());
			}
		}
	}

	void resize(size_type new_size)
	{
		resize(new_size, T());
	}

	void clear()
	{
		erase(start, finish);
	}

	void printAll()
	{
		for (auto it = start; it != finish; ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
	}
};

void TestVector()
{
#if 0
	//vector测试
	vector<int> vec;
	vector<int> vec2(5, 1);
	vector<int> vec3(vec2);
	vec.push_back(1);
	cout << "size: " << vec.size() << " capacity: " << vec.capacity() << endl;
	vec.push_back(2);
	cout << "size: " << vec.size() << " capacity: " << vec.capacity() << endl;
	vec.push_back(3);
	cout << "size: " << vec.size() << " capacity: " << vec.capacity() << endl;
	vec.push_back(4);
	cout << "size: " << vec.size() << " capacity: " << vec.capacity() << endl;
	vec.push_back(5);
	cout << "size: " << vec.size() << " capacity: " << vec.capacity() << endl;

	vec.resize(20);
	cout << "size: " << vec.size() << " capacity: " << vec.capacity() << endl;

	vec.resize(10);
	cout << "size: " << vec.size() << " capacity: " << vec.capacity() << endl;

	vec.erase(vec.end() - 1);
	cout << "size: " << vec.size() << " capacity: " << vec.capacity() << endl;
	vec.printAll();
#endif
}