/*
 ***************************************************************************************************
 * @brief Unit tests for use_malloc.c where system calls are stubbed out.
 *
 * This is an example showcasing how c code can be unit tested using Google Test along with the
 * Fake Function Framework and some trickery with preprocessor macros. When testing against our
 * own dependencies we can use link-time substitution of a function symbol from the real one with
 * a stub generated by FFF (link seams), but when testing against a system call that needs to be
 * available with its real implementation (e.g. malloc) we can include the .c file directly in the
 * test and use preprocessor macros to redefine the function name of the system call temporarily.
 ***************************************************************************************************
 */

/* Includes */
#include "gtest/gtest.h"
#include "fff.h"

/* Define fakes for syscalls */
FAKE_VALUE_FUNC(void *, _malloc, size_t);
FAKE_VOID_FUNC(_free, void *);
FAKE_VOID_FUNC_VARARG(_printf, const char*, void *, ...);

/* Create preprocessor seam in code under test */
extern "C"
{
#define malloc _malloc
#define free _free
#define printf _printf

#include "use_malloc.c"

#undef malloc
#undef free
#undef printf
}

class UseMallocTest : public ::testing::Test
{
public:
    void SetUp()
    {
        RESET_FAKE(_malloc);
        RESET_FAKE(_free);
        RESET_FAKE(_printf);
        FFF_RESET_HISTORY();
    }
};

/* Define tests */
TEST_F(UseMallocTest, Use_malloc_calls_free_on_malloced_pointer)
{
    uint8_t buffer[sizeof(int)];
    _malloc_fake.return_val = buffer;

    use_malloc();

    EXPECT_EQ(_free_fake.arg0_val, _malloc_fake.return_val);
}

TEST_F(UseMallocTest, Use_malloc_prints_pointer_address)
{
    uint8_t buffer[sizeof(int)];
    _malloc_fake.return_val = buffer;

    use_malloc();

    EXPECT_EQ(_printf_fake.arg1_val, _malloc_fake.return_val);
}
