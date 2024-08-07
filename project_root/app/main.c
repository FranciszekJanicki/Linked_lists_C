#include "SinglyLinkedList.h"
#include "CircularLinkedList.h"
#include "DoublyCircularLinkedList.h"
#include "DoublyLinkedList.h"

/* In C/C++ you cant have same names for variables/functions in the same scope, meaning the global scope (where you define global functions) cant
have variables and functions with same names. The global scope of a program is all of global scopes included together, in C++ you would just use classes as different scopes
or namespaces to avoid repeating names, but in C you have to use prefixes, like here with global functions: */
int main(int, char**) {
    
    /* remember that when function returns staically allocated memory you shouldnt copy its addres, as this addres will get erased after function returns, you should instead 
    copy the memory itself do returnee varaible, copy it to passed memory or member variable, allocate it as static variable or just allocate dynamically on the heap and 
    take pointer to it (like here below) !!! 
    */

    SinglyLinkedHandle_t sl_Handle = sl_listCreateDynamically();
    DoublyLinkedHandle_t dl_Handle = dl_listCreateDynamically();
    CircLinkedHandle_t cl_Handle = cl_listCreateDynamically();
    DoublyCircLinkedHandle_t dcl_Handle = dcl_listCreateDynamically();
    
    return 0;
}