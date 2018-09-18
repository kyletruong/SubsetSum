//
//  Sublist.h
//
//  Created by Kyle Truong on 4/15/18.
//  Copyright © 2018 Kyle Truong. All rights reserved.
//

#ifndef Sublist_h
#define Sublist_h

using namespace std;

// -------------------- Sublist class prototype --------------------

template <class T>
class Sublist {
public:
   Sublist(vector<T> *orig = NULL) : sum(0), originalObjects(orig) { }
   Sublist addItem(int indexOfItemToAdd);
   void showSublist() const; // need a const iterator
   int getSum() const { return sum; }

private:
   int sum;
   vector<T> *originalObjects;
   vector<int> indices;
};

// -------------------- Sublist class definitions --------------------
template<class T>
Sublist<T> Sublist<T>::addItem(int indexOfItemToAdd) {
   Sublist newSublist = *this;

   // -1 indicates TARGET >= masterSum
   // Skip entire algorithm and return a subList which contains entire dataSet
   if (indexOfItemToAdd == -1) {
      for (int i = 0; i < originalObjects->size(); i++) {
         newSublist.indices.push_back(i);
         newSublist.sum = newSublist.sum + (*originalObjects)[i];
      }
      return newSublist;
   }

   newSublist.indices.push_back(indexOfItemToAdd);
   newSublist.sum = this->sum + (*originalObjects)[indexOfItemToAdd];
   return newSublist;
}

template<class T>
void Sublist<T>::showSublist() const {
   vector<int>::const_iterator iter;
   cout << "-------------------- Sublist --------------------" << endl << endl;
   cout << "Sum: " << sum << endl << endl;
   for (iter = indices.begin(); iter != indices.end(); iter++) {
      cout << "array[" << *iter << "] = " << (*originalObjects)[*iter];
      if (*iter != indices.back())
         cout << ",   ";
   }
   cout << endl << endl;
}

#endif /* Sublist_h */
