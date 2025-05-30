#ifndef BUW_LIST_HPP
#define BUW_LIST_HPP

#include "list_node.hpp"
#include "list_iterator.hpp"

#include <cassert>
#include <cstddef>  //ptrdiff_t
#include <iterator> //std::bidirectional_iterator_tag
#include <iostream>

#include <initializer_list>

// forward declaration of template list class
template <typename T>
class List;

// forward declaration of free function "reverse"
template <typename T>
List<T> reverse(List<T> const& list_to_reverse);

template <typename T>
List<T> operator+(List<T> const& lhs, List<T> const& rhs);

template <typename T>
class List {
  public:

    //friend declarations for testing the members   
    template <typename TEST_TYPE>
    friend size_t get_size(List<TEST_TYPE> const& list_to_test);
    template <typename TEST_TYPE>
    friend ListNode<TEST_TYPE>* 
      get_first_pointer(List<TEST_TYPE> const& list_to_test);
    template <typename TEST_TYPE>
    friend ListNode<TEST_TYPE>* 
      get_last_pointer(List<TEST_TYPE> const& list_to_test);

    using value_type      = T;
    using pointer         = T*;
    using const_pointer   = T const*;
    using reference       = T&;
    using const_reference = T const&;
    using iterator        = ListIterator<T>;

    /* Declaration of Default Constructor */
    List();
    
    /* Declaration of Copy Constructor using Deep-Copy Semantics */
    List(List const& rhs);

    /* Declaration of Move Constructor */
    List(List&& rhs);

    /* Declaration of Initializer-List-based Constructor */
    List(std::initializer_list<T> ini_list);

    /* Declaration of Destructor */
    ~List();

    /* Declaration of Unifying Assignment Operator - see: Vorlesung 6, pp. 11-13, watch video explanation!*/
    List& operator=(List rhs);

    /* Declaration of built-in Member-Swap method used by Unifying Assignment Operator */
    void swap(List& rhs);

    /* Declaration of list-comparison-operator in terms of equality */
    bool operator==(List const& rhs) const;

    /* Declaration of list-comparison-operator in terms of inequality */
    bool operator!=(List const& rhs) const;
    
    /* Declaration of size-Method */
    std::size_t size() const;

    /* Declaration of empty-Method */
    bool empty() const;

    /* Declaration of push_front-Method */
    void push_front(T const& element);

    /* Declaration of pop_front-Method */
    void pop_front();

    /* Declaration of push_front-Method */
    void push_back(T const& element);

    /* Declaration of push_front-Method */
    void pop_back();

    /* Declaration of front-Method */
    T& front();

    /* Declaration of back-Method */
    T& back();

    /* Declaration of clear-Method */
    void clear();

    /* Declaration of reverse-Method*/
    void reverse();

    /* Declaration of begin-Method returning a ListIterator refering to the first list_node */
    ListIterator<T> begin();
    /* Declaration of end-Method returning a ListIterator refering to the past-the-end-element which marks the end of the list*/
    ListIterator<T> end();

    /* Declaration of insert-Method */
    ListIterator<T> insert(ListIterator<T> const& position, T const& value);
    /* Declaration of erase-Method */
    ListIterator<T> erase(ListIterator<T> const& position);

  // list members
  private: 
    std::size_t size_;
    ListNode<T>* first_;
    ListNode<T>* last_;
};

/* ======================================== *
 * BEGIN COMMENTING AND IMPLEMENTATION HERE *
 * ======================================== */

 //=========================
// not fully implemented yet
/* Aufgabe 3.2 - Teil 1 */
/* Die Stadartkonstruktion: Die stadtert gr��e ist 0 also sind die beiden pointer auch 0 also nullpointer */
template <typename T>
List<T>::List():size_(0), first_(nullptr), last_(nullptr) {}

//=========================
// test and implement
/* Aufgabe 3.2 - Teil 2 */
/* gibt size_ zur�ck da es sich dabei um die gr��e der Liste handelt */
template <typename T>
std::size_t List<T>::size() const {
    return size_;
};

//=========================
// test and implement
/* Aufgabe 3.2 - Teil 3 */
/* die list ist ja leer wenn die anzahl an elemnten 0 ist, also wird true zur�ck gegeben wenn die size_ 0 ist*/
template <typename T>
bool List<T>::empty() const {
    // check whether size member variable is zero -- this should be a one line implementation
    return size_ == 0;
};

//=========================
/* Aufgabe 3.3 - Teil 1 */
/*Wenn die Liste leer ist, zeigen beide (first,last) auf ein Listenelement, wenn nicht wird wird vo vorherigen first, der prev ge�ndert, dann wird der firstpointer auf das neue element gesetzt, und am ender wird die size +1*/
template <typename T>
void List<T>::push_front(T const& element) {
    // TODO: push_front-method (Aufgabe 3.3)
    ListNode<T>* new_node = new ListNode<T>(element, nullptr, first_); //altes first
    if (empty()) {
        first_ = new_node;
        last_ = first_;
    }
    else {
        first_->prev = new_node; //altes first
        first_ = new_node; //neues first
    }
    size_++;
}

//=========================
/* Aufgabe 3.3 - Teil 2 */
/*als erstes wird sich das erste element geg�nnt, von dem wird den next genommen, dann l�schen wir first, und machen v_node zum ersten, wenn es jetzt mindestens 2 gibt sind wir fertig*/
template <typename T>
void List<T>::pop_front() {
    if (empty()) {
        throw "List is empty";
    }
    else {
        ListNode<T>* v_node = first_->next;
        delete first_;
        first_ = v_node;
        if (first_ != nullptr) {
            first_->prev = nullptr;
        } 
        else {
            last_ = nullptr;
        }
        size_--;
    }

    // TODO: remainder of pop_front-method (Aufgabe 3.3)
}

//=========================
/* Aufgabe 3.3 - Teil 3 */
/* erst wird ein neues element erstellt und das prev davon zeigt auf dem vorherigen last, ist die liste leer machen wir noch first zu last, und wir sind fertig, wenn nicht, �ndern wir das next vom vorherigen last und �ndern das last, zur neuen node */
template <typename T>
void List<T>::push_back(T const& element) {
    // TODO: push_back-method (Aufgabe 3.3)
    ListNode<T>* new_node = new ListNode<T>(element, last_, nullptr); //altes first
    if (empty()) {
        last_ = new_node;
        first_ = last_;
    }
    else 
    {
        last_->next = new_node; //altes first
        last_ = new_node; //neues first
    }
    size_++;
}


//=========================
/* Aufgabe 3.3 - Teil 4 */
/* Gleiches prinzip  wie ebi Teil 2 nur das ich die wertr niegiert habe next -> prev, first_ -> last_ */
template <typename T>
void List<T>::pop_back() {
    if (empty()) {
        throw "List is empty";
    }
    else 
    {
        ListNode<T>* v_node = last_->prev;
        delete last_;
        last_ = v_node;
        if (last_ != nullptr) {
            last_->next = nullptr;
        }
        else {
            first_ = nullptr;
        }
        size_--;
    }

    // TODO: remainder of pop_back-method (Aufgabe 3.3)
}

//=========================
/* Aufgabe 3.3 - Teil 5 */
/* gibt den inhlat des ersten listnode aus */
template <typename T>
T& List<T>::front() {
    if (empty()) {
        throw "List is empty";
    }
    else {
        return first_->value;
    }
    // TODO: remainder of front-method (Aufgabe 3.3)
}

//=========================
/* Aufgabe 3.3 - Teil 6 */
/* gibt den inhlat des letzten listnode aus */
template <typename T>
T& List<T>::back() {
    if (empty()) {
        throw "List is empty";
    }
    else {
        return last_->value;
    }

    // TODO: remainder of back-method (Aufgabe 3.3)
}

//=========================
// test and implement:
// TODO: clear 
// Aufgabe 3.4 - Teil 1
/* l�scht so lange alles bis size 0 ist */
template <typename T>
void List<T>::clear() {
    while (size_ != 0) {
        pop_back();
    }
}

//=========================
// test and implement:
// TODO: List Destructor implemented by calling clear
// Aufgabe 3.4 - Teil 2
/* ruft clear auf */
template <typename T>
List<T>::~List() {
    clear();
} //can not be tested with unit tests

//=========================
// test and implement:
//TODO: Copy-Konstruktor using Deep-Copy semantics 
// Aufgabe 3.5
/* als erstes wird das defoult zu 0 und nullpointer gesetzt, dann wird eine indexnode erstellt die genutzt wird f�r die while schleife, wenn es sich nicht um ein nullpointer handelt wird dein elemt erstellt,
in der zweioten list, basically geht wihle von hinten die liste duch und erstellt nodes in der zweiten liste, solnage bis das n�chste elment auf ein nullpointer zeigt, dann h�rt er auf, da ja bei heden push front die liste verschoben wird,
ist am ende die liste in der richtigen reinfolge*/
template <typename T>
List<T>::List(List<T> const& rhs) : size_(0), first_(nullptr), last_(nullptr) {
    //if (!rhs.empty()) {
        ListNode<T>* index = rhs.last_;
        while (index != nullptr) {
            push_front(index->value);
            index = index->prev;
        }
    //}
}

//=========================
// test and implement:
// TODO: helper-swap-method for bultin-types used by unifying assignment operator (see Vorlesung 6, pp. 11-13)
// Aufgabe 3.6 - Teil 1
/* Swapt den kopf der der Liste */
template <typename T>
void List<T>::swap(List<T>& rhs) {
    std::swap(first_, rhs.first_);
    std::swap(last_, rhs.last_);
    std::swap(size_, rhs.size_);
}

//=========================
// test and implement:
// TODO: unyfing assignment operator (see Vorlesung 6, pp. 11-13)
// Aufgabe 3.6 - Teil 2
/* wendet alles an */
template <typename T>
List<T>& List<T>::operator=(List<T> rhs) {
    swap(rhs);
    return *this;
}

//=========================
// Aufgabe 3.7 - Teil 1 (liste umdehene)
/* als erstes wird die liste von hinten bis vorne durchgegangen, und diese conteiner werden hinten angesetzt, jetzt haben wir forne die liste normal, und hinten die liste reverse,
jetzt pop_fronten wir size/2 mal, und l�schen somit die alte liste, �brig bleibt nur noch die reverse lsite */
template <typename T>
void List<T>::reverse() {
    if (!empty()) {
        ListNode<T>* index = last_;
        int original_size = size_;  // Merke urspr�ngliche Gr��e

        // Baue reversed Kopie hinten an
        while (index != nullptr) {
            push_back(index->value);
            index = index->prev;
        }

        // Entferne vordere H�lfte (die Original-Liste)
        for (int i = 0; i < original_size; ++i) {
            pop_front();
        }
    }
}
//=========================
// Aufgabe 3.7 - Teil 2 (same aber als freie funktion)
/* ... */
template <typename T>
List<T> reverse(List<T> const& list_to_reverse) {
    List<T> temp{ list_to_reverse };
    temp.reverse();
    return temp;
}

//========================= (wann gleich oder ungleich)
// Aufgabe 3.8 - Teil 1
/* Zwei Listen sind gleich (==), wenn:
   - Sie die gleiche Anzahl an Elementen enthalten.
   - Jedes Element in gleicher Reihenfolge identisch ist (per == vergleichbar).
*/
template <typename T>
bool List<T>::operator==(List const& rhs) const {
    // Falls die Gr��en unterschiedlich sind, k�nnen sie nicht gleich sein.
    if (this->size_ != rhs.size_) {
        return false;
    }

    // Vergleiche Element f�r Element mit zwei Zeigern
    ListNode<T>* left = this->first_;
    ListNode<T>* right = rhs.first_;

    while (left != nullptr && right != nullptr) {
        if (!(left->value == right->value)) {
            return false; // ungleiches Paar gefunden
        }
        left = left->next;
        right = right->next;
    }

    // Wenn beide Listen gleichzeitig enden, sind sie gleich
    return true;
}

//=========================
// Aufgabe 3.8 - Teil 2
/* Zwei Listen sind ungleich (!=), wenn sie nicht gleich sind.
   Diese Funktion nutzt die bereits implementierte Logik von operator==.
*/
template <typename T>
bool List<T>::operator!=(List const& rhs) const {
    return !(*this == rhs);
}

//=========================
// Aufgabe 3.9 - Teil 1
/* Gibt einen Iterator zur�ck, der auf das erste Element der Liste zeigt.
   Falls die Liste leer ist, zeigt der Iterator auf nullptr.
*/
template <typename T>
ListIterator<T> List<T>::begin() {
    return ListIterator<T>{first_};
}

//=========================
// Aufgabe 3.9 - Teil 2
/* Gibt einen Iterator zur�ck, der auf das Element nach dem letzten zeigt.
   Daf�r wird ein Iterator mit nullptr zur�ckgegeben (standardkonform).
*/
template <typename T>
ListIterator<T> List<T>::end() {
    return ListIterator<T>{nullptr};
}


//=========================
// Aufgabe 3.11
/* F�gt ein neues Element *value* vor der Position *position* ein.
   Verwendet den Iterator, um in O(1) Zeit das Element einzuf�gen.
   Gibt einen Iterator auf das neu eingef�gte Element zur�ck.
*/
template <typename T>
ListIterator<T> List<T>::insert(ListIterator<T> const& position, T const& value) {
    ListNode<T>* pos_node = position.get_node();

    // Neuer Knoten, der eingef�gt wird
    ListNode<T>* new_node = new ListNode<T>{ value, nullptr, nullptr };

    if (pos_node == nullptr) {
        // Einf�gen am Ende der Liste (position == end())
        if (empty()) {
            // Liste war leer
            first_ = last_ = new_node;
        }
        else {
            // Anh�ngend an last_
            new_node->prev = last_;
            last_->next = new_node;
            last_ = new_node;
        }
    }
    else if (pos_node == first_) {
        // Einf�gen vor dem ersten Element (also ganz vorne)
        new_node->next = first_;
        first_->prev = new_node;
        first_ = new_node;
    }
    else {
        // Einf�gen irgendwo in der Mitte
        new_node->next = pos_node;
        new_node->prev = pos_node->prev;
        if (pos_node->prev) {
            pos_node->prev->next = new_node;
        }
        pos_node->prev = new_node;
    }

    ++size_;  // Gr��e der Liste erh�hen

    return ListIterator<T>{new_node};
}


//=========================
// Aufgabe 3.12
/* ... */
template <typename T>
ListIterator<T> List<T>::erase(ListIterator<T> const& position) {

}

//=========================
// Aufgabe 3.13 is a copy test and should be implemented in a cpp file

//=========================
// test and implement:
// TODO: Move-Konstruktor (Aufgabe 3.14)
/* ... */
template <typename T>
List<T>::List(List<T>&& rhs) {}

//=========================
// test and implement:
//TODO: Initializer - List Konstruktor (3.15 - Teil 1)
/* ...  */
template <typename T>
List<T>::List(std::initializer_list<T> ini_list) {
    //not implemented yet
}

//=========================
// Aufgabe 3.15 - Teil 2
/* ... */
template <typename T>
List<T> operator+(List<T> const& lhs, List<T> const& rhs) {

}


#endif // #ifndef BUW_LIST_HPP