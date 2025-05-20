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

//Tests for 3.5
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

//Tests for 3.6
/*TEST_CASE("swap function exchanges list contents", "[list_swap]") {
    List<int> list1;
    List<int> list2;

    // Test 1: Swap empty lists
    {
        list1.swap(list2);
        auto l1_first = get_first_pointer(list1);
        auto l1_last = get_last_pointer(list1);
        auto l2_first = get_first_pointer(list2);
        auto l2_last = get_last_pointer(list2);

        SECTION("empty lists remain empty after swap") {
            REQUIRE(nullptr == l1_first);
            REQUIRE(nullptr == l1_last);
            REQUIRE(nullptr == l2_first);
            REQUIRE(nullptr == l2_last);
            REQUIRE(list1.empty());
            REQUIRE(list2.empty());
        }
    }

    // Test 2: Swap with one empty and one non-empty list
    list1.push_back(42);
    {
        List<int> original1 = list1;
        List<int> original2 = list2;

        list1.swap(list2);

        auto l1_first = get_first_pointer(list1);
        auto l1_last = get_last_pointer(list1);
        auto l2_first = get_first_pointer(list2);
        auto l2_last = get_last_pointer(list2);

        SECTION("non-empty list becomes empty") {
            REQUIRE(nullptr == l1_first);
            REQUIRE(nullptr == l1_last);
            REQUIRE(list1.empty());
        }

        SECTION("empty list becomes non-empty") {
            REQUIRE(nullptr != l2_first);
            REQUIRE(nullptr != l2_last);
            REQUIRE(l2_first == l2_last);
            REQUIRE(42 == l2_first->value);
            REQUIRE(1 == get_size(list2));
        }
    }

    // Test 3: Swap two non-empty lists
    list1.clear();
    list1.push_back(1);
    list1.push_back(2);
    list2.push_back(3);
    list2.push_back(4);
    list2.push_back(5);
    {
        List<int> original1 = list1;
        List<int> original2 = list2;

        list1.swap(list2);

        auto l1_first = get_first_pointer(list1);
        auto l1_last = get_last_pointer(list1);
        auto l2_first = get_first_pointer(list2);
        auto l2_last = get_last_pointer(list2);

        SECTION("first list takes second list's contents") {
            REQUIRE(nullptr != l1_first);
            REQUIRE(nullptr != l1_last);
            REQUIRE(l1_first->next == l1_last);  // Korrigiert: Nur für Listen mit zwei Elementen
            REQUIRE(3 == l1_first->value);
            REQUIRE(4 == l1_last->value);
            REQUIRE(2 == get_size(list1));
        }

        SECTION("second list takes first list's contents") {
            REQUIRE(nullptr != l2_first);
            REQUIRE(nullptr != l2_last);
            REQUIRE(l2_first->next == l2_last);  // Korrigiert: Nur für Listen mit zwei Elementen
            REQUIRE(1 == l2_first->value);
            REQUIRE(2 == l2_last->value);
            REQUIRE(2 == get_size(list2));
        }
    }
}*/
TEST_CASE("unifying assignment operator copies list contents", "[list_assignment]") {
    List<int> list1;
    List<int> list2;

    // Test 1: Assignment of empty list
    {
        list2 = list1;
        auto l1_first = get_first_pointer(list1);
        auto l1_last = get_last_pointer(list1);
        auto l2_first = get_first_pointer(list2);
        auto l2_last = get_last_pointer(list2);

        SECTION("empty list assignment") {
            REQUIRE(nullptr == l1_first);
            REQUIRE(nullptr == l1_last);
            REQUIRE(nullptr == l2_first);
            REQUIRE(nullptr == l2_last);
            REQUIRE(list1.empty());
            REQUIRE(list2.empty());
        }
    }

    // Test 2: Assignment of non-empty list to empty list
    list1.push_back(42);
    {
        List<int> original = list1;
        list2 = list1;

        auto l1_first = get_first_pointer(list1);
        auto l1_last = get_last_pointer(list1);
        auto l2_first = get_first_pointer(list2);
        auto l2_last = get_last_pointer(list2);

        SECTION("original list remains unchanged") {
            REQUIRE(nullptr != l1_first);
            REQUIRE(nullptr != l1_last);
            REQUIRE(l1_first == l1_last);
            REQUIRE(42 == l1_first->value);
            REQUIRE(1 == get_size(list1));
        }

        SECTION("assigned list has correct contents") {
            REQUIRE(nullptr != l2_first);
            REQUIRE(nullptr != l2_last);
            REQUIRE(l2_first == l2_last);
            REQUIRE(42 == l2_first->value);
            REQUIRE(1 == get_size(list2));
        }
    }

    // Test 3: Assignment of two non-empty lists
    list1.clear();
    list1.push_back(1);
    list1.push_back(2);
    list2.push_back(3);
    list2.push_back(4);
    list2.push_back(5);
    {
        List<int> original = list1;
        list2 = list1;

        auto l1_first = get_first_pointer(list1);
        auto l1_last = get_last_pointer(list1);
        auto l2_first = get_first_pointer(list2);
        auto l2_last = get_last_pointer(list2);

        SECTION("original list remains unchanged") {
            REQUIRE(nullptr != l1_first);
            REQUIRE(nullptr != l1_last);
            REQUIRE(l1_first->next == l1_last);
            REQUIRE(1 == l1_first->value);
            REQUIRE(2 == l1_last->value);
            REQUIRE(2 == get_size(list1));
        }

        SECTION("assigned list has correct contents") {
            REQUIRE(nullptr != l2_first);
            REQUIRE(nullptr != l2_last);
            REQUIRE(l2_first->next == l2_last);
            REQUIRE(1 == l2_first->value);
            REQUIRE(2 == l2_last->value);
            REQUIRE(2 == get_size(list2));
        }
    }
}

//Tests for 3.7
/*TEST_CASE("Reverse an empty list", "[list_reverse]") {
    List<int> list;
    list.reverse();

    REQUIRE(list.empty());
}*/
TEST_CASE("Reverse a list with a single element", "[list_reverse]") {
    List<int> list;
    list.push_back(42);
    list.reverse();

    auto first = get_first_pointer(list);
    auto last = get_last_pointer(list);

    SECTION("List remains unchanged") {
        REQUIRE(nullptr != first);
        REQUIRE(nullptr != last);
        REQUIRE(first == last);
        REQUIRE(42 == first->value);
        REQUIRE(1 == get_size(list));
    }
}
TEST_CASE("Reverse a list with multiple elements", "[list_reverse]") {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.reverse();

    auto first = get_first_pointer(list);
    auto last = get_last_pointer(list);

    SECTION("List elements are reversed") {
        REQUIRE(nullptr != first);
        REQUIRE(nullptr != last);
        REQUIRE(3 == first->value);
        REQUIRE(1 == last->value);
        REQUIRE(3 == get_size(list));
    }
}
TEST_CASE("Reverse twice should restore original order", "[list_reverse]") {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.reverse();
    list.reverse();

    auto first = get_first_pointer(list);
    auto last = get_last_pointer(list);

    SECTION("List order is restored") {
        REQUIRE(nullptr != first);
        REQUIRE(nullptr != last);
        REQUIRE(1 == first->value);
        REQUIRE(3 == last->value);
        REQUIRE(3 == get_size(list));
    }
    list.push_back(42);
    list.push_back(42);
}

TEST_CASE("Reverse a list with a single element (free function)", "[list_reverse]") {
    List<int> list;
    list.push_back(42);
    auto reversed = reverse(list);

    auto first = get_first_pointer(reversed);
    auto last = get_last_pointer(reversed);

    SECTION("List remains unchanged") {
        REQUIRE(nullptr != first);
        REQUIRE(nullptr != last);
        REQUIRE(first == last);
        REQUIRE(42 == first->value);
        REQUIRE(1 == get_size(reversed));
    }
}

TEST_CASE("Reverse a list with multiple elements (free function)", "[list_reverse]") {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    auto reversed = reverse(list);

    auto first = get_first_pointer(reversed);
    auto last = get_last_pointer(reversed);

    SECTION("List elements are reversed") {
        REQUIRE(nullptr != first);
        REQUIRE(nullptr != last);
        REQUIRE(3 == first->value);
        REQUIRE(1 == last->value);
        REQUIRE(3 == get_size(reversed));
    }
}

TEST_CASE("Reverse twice should restore original order (free function)", "[list_reverse]") {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    auto reversed_once = reverse(list);
    auto reversed_twice = reverse(reversed_once);

    auto first = get_first_pointer(reversed_twice);
    auto last = get_last_pointer(reversed_twice);

    SECTION("List order is restored") {
        REQUIRE(nullptr != first);
        REQUIRE(nullptr != last);
        REQUIRE(1 == first->value);
        REQUIRE(3 == last->value);
        REQUIRE(3 == get_size(reversed_twice));
    }
}

TEST_CASE("Reverse an empty list (free function)", "[list_reverse]") {
    List<int> list;
    auto reversed = reverse(list);

    auto first = get_first_pointer(reversed);
    auto last = get_last_pointer(reversed);

    SECTION("List is still empty") {
        REQUIRE(nullptr == first);
        REQUIRE(nullptr == last);
        REQUIRE(0 == get_size(reversed));
    }
}

TEST_CASE("Reverse a list with duplicate elements (free function)", "[list_reverse]") {
    List<int> list;
    list.push_back(7);
    list.push_back(7);
    list.push_back(42);
    list.push_back(7);
    auto reversed = reverse(list);

    auto first = get_first_pointer(reversed);
    auto last = get_last_pointer(reversed);

    SECTION("List is reversed correctly with duplicates") {
        REQUIRE(nullptr != first);
        REQUIRE(nullptr != last);
        REQUIRE(7 == first->value);
        REQUIRE(7 == last->value);
        REQUIRE(4 == get_size(reversed));
    }
}

TEST_CASE("Reverse a list of strings (free function)", "[list_reverse]") {
    List<std::string> list;
    list.push_back("a");
    list.push_back("b");
    list.push_back("c");
    auto reversed = reverse(list);

    auto first = get_first_pointer(reversed);
    auto last = get_last_pointer(reversed);

    SECTION("String list is reversed") {
        REQUIRE(nullptr != first);
        REQUIRE(nullptr != last);
        REQUIRE("c" == first->value);
        REQUIRE("a" == last->value);
        REQUIRE(3 == get_size(reversed));
    }
}

TEST_CASE("Reverse a list of booleans (free function)", "[list_reverse]") {
    List<bool> list;
    list.push_back(true);
    list.push_back(false);
    list.push_back(true);
    auto reversed = reverse(list);

    auto first = get_first_pointer(reversed);
    auto last = get_last_pointer(reversed);

    SECTION("Boolean list is reversed") {
        REQUIRE(nullptr != first);
        REQUIRE(nullptr != last);
        REQUIRE(true == first->value);
        REQUIRE(true == last->value);
        REQUIRE(3 == get_size(reversed));
    }
}
TEST_CASE("Compare string lists with same content", "[list_compare][string]") {
    List<std::string> list1;
    List<std::string> list2;

    list1.push_back("hello");
    list1.push_back("world");

    list2.push_back("hello");
    list2.push_back("world");

    SECTION("String lists with identical content") {
        REQUIRE(list1 == list2);
        REQUIRE_FALSE(list1 != list2);
    }
}

TEST_CASE("Compare string lists with different content", "[list_compare][string]") {
    List<std::string> list1;
    List<std::string> list2;

    list1.push_back("hello");
    list1.push_back("world");

    list2.push_back("hello");
    list2.push_back("WORLD"); // Groß-/Kleinschreibung unterscheidet sich

    SECTION("String lists differ in casing") {
        REQUIRE(list1 != list2);
        REQUIRE_FALSE(list1 == list2);
    }
}

TEST_CASE("Compare string lists with different lengths", "[list_compare][string]") {
    List<std::string> list1;
    List<std::string> list2;

    list1.push_back("only one");

    SECTION("One list has an element, one is empty") {
        REQUIRE(list1 != list2);
        REQUIRE_FALSE(list1 == list2);
    }
}

TEST_CASE("Compare two empty string lists", "[list_compare][string]") {
    List<std::string> list1;
    List<std::string> list2;

    SECTION("Both are empty, so equal") {
        REQUIRE(list1 == list2);
        REQUIRE_FALSE(list1 != list2);
    }
}
TEST_CASE("Compare two empty lists for equality", "[list_compare]") {
    List<int> list1;
    List<int> list2;

    SECTION("Both lists are empty, should be equal") {
        REQUIRE(list1 == list2);
        REQUIRE_FALSE(list1 != list2);
    }
}

TEST_CASE("Compare identical lists with one element", "[list_compare]") {
    List<int> list1;
    List<int> list2;
    list1.push_back(42);
    list2.push_back(42);

    SECTION("Both lists have one identical element") {
        REQUIRE(list1 == list2);
        REQUIRE_FALSE(list1 != list2);
    }
}

TEST_CASE("Compare lists with different sizes", "[list_compare]") {
    List<int> list1;
    List<int> list2;

    list1.push_back(1);
    list1.push_back(2);

    list2.push_back(1);

    SECTION("Lists have different lengths") {
        REQUIRE(list1 != list2);
        REQUIRE_FALSE(list1 == list2);
    }
}

TEST_CASE("Compare lists with same size but different elements", "[list_compare]") {
    List<int> list1;
    List<int> list2;

    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);

    list2.push_back(1);
    list2.push_back(2);
    list2.push_back(4); // Unterschied hier

    SECTION("Same size, different values") {
        REQUIRE(list1 != list2);
        REQUIRE_FALSE(list1 == list2);
    }
}

TEST_CASE("Compare identical lists with multiple elements", "[list_compare]") {
    List<int> list1;
    List<int> list2;

    for (int i = 0; i < 5; ++i) {
        list1.push_back(i);
        list2.push_back(i);
    }

    SECTION("Lists with identical sequences") {
        REQUIRE(list1 == list2);
        REQUIRE_FALSE(list1 != list2);
    }
}

TEST_CASE("Compare lists of different types (should not compile)", "[list_compare][compile_error]") {
    // Dieser Test ist rein illustrativ.
    // Ein Vergleich von List<int> mit List<std::string> sollte durch den Compiler verhindert werden.
    // Daher wird er hier nicht ausgeführt.
    SUCCEED("Typisierte Listen lassen sich nicht direkt vergleichen – Kompilerfehler gewünscht.");
}

TEST_CASE("Compare list with itself", "[list_compare]") {
    List<int> list;
    list.push_back(5);
    list.push_back(10);

    SECTION("List should be equal to itself") {
        REQUIRE(list == list);
        REQUIRE_FALSE(list != list);
    }
}




//test cases for retrieving iterators
#include "sub_tests/begin.test"
#include "sub_tests/end.test"

//iterator tests
/*#include "sub_tests/iterators/operator_star.test"
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




