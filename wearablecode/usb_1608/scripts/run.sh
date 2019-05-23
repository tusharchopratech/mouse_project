cd ../bin
g++ ../src/main.cpp ../src/modules/m_daq/MDaq.cpp -L/../lib -luldaq -std=c++0x
if [ $? -eq 0 ]; then
    printf "\nCompiled Successfully!\n\n"
    ./a.out
fi