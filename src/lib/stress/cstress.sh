#!/bin/bash 

mkdir -p _stressSource

echo "Compiling smart..." 
g++ "$1" -o _stressSource/smart
echo "Compiling stupid..."
g++ stupid.cpp -o _stressSource/stupid
echo "Compiling checker..." 
g++ checker.cpp -o _stressSource/checker 
echo "Compiling gen..."  
g++ gen.cpp -o _stressSource/gen

cd _stressSource 

num=1 
for ((;;)) do 
  echo "Test number $num" 
  ./gen > temp.txt 
  cat temp.txt
  echo ""
  smartRes=`./smart < temp.txt`
  stupidRes=`./stupid < temp.txt`
  echo "$smartRes" >> temp.txt
  echo "$stupidRes" >> temp.txt
  checkRes=`./checker < temp.txt` 
  echo -e "Smart res:\n$smartRes\nStupid res:\n$stupidRes\nCheck res:\n$checkRes\n"
  if [ "$checkRes" != "1" ]; then 
      break 
  fi 
  num=$((num+1)) 
done
