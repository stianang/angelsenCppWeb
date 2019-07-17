#ifndef TESTS_ASSERT_HPP
#define TESTS_ASSERT_HPP

#include <cstdlib>
#include <iostream>

#define ASSERT(e) ((void)((e) ? ((void)0) : ((void)(std::cerr << "Assertion failed: (" << #e << "), function " << __func__ << ", file " << __FILE__ << ", line " << __LINE__ << ".\n"), std::abort())))

#endif /* TESTS_ASSERT_HPP */
