#include<iostream.h>


struct true_t{};  // boolean values represented by types
struct false_t{}; 

// ---------- Lazy lists and partial specializations ------------
template<int i, int step, class Operation>
struct lazy_list;

struct i_plus_c {};
template<int i, int step>
struct lazy_list<i,step,i_plus_c > {
  enum {n=i};
  typedef lazy_list<i+step,step,i_plus_c > next;  
  
};
struct i_times_c {};
template<int i, int step>
struct lazy_list<i,step,i_times_c > {
  enum {n=i};
  typedef lazy_list<i*step,step,i_times_c > next; 
};

struct i_times_i {}; 
template<int i, int step>
struct lazy_list<i,step,i_times_i > {
  enum {n=i};
  typedef lazy_list<step*step,step+1,i_times_i > next; 
};

struct fibonacci{}; 
template<>
struct lazy_list<0,1,fibonacci> {
  enum {n=1};
  typedef lazy_list<1,1,fibonacci> next; 
};

template<int i, int step>
struct lazy_list<i,step,fibonacci> {
  enum {n=i};
  typedef lazy_list<i+step, i, fibonacci> next; 
};


//---------------------    head  --------------------------------
template<typename Lazy_List>
struct head {
  head() { cout << typename Lazy_List::val() << endl; }
};

//----------------------   take  ------------------------------------
template<typename Lazy_List, int how_many>
struct take {
  typedef typename Lazy_List::next next;
  enum {n=Lazy_List::n};
  take() { 
    cout << Lazy_List::n << ", " ;
    take<typename Lazy_List::next,how_many -1>();
  }
};

template<typename Lazy_List>
struct take<Lazy_List,0>{
  typedef typename Lazy_List::next next;
  enum {n=Lazy_List::n};
  take() { cout << "..." << endl; }
};
//---------------------  takeWhile -------------------------------
template<typename Lazy_List, typename Pred, int comp>
struct takeWhile {
  typedef takeWhile<Lazy_List,Pred,comp> val;
};

template<int i, typename Lazy_List, typename Pred, int comp>
struct _takeWhile;

template<typename Lazy_List, typename Pred, int comp>
struct _takeWhile<0,Lazy_List,Pred,comp> {
  typedef typename 
  takeWhile<typename Lazy_List::next, Pred, comp>::val val;
};

template<typename Lazy_List, typename Pred, int comp>
struct _takeWhile<1,Lazy_List,Pred,comp> {
  typedef  Lazy_List val;
};
struct greater_than_c {};
template<typename Lazy_List, int comp>
struct takeWhile<Lazy_List, greater_than_c, comp>  {
  typedef typename
  _takeWhile<(Lazy_List::n > comp), Lazy_List,greater_than_c, comp>::val val;
};
struct modulo_c {};
template<typename Lazy_List, int comp>
struct takeWhile<Lazy_List, modulo_c, comp>  {
  typedef typename
  _takeWhile<(Lazy_List::n % comp) == 0, Lazy_List,modulo_c, comp>::val val;
};

//----------------------  Nth -----------------------------------
template<typename Lazy_List, int nth>
struct Nth {
  typedef typename Nth<typename Lazy_List::next,nth-1>::val val;
};

template<typename Lazy_List>
struct Nth<Lazy_List,1>{
  typedef typename Lazy_List::next val;
};

//------------------   elem ------------------------------------
template<typename Lazy_List,int el>
struct elem;

template<typename Lazy_List, int head, int el>
struct _elem {
  typedef false_t val;
  typedef typename _elem<typename Lazy_List::next, Lazy_List::n,
                       el>::bool_t bool_t;
  _elem() { cout << bool_t() << endl;}
};

template<typename Lazy_List, int head>
struct _elem<Lazy_List,head,head> {
  typedef true_t val;
  typedef true_t bool_t;
  _elem() { cout << bool_t() << endl;}
};

template<typename Lazy_List, int el>
struct elem {
  typedef false_t val;
  typedef typename _elem<Lazy_List, Lazy_List::n,el>::bool_t bool_t;
  elem() { cout << bool_t() << endl; }
};

template<typename Lazy_List,int head, int el,int how_many>
struct _elem <take<Lazy_List,how_many>,head,el>{
  typedef false_t val;
  typedef typename _elem<take<Lazy_List,how_many-1>,
                       Lazy_List::n,el>::bool_t bool_t;
  _elem() { bool_t(); }
};

template<typename Lazy_List, int how_many,int head>
struct _elem <take<Lazy_List,how_many>,head,head >{
  typedef true_t val;
  typedef true_t bool_t;
  _elem() { cout << "true " << endl; }
};

template<typename Lazy_List,int head,int el>
struct _elem <take<Lazy_List,0>,head,el>{
  typedef false_t val;
  typedef false_t bool_t;
  _elem() { cout << "false " << endl; }
};

//----------------------- print -------------------------------------
ostream& operator<<(ostream& s, const true_t) {
  return s << "true";
 };
ostream& operator<<(ostream& s, const false_t) {
  return s << "false";
 };
template<int i, int step,typename Operation>
ostream& operator<<(ostream& s, const lazy_list<i,step,Operation>& str) {
  return s << i;
 };

//---------------------  Main -----------------------------------------

int main() {

  // Define some lazy lists and introduce symbolic names for them
  typedef lazy_list<0,1,i_plus_c>  naturals;
  typedef lazy_list<0,2,i_plus_c>  even;
  typedef lazy_list<1,2,i_plus_c>  odd;
  typedef lazy_list<0,3,i_plus_c>  multiples_of_three;

  typedef lazy_list<1,2,i_times_c> powers_of_two;
  typedef lazy_list<1,3,i_times_c> powers_of_three;
  typedef lazy_list<1,2,i_times_i> squares;
  typedef lazy_list<0,1,fibonacci> fibonacci;

  // Generate initial values and write them out 
  cout << "Printing the first 7 elements of the  " << endl;
  cout << " natural numbers:   ";   take<naturals,7>();
  cout << " even numbers:      ";   take<even,7>();
  cout << " odd numbers:       ";   take<odd,7>();
  cout << " multiples of 3:    ";   take<multiples_of_three,7>();
  cout << " powers of 2:       ";   take<powers_of_two,7>();

  cout << " powers of 3:       ";   take<powers_of_three,7>(); 

  cout << " squares:           ";   take<squares,7>();
  cout << " fibonacci numbers: ";   take<fibonacci,7>();


  cout << "\nOther generator-filter examples:\n";
  cout << " The 11th odd number? ";
  head<Nth<odd,10> >();
  cout << " The first square number greater than 50? ";
  head<takeWhile<squares,greater_than_c,50> >();
  cout << " The first multiple of 3 divisible by 2? ";
  head<takeWhile<multiples_of_three,modulo_c,2> >();
  cout << " The first nonzero multiple of 3 divisible by 2? ";
  head<takeWhile<take<multiples_of_three,1>::next,modulo_c,2> >();

  cout << " 21 is a Fibonacci number, correct? " ; elem<fibonacci,21>();
  cout << " 37 is one of the first 5 Fibonacci numbers, correct? "; 
          elem<take<fibonacci,5>,33>();

}

