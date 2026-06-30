#pragma once

#define BASE_UNIT_LIST(X)

#define BASE_ERROR_LIST(X) \
    X(NoError, "No Error") \
    X(UnexpectedError, "Unexpected Error")

#define BASE_NOTICE_LIST(X) X(NoNotice, "No Notice")

#define BASE_WORD_LIST(X) X(Unknown, "Unknown")
