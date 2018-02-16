template<class T, int max_size>
class heap
{
protected:
	T data[max_size];
	int heap_size;
public:
	heap() { heap_size = 0; }
	/*	init()
	{ if(heap_size>0)
	delete [] data;
	max_size=100000; data=new T[max_size];
	}
	*/	int heap_empty() { return heap_size == 0; }
	void swap(T &a, T &b)
	{
		T   tmp = a;
		a = b;
		b = tmp;
	}

	void movedown(int first, int last)
	{
		int largest = 2 * first + 1;  // contain the index of the child
									  // that has the larger value,
									  // initialize to left child

		while (largest <= last) // continue to move down
		{
			if (largest < last && le(data[largest], data[largest + 1]))
				largest++; // if first has 2 children and right has a higher
						   // value, move down on the right path. 
						   // otherwise, use left path
						   // swap first with largest and move down, if necessary
			if (le(data[first], data[largest]))
			{
				swap(data[first], data[largest]);
				first = largest;
				largest = 2 * first + 1;
			}
			else largest = last + 1; // set largest to exit;
		}
	}
	void push_heap(T newdata)
	{
		if (heap_size == max_size)
		{
			/*			max_size++;
			T *next;
			next=data+heap_size;
			next = new T;
			heap_size++;
			*/
			static int despose = heap_size;
			if (despose>(heap_size - 2) / 2)
				despose--;
			else
				despose = heap_size;
			data[despose] = newdata; // replace one on the last level
		}
		else
		{
			heap_size++;
			data[heap_size - 1] = newdata; // place at the end
		}

		//		fh << "Heap size:\t" << heap_size << endl;
		int child = heap_size - 1, parent = (child - 1) / 2;

		while (child>0 && le(data[parent], data[child]))
		{
			swap(data[parent], data[child]);
			child = parent;
			parent = (child - 1) / 2;
		}
	}
	void pop_heap(T &dt)
	{
		dt = data[0];
		data[0] = data[heap_size - 1];
		heap_size--;
		if (!heap_empty())
			movedown(0, heap_size - 1);
	}
};
