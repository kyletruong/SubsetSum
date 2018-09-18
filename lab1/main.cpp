//
//  main.cpp
//
//  Created by Kyle Truong on 4/15/18.
//  Copyright © 2018 Kyle Truong. All rights reserved.
//

#include <iostream>
#include <time.h>
#include "iTunes.h"
#include "Sublist.h"

// -------------------- subsetSum template function --------------------

template<class T>
void subsetSum(int TARGET, vector<T> dataSet) {
   vector<Sublist<T>> choices;
   int k, j;
   long numSets;
   int masterSum = 0;
   choices.clear();

   cout << "Target: " << TARGET << endl << endl;

   for (int i = 0; i < dataSet.size(); i++)
      masterSum = masterSum + dataSet[i];

   // If TARGET >= masterSum, skip algorithm
   // Returns single Sublist which contains entire dataSet
   if (TARGET >= masterSum) {
      choices.push_back(Sublist<T>(&dataSet).addItem(-1));
      return choices[0].showSublist();
   }

   // Initializing choices with an empty sublist
   choices.push_back(Sublist<T>(&dataSet));

   // Algorithm
   for (k = 0; k < dataSet.size(); k++) {
      numSets = choices.size();
      for (j = 0; j < numSets; j++) {
         if ((choices[j].getSum() + dataSet[k]) <= TARGET)
            choices.push_back(choices[j].addItem(k));
         if (choices.back().getSum() == TARGET)
            return choices.back().showSublist();
      }
   }

   // If we can't find the exact target, find the best subList
   Sublist<T> bestSublist = choices[0];
   for (int i = 0; i < choices.size(); i++) {
      if (choices[i].getSum() > bestSublist.getSum())
         bestSublist = choices[i];
   }
   bestSublist.showSublist();
}

// -------------------- overloaded operators --------------------

int operator+(int lhs, const iTunesEntry &rhs) {
   return lhs + rhs.getTime();
}

ostream & operator<<(ostream & ostrm, const iTunesEntry &tune) {
   ostrm << tune.getTitle() << " by " << tune.getArtist() << "("
   << tune.getTime() << ")";

   return ostrm;
}

// -------------------- main --------------------
// Testing edge cases

int main() {
   const int TARGET = 3600;
   vector<iTunesEntry> dataSet;

   // read the data
   iTunesEntryReader tunes_input("itunes_file.txt");

   if (tunes_input.readError()) {
      cout << "couldn't open " << tunes_input.getFileName()
      << " for input.\n";
      exit(1);
   }

   // time the algorithm -------------------------
   clock_t startTime, stopTime;
   startTime = clock();

   // create a vector of objects for our own use:
   int array_size = tunes_input.getNumTunes();
   for (int k = 0; k < array_size; k++)
      dataSet.push_back(tunes_input[k]);

   // Templatized subsetSub
   subsetSum(TARGET, dataSet);

   // how we determine the time elapsed -------------------
   stopTime = clock();

   // report algorithm time
   cout << "\nAlgorithm Elapsed Time: "
   << (double)(stopTime - startTime)/(double)CLOCKS_PER_SEC
   << " seconds." << endl << endl;

   cout << "******************* MORE TESTING *******************" << endl
   << endl << endl;
   const int TARGET2 = 0;
   const int TARGET3 = 300;
   const int TARGET4 = -1;

   subsetSum(TARGET2, dataSet);
   subsetSum(TARGET3, dataSet);
   subsetSum(TARGET4, dataSet);

   return 0;
}

/* -------------------- output pasted below --------------------

 Target: 3600

 -------------------- Sublist --------------------

 Sum: 3600

 array[0] = Cowboy Casanova by Carrie Underwood(236),
 array[1] = Quitter by Carrie Underwood(220),
 array[2] = Russian Roulette by Rihanna(228),
 array[4] = Monkey Wrench by Foo Fighters(230),
 array[5] = Pretending by Eric Clapton(283),
 array[6] = Bad Love by Eric Clapton(308),
 array[7] = Everybody's In The Mood by Howlin' Wolf(178),
 array[8] = Well That's All Right by Howlin' Wolf(175),
 array[9] = Samson and Delilah by Reverend Gary Davis(216),
 array[11] = Hot Cha by Roy Buchanan(208),
 array[12] = Green Onions by Roy Buchanan(443),
 array[13] = I'm Just a Prisoner by Janiva Magness(230),
 array[14] = You Were Never Mine by Janiva Magness(276),
 array[15] = Hobo Blues by John Lee Hooker(187),
 array[16] = I Can't Quit You Baby by John Lee Hooker(182)


 Algorithm Elapsed Time: 0.119874 seconds.

 ******************* MORE TESTING *******************


 Target: 0

 -------------------- Sublist --------------------

 Sum: 0



 Target: 300

 -------------------- Sublist --------------------

 Sum: 300

 array[22] = Our Big Break by Veggie Tales(69),
 array[69] = Luka by Suzanne Vega(231)

 Target: -1

 -------------------- Sublist --------------------

 Sum: 0



 Program ended with exit code: 0

-------------------- end of output -------------------- */
