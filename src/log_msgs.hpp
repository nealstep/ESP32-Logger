#pragma once

#define SEVERITY_LIST(X) \
    X(Dbg, "Debug")      \
    X(Inf, "Info")       \
    X(Wrn, "Warning")    \
    X(Err, "Error")      \
    X(All, "All")

#define BASE_UNIT_LIST(X)

#define BASE_ERROR_LIST(X) \
    X(NoError, "No Error") \
    X(UnexpectedError, "Unexpected Error")

#define BASE_NOTICE_LIST(X) X(NoNotice, "No Notice")

#define BASE_WORD_LIST(X) X(Unknown, "Unknown")

// edit his file for messages includes from your libraries
#include "main_msgs.hpp"

#define UNIT_LIST(X)  \
    BASE_UNIT_LIST(X) \
    MAIN_UNIT_LIST(X) \
    X(Last, "Last+1")

#define ERROR_LIST(X)  \
    BASE_ERROR_LIST(X) \
    MAIN_ERROR_LIST(X)

#define NOTICE_LIST(X)  \
    BASE_NOTICE_LIST(X) \
    MAIN_NOTICE_LIST(X)

#define WORD_LIST(X)  \
    BASE_WORD_LIST(X) \
    MAIN_WORD_LIST(X)
