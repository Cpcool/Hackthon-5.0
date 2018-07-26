#/bin/bash
file="fileList.txt";
while IFS= read -r line
do

RNAfold --noPS < $line
      
done <"$file"




