#include <lame/Event.h>

#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestHarness.h>


TEST_GROUP(EventTests) {

LAME_Event event;

void setup()
{
    
}

void teardown()
{
}

};

TEST(EventTests, clearAfterCreate)
{
    LAME_Event_Init(&event);

    CHECK_FALSE(LAME_Event_Check(&event));
}

int main(int argc, char **argv)
{
    return RUN_ALL_TESTS(argc, argv);
}
