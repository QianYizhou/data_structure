CPPUTEST_HOME	= ../
INCLUDES		= -I../include \
				  -I../project \
				  -I../project/kdl \
				  -I../project/week2 \
				  -I../mock \
				  -I../expect

################################################################################
bin_PROGRAMS			= ut_frame
ut_frame_SOURCES		= \
						  ../testcode/main.cpp \
						  \
						  ../project/kdl/velocityprofile_trap.cpp \
						  ../project/kdl/velocityprofile_trap.hpp \
						  \
						  ../project/week2/polynomial_calc.c \
						  ../project/week2/polynomial_calc.h \
						  \
						  ../testcode/test_simu_plan.cpp \
						  \
						  ../testcode/week2/test_polynomial_calc.cpp

ut_frame_CXXFLAGS		= \
						  -DTIXML_USE_STL \
						  `pkg-config glib-2.0 --cflags` \
						  -g -Wall -fprofile-arcs -ftest-coverage \
						  -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorMallocMacros.h \
						  -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorNewMacros.h
ut_frame_CFLAGS			= \
						  -DTIXML_USE_STL \
						  `pkg-config glib-2.0 --cflags` \
						  -g -Wall -fprofile-arcs -ftest-coverage \
						  -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorMallocMacros.h \
						  -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorNewMacros.h
ut_frame_LDFLAGS		= \
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
