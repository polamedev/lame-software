#include <lame/SoftTimer.h>

#include <CppUTest/TestHarness.h>

unsigned mSecTime = 0;
unsigned millis()
{
    return mSecTime;
}

TEST_GROUP(SoftTimer)
{
    LAME_SoftTimer tim;

    void setup()
    {
        LAME_SoftTimer_Init(&tim, LAME_SoftTimer_ModePeriodic, 100);
        LAME_SoftTimer_SetMillisSource(millis);
    }

    void teardown()
    {
        mSecTime = 0;
    }
};

TEST(SoftTimer, stopAfterInit)
{
    CHECK_TRUE(LAME_SoftTimer_GetState(&tim) == LAME_SoftTimer_StateStop);
}

TEST(SoftTimer, runAfterStart)
{
    LAME_SoftTimer_Start(&tim);
    CHECK_TRUE(LAME_SoftTimer_GetState(&tim) == LAME_SoftTimer_StateRun);
}

TEST(SoftTimer, notOccurredAfterStart)
{
    LAME_SoftTimer_Start(&tim);
    CHECK_TRUE(LAME_SoftTimer_Occur(&tim) == false);
}

TEST(SoftTimer, timerOccurred)
{
    LAME_SoftTimer_Start(&tim);
    mSecTime = 100;
    CHECK_TRUE(LAME_SoftTimer_Occur(&tim) == true);
}

TEST(SoftTimer, SecondCheckAfterOccurred)
{
    LAME_SoftTimer_Start(&tim);
    mSecTime = 100;
    LAME_SoftTimer_Occur(&tim);
    CHECK_TRUE(LAME_SoftTimer_Occur(&tim) == false);
}