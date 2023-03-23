// #include "bintree.h"
// #include <fstream>
// #include <iostream>
// using namespace std;

// //global function prototype
// void buildTree(BinTree&, ifstream&); // build the tree using given data file

// int main() {
//    // create file object infile and open it
//    // for testing, call your data file something appropriate, e.g., data2.txt
//    ifstream infile("data2.txt");
//    if (!infile) {
//       cout << "File could not be opened." << endl;
//       return 1;
//    }

//    // the NodeData class must have a constructor that takes a string
//    NodeData iiiND("iii");
//    NodeData andND("and");
//    NodeData rND("r");
//    NodeData aND("a");
//    NodeData bND("b");
//    NodeData cND("c");

//    BinTree T;
//    for (;;) {
//       cout << "Initial data:" << endl << "  ";
//       buildTree(T, infile);              // builds and displays initial data
//       cout << endl;
//       if (infile.eof()) {
//          break;
//       }
//       cout << "Tree Inorder:" << endl << T;         // operator<< does endl
//       T.displaySideways(); cout << endl;

//       // test remove
//       NodeData* p;                    // pointer of removed object
//       bool found;                     // whether or not object was found in tree
//       found = T.remove(andND, p);
//       cout << "remove --> and:  " << (found ? "found":"not found") << endl;
//       if (found) delete p;
//       T.displaySideways(); cout << endl;

//       found = T.remove(iiiND, p);
//       cout << "remove --> iii:  " << (found ? "found":"not found") << endl;
//       if (found) delete p;
//       T.displaySideways(); cout << endl;

//       found = T.remove(rND, p);
//       cout << "remove --> r  :  " << (found ? "found":"not found") << endl;
//       if (found) delete p;
//       T.displaySideways(); cout << endl;

//       found = T.remove(cND, p);
//       cout << "remove --> c  :  " << (found ? "found":"not found") << endl;
//       if (found) delete p;
//       T.displaySideways(); cout << endl;

//       found = T.remove(bND, p);
//       cout << "remove --> b  :  " << (found ? "found":"not found") << endl;
//       if (found) delete p;
//       T.displaySideways(); cout << endl;

//       found = T.remove(aND, p);
//       cout << "remove --> a  :  " << (found ? "found":"not found") << endl;
//       if (found) delete p;
//       T.displaySideways(); cout << endl;

//       cout << "Tree Inorder:" << endl << T;  

//       cout << "---------------------------------------------------------------"
//            << endl;
//       T.makeEmpty();             // empty out the tree so another can be built
//    }
//    infile.close();

//    return 0;
// }

// //----------------------------------------------------------------------------
// // buildTree
// //
// // To build a tree, read strings from a line, terminating with "$$" .
// // Since there is some work to do before the actual insert that is specific to
// // the client problem (tree class does not know about the data that it holds),
// // building a tree is not a member function.  It's a global function.

// void buildTree(BinTree& t, ifstream& infile) {
//    string s;

//    for (;;) {
//       infile >> s;
//       cout << s << ' ';
//       if (s == "$$") {                      // at end of one line
//          break;
//       }

//       // no more lines of data, must attempt to read the line so the
//       // end-of-file character is read, triggering eof() to be true
//       if (infile.eof()) {
//          break;
//       }

//       // in an object-oriented program, change to setData() for reading
//       NodeData* ptr = new NodeData(s);

//       bool success = t.insert(ptr);
//       if (!success) {
//          delete ptr;                       // duplicate case, not inserted
//          ptr = nullptr;
//       }
//    }
// }
