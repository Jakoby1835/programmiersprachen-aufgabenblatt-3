#ifndef BUW_LIST_ITERATOR_HPP
#define BUW_LIST_ITERATOR_HPP

#include "list_node.hpp"

//TODO: Implementierung der Methoden des Iterators (Aufgabe 3.10)
template <typename T>
struct ListIterator {
public:

    //friend declarations for testing the members   
    template <typename TEST_TYPE>
    friend ListNode<TEST_TYPE>* get_node_pointer(ListIterator<TEST_TYPE> const& list_iterator_to_test);

    using Self = ListIterator<T>;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using difference_type = ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;

    //default constructor with default-member initialization will not be implemented
    ListIterator() = default;
    //user defined constructor implementation is provided below
    ListIterator(ListNode<T>* node);

    /* Declaration of operator*() */
    T& operator*()  const;

    /* Declaration of operator->() */
    T* operator->() const;

    /* Declaration of PREINCREMENT-operator, call: ++it, advances one element forward */
    ListIterator<T>& operator++();

    /* Declaration of POSTINCREMENT (signature distinguishes the iterators),
                      call:  it++, advances one element forward */
    ListIterator<T> operator++(int);

    /* Declaration of comparison-operator in terms of equality */
    bool operator==(ListIterator<T> x) const;

    /* Declaration of comparison-operator in terms of inequality */
    bool operator!=(ListIterator<T> x) const;

    /* Advances Iterator */
    ListIterator<T> next() const;

    ListNode<T>* get_node() const;

private:
    //only member variable, pointer to the underlying node (see list_node.hpp)
    ListNode <T>* node_ = nullptr;
};


//user-defined constructor is already completely implemented
template<typename T>
ListIterator<T>::ListIterator(ListNode<T>* node) : node_{ node } 
{}

/* ======================================== *
 * BEGIN COMMENTING AND IMPLEMENTATION HERE *
 * ======================================== */

 //=========================
 // (Aufgabe 3.10 - Teil 1)
 /* Dereferenzierungsoperator *
    Gibt eine Referenz auf den Wert des Knotens zurück, auf den der Iterator zeigt. */
template <typename T>
T& ListIterator<T>::operator*() const {
    if (nullptr == node_) {
        throw "Iterator does not point to valid node";
    }
    return node_->value;
}

//=========================
// (Aufgabe 3.10 - Teil 2)
/* Dereferenzierungsoperator ->
   Gibt einen Zeiger auf das Element zurück, auf das der Iterator zeigt.
   Ermöglicht Zugriff auf Member des Elements (z. B. it->member). */
template <typename T>
T* ListIterator<T>::operator->() const {
    if (nullptr == node_) {
        throw "Iterator does not point to valid node";
    }
    return &(node_->value);
}

//=========================
// (Aufgabe 3.10 - Teil 3)
/* Präinkrement-Operator (++it)
   Bewegt den Iterator auf das nächste Element und gibt eine Referenz auf sich selbst zurück. */
template <typename T>
ListIterator<T>& ListIterator<T>::operator++() {
    if (nullptr == node_) {
        throw "Iterator does not point to valid node";
    }
    node_ = node_->next;
    return *this;
}

//=========================
// (Aufgabe 3.10 - Teil 4)
/* Postinkrement-Operator (it++)
   Gibt den aktuellen Iterator zurück und bewegt ihn anschließend auf das nächste Element. */
template <typename T>
ListIterator<T> ListIterator<T>::operator++(int) {
    if (nullptr == node_) {
        throw "Iterator does not point to valid node";
    }
    ListIterator<T> temp = *this;
    node_ = node_->next;
    return temp;
}

//=========================
// (Aufgabe 3.10 - Teil 5)
/* Vergleichsoperator ==
   Zwei Iteratoren sind gleich, wenn sie auf denselben Knoten zeigen. */
template <typename T>
bool ListIterator<T>::operator==(ListIterator<T> x) const {
    return node_ == x.node_;
}

//=========================
// (Aufgabe 3.10 - Teil 6)
/* Vergleichsoperator !=
   Zwei Iteratoren sind ungleich, wenn sie nicht auf denselben Knoten zeigen.
   Reimplementiert über operator==. */
template <typename T>
bool ListIterator<T>::operator!=(ListIterator<T> x) const {
    return !(*this == x);
}

//=========================
// is already implemented
template <typename T>
ListIterator<T> ListIterator<T>::next() const {
    if (nullptr != node_) {
        return ListIterator{ node_->next };
    }
    else {
        return ListIterator{ nullptr };
    }
}

template <typename T>
ListNode<T>* ListIterator<T>::get_node() const {
    return node_;
}

#endif // #ifndef BUW_LIST_ITERATOR_HPP