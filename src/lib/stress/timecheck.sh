echo "Compiling smart..."
g++ "$1" -o _stressSource/smart 
time _stressSource/smart < input.txt
