#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTestExt/MockSupport.h"
#include "CppUTestExt/MockSupport_c.h"

//#include "test_target_operation.cpp"
//#include "test_velocityprofile_trap.cpp"
//#include "test_simu_plan.cpp"
//#include "test_move_plan.cpp"

int main(int argc, const char *argv[])
{
    return CommandLineTestRunner::RunAllTests( argc, argv );
}

