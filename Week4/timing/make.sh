g++ timeBasicOperators.cpp ../matrix/naive.cpp -o basicNaive
g++ timeExp.cpp ../matrix/naive.cpp -o expNaive
g++ timeMatrOps.cpp ../matrix/naive.cpp -o matrOpsNaive
g++ timeMinMax.cpp ../matrix/naive.cpp -o minMaxNaive
g++ timeBasicOperators.cpp ../matrix/kernel.cpp ../matrix/optim.cpp -o basicOptim  -std=c++17 -pthread -I../matrix/OpenCL/include -L../matrix/OpenCL/lib -lOpenCL # feel free to edit
g++ timeExp.cpp ../matrix/optim.cpp -o expOptim # feel free to edit
g++ timeMatrOps.cpp ../matrix/optim.cpp -o matrOpsOptim # feel free to edit
g++ timeMinMax.cpp ../matrix/optim.cpp -o minMaxOptim # feel free to edit
