CPPUTEST_HOME	= ../
INCLUDES		= -I../include \
				  -I../project \
				  -I../project/kdl \
				  -I../mock \
				  -I../expect

################################################################################
bin_PROGRAMS			= ut_foot_module
ut_foot_module_SOURCES	= \
						  ../testcode/main.cpp \
						  \
						  ../project/kdl/velocityprofile_trap.cpp \
						  ../project/kdl/velocityprofile_trap.hpp \
						  \
						  ../testcode/test_simu_plan.cpp

ut_foot_module_CXXFLAGS	= \
						  -DTIXML_USE_STL \
						  `pkg-config glib-2.0 --cflags` \
						  -g -Wall -fprofile-arcs -ftest-coverage \
						  -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorMallocMacros.h \
						  -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorNewMacros.h
ut_foot_module_CFLAGS	= \
						  -DTIXML_USE_STL \
						  `pkg-config glib-2.0 --cflags` \
						  -g -Wall -fprofile-arcs -ftest-coverage \
						  -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorMallocMacros.h \
						  -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorNewMacros.h
ut_foot_module_LDFLAGS	= \
						  `pkg-config glib-2.0 --libs` \
						  -fprofile-arcs -ftest-coverage \
						  -L../libs/fedora_10 -lCppUTest -lCppUTestExt \
						  -lmeschach \
						  -lm

#if LX800_ENA
#rsp_app_LDFLAGS		+=
#endif
#if E600_ENA
#rsp_app_LDFLAGS		+= -L../libs/e600_wrl5
#endif
#if E3845_ENA
#rsp_app_LDFLAGS		+= -L../libs/e3845_wrl5
#endif
