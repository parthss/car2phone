# Quick build for macOS/Linux without CMake. CMake (core/CMakeLists.txt) is the
# build used for AGL/Yocto, QNX and the Android NDK.

CXX      ?= c++
CXXFLAGS ?= -std=c++17 -O2 -Wall -Wextra -Wpedantic
BUILD    := build

CORE_SRC := $(wildcard core/src/*.cpp)
CORE_OBJ := $(patsubst core/src/%.cpp,$(BUILD)/core/%.o,$(CORE_SRC))
CORE_INC := -Icore/include

.PHONY: all test sims cluster clean

all: test sims

$(BUILD)/core/%.o: core/src/%.cpp $(wildcard core/include/c2p/*.hpp) core/include/c2p/c2p.h
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CORE_INC) -c $< -o $@

$(BUILD)/libc2p.a: $(CORE_OBJ)
	ar rcs $@ $^

$(BUILD)/c2p_tests: core/tests/test_main.cpp core/tools/demo_themes.hpp $(BUILD)/libc2p.a
	$(CXX) $(CXXFLAGS) $(CORE_INC) -DC2P_PROFILE_DIR='"profiles"' $< $(BUILD)/libc2p.a -o $@

$(BUILD)/c2p_car_sim: core/tools/car_sim.cpp $(BUILD)/libc2p.a
	$(CXX) $(CXXFLAGS) $(CORE_INC) $< $(BUILD)/libc2p.a -o $@

$(BUILD)/c2p_phone_sim: core/tools/phone_sim.cpp core/tools/demo_themes.hpp $(BUILD)/libc2p.a
	$(CXX) $(CXXFLAGS) $(CORE_INC) $< $(BUILD)/libc2p.a -o $@

test: $(BUILD)/c2p_tests
	./$(BUILD)/c2p_tests

sims: $(BUILD)/c2p_car_sim $(BUILD)/c2p_phone_sim

# Qt cluster receiver (Qt 5.15 or Qt 6 with Qt Quick). Override QMAKE=... if needed.
QMAKE ?= qmake
cluster:
	@mkdir -p $(BUILD)/qt-cluster
	cd $(BUILD)/qt-cluster && $(QMAKE) ../../car/qt-cluster/car2phone-cluster.pro && $(MAKE)

clean:
	rm -rf $(BUILD)
