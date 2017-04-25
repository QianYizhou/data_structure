#include <stdio.h>

#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTestExt/MockSupport.h"

#include "velocityprofile_trap.hpp"

using namespace KDL;

#define AXIS_MAX    (12)

typedef struct t_plan_info {
    VelocityProfile_Trap    *pVel;
    double                  startpos;
    double                  endpos;
} T_PLAN_INFO,
*PT_PLAN_INFO;

typedef struct t_plan_mgr {
    T_PLAN_INFO     plan[AXIS_MAX];
    double          duration_max;
    int32_t         index_max;
} T_PLAN_MGR,
*PT_PLAN_MGR;

struct plan_info_set {
    double      maxvel;
    double      maxacc;
    double      startpos;
    double      endpos;
};

static struct plan_info_set plan_info_set[AXIS_MAX] = {
            /*
             *  vel     acc     start   end
             */
/* 3-1 */   {   170.0f, 150.0f, 10.0,   10.0,   },
/* 3-2 */   {   170.0f, 150.0f, 148.81, 90.0,   },
/* 3-3 */   {   170.0f, 150.0f, 40.77,  180.0,  },
/* 4-1 */   {   170.0f, 150.0f, 10.0,   10.0,   },
/* 4-2 */   {   170.0f, 150.0f, 148.81, 90.0,   },
/* 4-3 */   {   170.0f, 150.0f, 40.77,  180.0,  },
/* 2-3 */   {   170.0f, 150.0f, 40.77,  180.0,  },
/* 2-2 */   {   170.0f, 150.0f, 148.81, 90.0,   },
/* 2-1 */   {   170.0f, 150.0f, 10.0,   10.0,   },
/* 1-3 */   {   170.0f, 150.0f, 40.77,  180.0,  },
/* 1-2 */   {   170.0f, 150.0f, 148.81, 90.0,   },
/* 1-1 */   {   170.0f, 150.0f, 10.0,   10.0,   },
};

//static void run_and_print_plan( void );
static void run_and_print_plan( PT_PLAN_MGR pMgr );
#if 0
static double debug_plan_info( PT_PLAN_MGR mgr );
static double debugInfo( VelocityProfile_Trap *pVel, double maxvel, double maxacc, double timeVal );
#endif

TEST_GROUP( simu_plan )
{
    T_PLAN_MGR  mgr;

    void setup()
    {
        int i;
        for (i = 0; i < AXIS_MAX; i++) {
            mgr.plan[i].pVel = new VelocityProfile_Trap(
                                        plan_info_set[i].maxvel, 
                                        plan_info_set[i].maxacc );
        }
    }

    void teardown()
    {
        int i;
        for (i = 0; i < AXIS_MAX; i++) {
            delete mgr.plan[i].pVel;
        }

        mock().checkExpectations();
        mock().clear();
    }
};

TEST( simu_plan, simple )
{
    int i;
    //double max_duration = 0.0f;
    double cur_duration = 0.0f;
    for (i = 0; i < AXIS_MAX; i++) {
        mgr.plan[i].pVel ->SetProfile(
                                plan_info_set[i].startpos, 
                                plan_info_set[i].endpos );
        cur_duration = mgr.plan[i].pVel ->Duration();

        if ( cur_duration > mgr.duration_max ) {
            mgr.duration_max = cur_duration;
            mgr.index_max = i;
        }
    }

    for (i = 0; i < AXIS_MAX; i++) {
        /*
         * FIXME: should not re-call SetProfile in SetProfileDuration
         */
        mgr.plan[i].pVel ->SetProfileDuration(
                                plan_info_set[i].startpos, 
                                plan_info_set[i].endpos,
                                mgr.duration_max );
    }

    run_and_print_plan( &mgr );
};

void run_and_print_plan( PT_PLAN_MGR pMgr )
{
    double run_time( 0.0f );
    const static double run_pace( 0.004f );

    int i;
    int index( 0 );

    printf( "index, duration, time " );
    for (i = 0; i < AXIS_MAX; i++) {
        printf( ", AXIS %d", i );
    }
    printf( "\n" );

    do {
        run_time = run_pace * index;
        printf( "%d, %f, %f", index, pMgr ->duration_max, run_time );
        for (i = 0; i < AXIS_MAX; i++) {
            printf( ", %f", pMgr ->plan[i].pVel ->Pos(run_time) );
        }
        printf( "\n" );
        ++index;
        
    } while ( run_time < pMgr ->duration_max );
}

