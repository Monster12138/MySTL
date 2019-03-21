#pragma once

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

	void insert_aux(iterator position, const reference x);
	void deallocate();
	void fill_initialize(size_type n, const reference x);
	void copy(iterator start, iterator end, iterator dst);
public:
	vector():start(0), finish(0), end_of_storage(0) {}
	vector(size_type n, const reference value) { fill_initialize(n, value); }
	explicit vector(size_type n) { fill_initialize(n, T()); }

	~vector() {}

	iterator begin() { return start; }
	iterator end() { return finish; }
	size_type size() const { return size_type(finish - start); }
	size_type capacity()const { return size_type(end_of_storage - start); }
	bool empty() { return start == finish; }
	reference operator[](size_type n) { return *(start + n); }

	reference front() { return *start; }
	reference back() { return *(finish - 1); }
	void push_back(const reference value)
	{
		if (finish != end_of_storage)
		{
			*(finish++) = value;
		}
		else
		{
			insert_aux(finish, value);
		}
	}

	void pop_back()
	{
		--finish;
	}

	iterator erase(iterator position)
	{
		if (position + 1 ！= finish)
		{
			copy(position + 1, finish, position);
		}
		pop_back();
		return position;
	}

	iterator erase(iterator start, iterator end)
	{

	}

	iterator insert(iterator position, size_type count, const reference value)
	{

	}

	void resize(size_type new_size, const reference value)
	{
		if (new_size < size())
			erase(begin() + new_size, end());
		else
			insert(end(), new_size - size(), value);
	}

	void resize(size_type new_size)
	{
		resize(new_size, T());
	}

	void clear()
	{
		erase(start, finish);
	}
};