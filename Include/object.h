// Copyright (c) 2025-present Dinh Son Hai
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef MERCURY_OBJECT_HEADER_FILE
#define MERCURY_OBJECT_HEADER_FILE

#include "..\Mercury\type.cpp"
#include "..\Mercury\global.cpp"

typedef struct _pcode           mCode_T;
typedef struct _code            mOpCode_T;
typedef struct _type            mType_T;
typedef struct _val             mValue_T;
typedef struct _string          mString_T;
typedef struct _variable        mVariable_T;
typedef struct _func_object     mFunc_object_T;
typedef struct _list_object     mList_T;
typedef struct _object          mObject_T;
typedef struct __iter           mIter_T;
typedef __global_table   GlobalTable;
typedef void* (*mFunc_T)();
typedef void* (*Point_to)();

#endif // MERCURY_OBJECT_HEADER_FILE
