#include <iostream>
#include <memory>

using namespace std;

enum Direction {dirForward, dirBackward };

Direction opposite(const Direction dir)
{
   return ( dir == dirForward ? dirBackward : dirForward );
}

class Node
{
public:
   Node(const int v) :
       next(nullptr),
       prev(nullptr),
       value(v)
   {}

   shared_ptr<Node> next;
   shared_ptr<Node> prev;
   int value;

   shared_ptr<Node> * adjanced(const Direction dir); // zwraca wskaznik na next albo prev
};

class List
{
public:
   List();

   void addLast(shared_ptr<Node> node);    // dodaje element na koniec listy
   void addFirst(shared_ptr<Node> node);   // dodaje element na poczatek listy
   shared_ptr<Node> getForward(const int value);  // zwraca element o wskazanej wartości
   shared_ptr<Node> getBackward(const int value);  // zwraca element o wskazanej wartości

private:
   shared_ptr<Node> first;
   shared_ptr<Node> last;
   shared_ptr<Node> * edge(const Direction dir); // zwraca wskaznik na first albo last
   void add(shared_ptr<Node> node, const Direction dir);        // dodaje element na skraj listy
   shared_ptr<Node> get(const int value, const Direction dir);  // zwraca element o wskazanej wartości
};

List::List()
{
 first = nullptr;
 last = nullptr;
}

shared_ptr<Node> * List::edge(const Direction dir)
{
   return ( dir == dirForward ? &last : &first );
}

shared_ptr<Node> * Node::adjanced(const Direction dir)
{
   return ( dir == dirForward ? &next : &prev );
}


void List::add(shared_ptr<Node> node, const Direction dir)
{
   if (!(*edge(dir))) {
       node->next = nullptr;
       node->prev = nullptr;
       first = node;
       last = node;
   }    
   else {
       *(node->adjanced(opposite(dir))) = *edge(dir);
       *((*edge(dir))->adjanced(dir)) = node;  
       *(node->adjanced(dir)) = nullptr;
       *edge(dir) = node;
   }
}

void List::addLast(shared_ptr<Node> node)
{
 List::add(node, dirForward);
}

void List::addFirst(shared_ptr<Node> node)
{
 List::add(node, dirBackward);
}


shared_ptr<Node> List::get(const int value, const Direction dir)
{
   if( !first) {
       cout << "List is empty!" << endl;
       return nullptr;
   }
   else  {
       shared_ptr<Node> current = *edge(opposite(dir));
       do {
           if(current->value == value)  {
               cout << "Found value " << current->value << endl;
               return current;
           }
           else  {
               cout << "Going through " << current->value << endl;
               current = *(current->adjanced(dir));
           }
       } while(current);
       cout << "Not found: value " << value << endl;
       return nullptr;
   }
}

shared_ptr<Node> List::getForward(const int value)
{
  return get(value, dirForward);
}


shared_ptr<Node> List::getBackward(const int value)
{
  return get(value, dirBackward);

}

int main()
{
   List lista;
   shared_ptr<Node> node4 = make_shared <Node> (4);
   shared_ptr<Node> node7 = make_shared <Node> (7);

   lista.addLast(node4);
   lista.addLast(make_shared <Node> (2));
   lista.addLast(node7);
   lista.addLast(make_shared <Node> (9)); /*
   lista.addFirst(node4);
   lista.addFirst(make_shared <Node> (2));
   lista.addFirst(node7);
   lista.addFirst(make_shared <Node> (9));    */
   auto node = lista.getForward(2);
   node = lista.getBackward(2);
   
   return 0;
}
