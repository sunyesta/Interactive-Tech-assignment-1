
#pragma once
#ifndef STRING_UTILS_CPP
#define STRING_UTILS_CPP

#include "Assert.hpp"

bool string_cpy(char **pointer, char *string_to_cpy) {
    // makes sure the memory adress of the string is not NULL
    assert_simple(pointer, "pointer must not be NULL");

    // check if string needs to be copied
    if (string_to_cpy == NULL) {
        *pointer = NULL;

        // copies the string
    } else {
        // allocates space for the new string
        *pointer = (char *)malloc(strlen(string_to_cpy) * sizeof(char) + 1);

        // if allocating space failed, return false to show that it was not
        // successful
        if (*pointer == NULL) {
            return false;
        }

        // copy the string character by character into *pointer
        strcpy(*pointer, string_to_cpy);
    }

    // copying the string was successful
    return true;
}

#endif /* STRING_UTILS_CPP */
