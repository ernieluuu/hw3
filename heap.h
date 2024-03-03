#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <cmath> /*included to implement ceiling division*/

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

  // added member functions

  /*add parameters for these?*/

  void trickleUp();

  void trickleDown();

  /*prints the contents and indices of the vector*/
  void printHeap();

private:

	std::vector<T> heap_;

	size_t size_;

	int m_;

	PComparator comp_;
};

// Add implementation of member functions here


template<typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c)
{
	size_ = 0;
	m_ = m;
	comp_ = c;
}

template<typename T, typename PComparator>
Heap<T, PComparator>::~Heap()
{
}

template<typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item)
{
	/*
	a series of starting at the back (the first empty idx)
	and comparing it to the parent, and making the necessary
	swaps.
	use the PComparator template to do the comparison so it works
	for many different types.
	*/

	// push back into the vector
	// update size_
	// call trickleUp

	heap_.push_back(item);
	++size_;
	trickleUp();

}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
	  throw std::underflow_error("called top on empty heap.");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  
  // return first item in vector
  return heap_.front();

}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
	  throw std::underflow_error("called top on empty heap.");
  }

  // swap first + last item, then pop_back()
  heap_[0] = heap_[size_ - 1];
  heap_.pop_back();
  --size_;
  trickleDown();
}

template<typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const
{
	return size_ == 0;
}

template<typename T, typename PComparator>
size_t Heap<T, PComparator>::size() const
{
	return this->size_;
}

template<typename T, typename PComparator>
void Heap<T, PComparator>::trickleUp()
{
	// use PComparator (returns a bool) PComparator(x,y)

	// start @ last idx (that's where we placed the new node)
	// and then keep comparing it to the parent until comp_ is false

	if (size_ == 1)
	{
		return;
	}

	int xIdx = size_ - 1;
	int yIdx = static_cast<int>(std::ceil(static_cast<double>(size_ - 1) / m_)) - 1;

	/*where x is the element at the last idx and y is the parent of x*/
	T x = heap_[xIdx];
	T y = heap_[yIdx];

	while (comp_(x,y))
	{
		// swap
		T temp = x;
		heap_[xIdx] = y;
		heap_[yIdx] = temp;

		// if x has become the root node
		if (yIdx == 0)
		{
			break;
		}

		// update x + y
		xIdx = yIdx;
		yIdx = static_cast<int>(std::ceil(static_cast<double>(xIdx) / m_)) - 1;

		x = heap_[xIdx];
		y = heap_[yIdx];
	}
}

template<typename T, typename PComparator>
void Heap<T, PComparator>::trickleDown()
{
	// start at top

	/*
	Note : This is true when your heap is starting from index 1. 
	If the heap is starting at position 0, the values are 
	(2*i) +1 and (2*i) +2 for left and right child respectively.
	*/

	// for all the children, find the 'best' (use comp_ on all the children first)
	// then if comp_(child, top), do swap.

	T curr_item = this->top();

	T best_item;

	int currIdx = 0;
	int bestItemIdx;

	while (m_*currIdx >= size_) /*breaks when there is no child node for the given parent*/
	{

		int firstChildIdx = m_ * currIdx + 1;

		/*compares all the children nodes to find the 'best' one*/
		best_item = heap_[firstChildIdx];
		for (int i = firstChildIdx+1; i < firstChildIdx+m_; i++)
		{
			// if out of bounds, break out of the for loop
			if (i >= size_)
			{
				break;
			}

			/*if curr item is better than the best item*/
			if (comp_(heap_[firstChildIdx + i], best_item))
			{
				// update best item
				best_item = heap_[firstChildIdx + i];
				bestItemIdx = firstChildIdx + i;
			}
		}

		/*if the item we are trickling down is in the right place ('better' than all children)*/
		if (comp_(curr_item, best_item))
		{
			break;
		}
		else 
		{
			// swap
			T temp = curr_item;
			heap_[currIdx] = best_item;
			heap_[bestItemIdx] = curr_item;
			// update currIdx (where is the root node now?)
			currIdx = bestItemIdx;
		}	
	}

}

/*helper function for debugging*/
template<typename T, typename PComparator>
void Heap<T, PComparator>::printHeap()
{
	std::cout << "Heap Contents (idx, content):" << std::endl;

	for (int i = 0; i < size_; i++)
	{
		std::cout << "idx " << i << ": " << heap_[i] << std::endl;
	}
}

#endif

