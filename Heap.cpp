#include <iostream>
#include "Heap.h"

/**
@Brief This is the constructor for the Heap which uses a maxNumber to determinee the
maximum number of elements possible in the heap
*/
template <typename DataType, typename KeyType, typename Comparator>
Heap<DataType, KeyType, Comparator>::Heap(int maxNumber)
{
  maxSize = maxNumber;
  dataItems = new DataType[maxSize];
}

/**
@Brief This is the copy constructor for the Heap which uses another Heap object and
copies over the values element by element to our own.
*/
template <typename DataType, typename KeyType, typename Comparator>
Heap<DataType, KeyType, Comparator>::Heap(const Heap<DataType, KeyType, Comparator>& other)
{

  dataItems = new DataType[maxSize];

  for(int i = 0; i < maxSize; i++)
  {
    dataItems[i] = other.dataItems[i];
  }

}

/**
@Brief This is the equals operator for the Heap which determines whether or not the two
heaps are equivalent.
*/
template <typename DataType, typename KeyType, typename Comparator>
Heap<DataType, KeyType, Comparator>& Heap<DataType, KeyType, Comparator>::operator=(const Heap& other)
{
  if(this == &other)
    return *(this);

  clear();

  for(int i = 0; i < maxSize; i++)
  {
    dataItems[i] = other.dataItems[i];
  }

  return dataItems;
}


/**
@Brief This is the destructor for the Heap class which uses the clear() function*/
template <typename DataType, typename KeyType, typename Comparator>
Heap<DataType, KeyType, Comparator>::~Heap()
{
  clear();
}
/**
@Brief This is the insert function which inserts an item into the heap unless it is full*/
template <typename DataType, typename KeyType, typename Comparator>
void Heap<DataType, KeyType, Comparator>::insert(const DataType &newDataItem) throw (logic_error)
{


  if(isFull())
  {
    throw logic_error("insert() heap full");
  }
  else if(size > 0)
  {
    Comparator compare;
    ++size;
    int current = size - 1;
    int parent = 0;
    DataType hold;
     dataItems[size-1] = newDataItem;


       while(current > 0)
      {

            parent = (current - 1)/2;



            if(compare(dataItems[parent].getPriority(), dataItems[current].getPriority()))
            {


              current = parent;
            }
            else
            {
              hold = dataItems[parent];
              dataItems[parent] = dataItems[current];
              dataItems[current] = hold;
            }
            current = parent;
       }


  }
  else
  {
    dataItems[0] = newDataItem;
    size++;
  }

}

/**
@Brief This is the remove function which will remove an element from the heap unless
the heap is empty*/
template <typename DataType, typename KeyType, typename Comparator>
DataType Heap<DataType, KeyType, Comparator>::remove() throw (logic_error)
{
  if(isEmpty())
    throw logic_error("remove() heap empty");


    Comparator compare;

    int current = 0;
    int left = 0;
    int right = 0;
    int cmpIndex = 0;

  DataType removed;
  DataType temp;
  removed = dataItems[0];
  dataItems[0] = dataItems[size - 1];

  --size;

  while(current < size - 1)
  {

    left = current * 2 + 1;
    right = current * 2 + 2;




    if(right < size)
    {
      if(compare(dataItems[left].getPriority(), dataItems[right].getPriority()))
      {
        if(compare(dataItems[right].getPriority(), dataItems[current].getPriority()))
        {
          temp = dataItems[current];
          dataItems[current] = dataItems[right];
          dataItems[right] = temp;
          current = right;

        }
      }
      else
      {
        if(compare(dataItems[left].getPriority(), dataItems[current].getPriority()))
        {
          temp = dataItems[current];
          dataItems[current] = dataItems[left];
          dataItems[left] = temp;
          current = left;
        }
      }
    }
    else
    {
      if(compare(dataItems[left].getPriority(), dataItems[current].getPriority()))
      {
        temp = dataItems[current];
        dataItems[current] = dataItems[left];
        dataItems[left] = temp;
        current = left;
      }
    }




    current = size;
  }
  return removed;
}
/**
@Brief This is the clear function for the Heap*/
template <typename DataType, typename KeyType, typename Comparator>
void Heap<DataType, KeyType, Comparator>::clear()
{

  size = 0;

}
/**
@Brief This is the isEmpty function for the heap - returns true if size is 0
*/
template <typename DataType, typename KeyType, typename Comparator>
bool Heap<DataType, KeyType, Comparator>::isEmpty() const
{
  if(size > 0)
    return false;
  else
    return true;
}
/**
@Brief This is the isFull function for the heap - returns true if size == maxSize
*/
template <typename DataType, typename KeyType, typename Comparator>
bool Heap<DataType, KeyType, Comparator>::isFull() const
{
  if(size == maxSize)
    return true;
  else
    return false;
}

/**
@Brief  This shows the structure of the heap
*/
template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType,KeyType,Comparator>:: showStructure () const

// Outputs the priorities of the data items in a heap in both array
// and tree form. If the heap is empty, outputs "Empty heap". This
// operation is intended for testing/debugging purposes only.

{
    int j;   // Loop counter

    cout << endl;
    if ( size == 0 )
       cout << "Empty heap" << endl;
    else
    {
       cout << "size = " << size << endl;       // Output array form
       for ( j = 0 ; j < maxSize ; j++ )
           cout << j << "\t";
       cout << endl;
       for ( j = 0 ; j < size ; j++ )
           cout << dataItems[j].getPriority() << "\t";
       cout << endl << endl;
       showSubtree(0,0);                        // Output tree form
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

/**
@Brief  Helper to the showStructure function
*/
template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType,KeyType,Comparator>:: showSubtree ( int index, int level ) const

// Helper function for the showStructure() function. Outputs the
// subtree (subheap) whose root is stored in dataItems[index]. Argument
// level is the level of this dataItems within the tree.

{
     int j;   // Loop counter

     if ( index < size )
     {
        showSubtree(2*index+2,level+1);        // Output right subtree
        for ( j = 0 ; j < level ; j++ )        // Tab over to level
            cout << "\t";
        cout << " " << dataItems[index].getPriority();   // Output dataItems's priority
        if ( 2*index+2 < size )                // Output "connector"
           cout << "<";
        else if ( 2*index+1 < size )
           cout << "\\";
        cout << endl;
        showSubtree(2*index+1,level+1);        // Output left subtree
    }
}

/**
@Brief This function will write the levels in descending order
*/
template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType,KeyType,Comparator>::writeLevels() const
{
  int count = 0;
  int level = 0;
  int ctrl = 0;

  while(count < size)
  {
    ++level;
    if(count * 2 + 1 < size)
      ctrl = count * 2 + 1;
    else
      ctrl = size;
    for(count; count < ctrl; count++ )
    {
      cout << dataItems[count].getPriority() << " ";
    }


    cout << endl;
  }
}
