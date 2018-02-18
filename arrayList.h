


#include<iostream>
#include<sstream>
#include<string>
#include<algorithm>
#include "linearList.h"
#include "myExceptions.h"
#include "changeLength1D.h"

using namespace std;

template<class T>
class arrayList : public linearList<T> 
{
   public:

      arrayList(int initialCapacity = 10);
      arrayList(const arrayList<T>&);
      ~arrayList() {delete [] element;}

   
      bool empty() const {return listSize == 0;}
      int size() const {return listSize;}
      T& get(int theIndex) const;
      int indexOf(const T& theElement) const;
      void erase(int theIndex);
      void insert(int theIndex, const T& theElement);
      void output(ostream& out) const;

   
      int capacity() const {return arrayLength;}

   protected:
      void checkIndex(int theIndex) const;
            
      T* element;            
      int arrayLength;       
      int listSize;          
};

template<class T>
arrayList<T>::arrayList(int initialCapacity)
{
   if (initialCapacity < 1)
   {ostringstream s;
    s << "Initial capacity = " << initialCapacity << " Must be > 0";
    throw illegalParameterValue(s.str());
   }
   arrayLength = initialCapacity;
   element = new T[arrayLength];
   listSize = 0;
}

template<class T>
arrayList<T>::arrayList(const arrayList<T>& theList)
{
   arrayLength = theList.arrayLength;
   listSize = theList.listSize;
   element = new T[arrayLength];
   copy(theList.element, theList.element + listSize, element);
}

template<class T>
void arrayList<T>::checkIndex(int theIndex) const
{
   if (theIndex < 0 || theIndex >= listSize)
   {ostringstream s;
    s << "index = " << theIndex << " size = " << listSize;
    throw illegalIndex(s.str());
   }

}

template<class T>
T& arrayList<T>::get(int theIndex) const
{
   checkIndex(theIndex);
   return element[theIndex];
}

template<class T>
int arrayList<T>::indexOf(const T& theElement) const
{

   
   int theIndex = (int) (find(element, element + listSize, theElement)
                         - element);

  
   if (theIndex == listSize)
  
     return -1;
   else return theIndex;
 }

template<class T>
void arrayList<T>::erase(int theIndex)
{
   checkIndex(theIndex);

   
   copy(element + theIndex + 1, element + listSize,
                                element + theIndex);

   element[--listSize].~T(); 
}

template<class T>
void arrayList<T>::insert(int theIndex, const T& theElement)
{
   if (theIndex < 0 || theIndex > listSize)
   {
      ostringstream s;
      s << "index = " << theIndex << " size = " << listSize;
      throw illegalIndex(s.str());
   }

   
   if (listSize == arrayLength)
      {
         changeLength1D(element, arrayLength, 2 * arrayLength);
         arrayLength *= 2;
      }

 
   copy_backward(element + theIndex, element + listSize,
                 element + listSize + 1);

   element[theIndex] = theElement;

   listSize++;
}

template<class T>
void arrayList<T>::output(ostream& out) const
{
   copy(element, element + listSize, ostream_iterator<T>(cout, "  "));
}


template <class T>
ostream& operator<<(ostream& out, const arrayList<T>& x)
   {x.output(out); return out;}

