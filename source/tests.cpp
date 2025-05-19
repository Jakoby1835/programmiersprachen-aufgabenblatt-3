#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

#include "list.hpp"


// Hilfsfunktionen, um indirekt auf die Member der Klasse List zuzugreifen (nur für die Tests!)
template <typename T>
size_t get_size(List<T> const& list_to_test) {return list_to_test.size_;}

template <typename T>
ListNode<T>* get_first_pointer(List<T> const& list_to_test) {return list_to_test.first_;}

template <typename T>
ListNode<T>* get_last_pointer(List<T> const& list_to_test) {return list_to_test.last_;}

template <typename T>
ListNode<T>* get_node_pointer(ListIterator<T> const& list_iterator_to_test) { return list_iterator_to_test.node_; }


//test case definitions for default constructor of list as well as empty and size for empty list
#include "sub_tests/default_constructed_list.test"


//test case definitions for push methods of list
#include "sub_tests/push_front.test"
#include "sub_tests/push_back.test"

//test case definitions for pop methods of list
#include "sub_tests/pop_front.test"
#include "sub_tests/pop_back.test"

//test case definitions for 

//test cases for element access of list
#include "sub_tests/front.test"
#include "sub_tests/back.test"

//Tests for 1.5
TEST_CASE("copy constructor creates valid copy", "[list_copy]") {
    List<int> original;

    // Test 1: Kopie einer leeren Liste
    {
        List<int> copy(original);
        auto original_first = get_first_pointer(original);
        auto original_last = get_last_pointer(original);
        auto copy_first = get_first_pointer(copy);
        auto copy_last = get_last_pointer(copy);

        SECTION("empty list properties are preserved") {
            REQUIRE(nullptr == original_first);
            REQUIRE(nullptr == original_last);
            REQUIRE(nullptr == copy_first);
            REQUIRE(nullptr == copy_last);
            REQUIRE(original.empty());
            REQUIRE(copy.empty());
        }
    }

    // Test 2: Kopie einer Liste mit einem Element
    original.push_back(42);
    {
        List<int> copy(original);
        auto original_first = get_first_pointer(original);
        auto original_last = get_last_pointer(original);
        auto copy_first = get_first_pointer(copy);
        auto copy_last = get_last_pointer(copy);

        SECTION("single element list properties are preserved") {
            REQUIRE(nullptr != original_first);
            REQUIRE(nullptr != original_last);
            REQUIRE(nullptr != copy_first);
            REQUIRE(nullptr != copy_last);
            REQUIRE(original_first == original_last);
            REQUIRE(copy_first == copy_last);
        }

        SECTION("node links are correct in both lists") {
            REQUIRE(nullptr == original_first->prev);
            REQUIRE(nullptr == original_first->next);
            REQUIRE(nullptr == copy_first->prev);
            REQUIRE(nullptr == copy_first->next);
        }

        SECTION("values are preserved") {
            REQUIRE(42 == original_first->value);
            REQUIRE(42 == copy_first->value);
        }

        SECTION("list sizes match") {
            REQUIRE(1 == get_size(original));
            REQUIRE(1 == get_size(copy));
            REQUIRE(false == original.empty());
            REQUIRE(false == copy.empty());
        }
    }

    // Test 3: Kopie einer Liste mit mehreren Elementen
    original.push_back(13);
    original.push_back(-7);
    {
        List<int> copy(original);
        auto original_first = get_first_pointer(original);
        auto original_last = get_last_pointer(original);
        auto copy_first = get_first_pointer(copy);
        auto copy_last = get_last_pointer(copy);
        auto original_mid = original_first->next;
        auto copy_mid = copy_first->next;

        SECTION("multiple element list properties are preserved") {
            REQUIRE(nullptr != original_first);
            REQUIRE(nullptr != original_last);
            REQUIRE(nullptr != copy_first);
            REQUIRE(nullptr != copy_last);
            REQUIRE(original_first != original_last);
            REQUIRE(copy_first != copy_last);
        }

        SECTION("node links are correct in both lists") {
            REQUIRE(nullptr == original_first->prev);
            REQUIRE(original_mid == original_first->next);
            REQUIRE(original_last == original_mid->next);
            REQUIRE(nullptr == original_last->next);
            REQUIRE(nullptr == copy_first->prev);
            REQUIRE(copy_mid == copy_first->next);
            REQUIRE(copy_last == copy_mid->next);
            REQUIRE(nullptr == copy_last->next);
        }

        SECTION("values are preserved") {
            REQUIRE(42 == original_first->value);
            REQUIRE(13 == original_mid->value);
            REQUIRE(-7 == original_last->value);
            REQUIRE(42 == copy_first->value);
            REQUIRE(13 == copy_mid->value);
            REQUIRE(-7 == copy_last->value);
        }

        SECTION("list sizes match") {
            REQUIRE(3 == get_size(original));
            REQUIRE(3 == get_size(copy));
            REQUIRE(false == original.empty());
            REQUIRE(false == copy.empty());
        }
    }
}
//test cases for retrieving iterators
/*#include "sub_tests/begin.test"
#include "sub_tests/end.test"

//iterator tests
#include "sub_tests/iterators/operator_star.test"
#include "sub_tests/iterators/operator_arrow.test"
#include "sub_tests/iterators/operator_equals.test"
#include "sub_tests/iterators/operator_does_not_equal.test"
#include "sub_tests/iterators/operator_iterate_forward.test"
*/

#include <map>

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}




