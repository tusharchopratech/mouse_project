cd ../bin
g++ ../src/main.cpp ../src/modules/m_daq/MDaq.cpp -L/../lib -luldaq
if [ $? -eq 0 ]; then
    printf "\nCompiled Successfully!\n\n"
    ./a.out
fi