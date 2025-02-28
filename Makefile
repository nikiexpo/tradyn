
EXE = main

OBJS = main.o gradientFD.o UserDefinedFunctions.o jacobian.o hessian_wL.o commonFuncs.o hessian_FG.o

CXX = g++

CXXFLAGS = -std=c++11

all: $(EXE)

.SUFFIXES: .cpp .o

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)


clean:
	rm -rf $(EXE) $(OBJS)
.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<