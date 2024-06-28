BUILD_DIR := build
CPP_SRCS := $(shell find . -name "*.cpp")
OBJS = $(CPP_SRCS:%=$(BUILD_DIR)/%.o)
CPP_BIN := nt_cron
LDLIBS += -lpthread
CPPFLAGS += -g

all: folder $(CPP_BIN) config 

$(BUILD_DIR)/%.cpp.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(INC_FLAGS) $(CPPDEFS) -c $< -o $@

$(CPP_BIN): $(OBJS) 
	$(CXX) -o $(BUILD_DIR)/$@ $(CPPFLAGS) $(CXXFLAGS) $(INC_FLAGS) $(CPPDEFS) $(LDFLAGS) $^  $(LDLIBS) 

folder:
	mkdir -p $(BUILD_DIR)

config:
	cp nt_cron.conf ${BUILD_DIR}/


.PHONY:clean 

clean:
	-rm $(BUILD_DIR)/*.o
	-rm $(BUILD_DIR)/nt_cron.conf
	-rm $(BUILD_DIR)/$(CPP_BIN)
