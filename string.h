#ifndef MOPER_STL_STRING_H
#define MOPER_STL_STRING_H

#include "basic_string.h"

namespace MoperSTL {

using string = MoperSTL::basic_string<char>;
using wstring = MoperSTL::basic_string<wchar_t>;
using u16string = MoperSTL::basic_string<char16_t>;
using u32string = MoperSTL::basic_string<char32_t>;

}; /* MoperSTL */

#endif /* MOPER_STL_STRING_H */