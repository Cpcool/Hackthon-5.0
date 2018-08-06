# Hackthon-5.0
Our Project is related to bioinformatic where we optimized the performance of one functionality of ViennaRNA'software package RNAfold, which is used to calculate the secondary structure of RNA (in medical research) and if there will be complex jobs to run on in future, then it takes a lot of time to execute (may be some days) so we create an Wrapper idea of that so that it can be useful in future to get quick result. 


You have to execute it in this way :-

// To generates the datasets 

1.    g++ -std=c++11 randomset.cpp -o rset
      ./rset x y                
      
      (where x is the no of files and y is no of sequences in a single file which you generate)

2.    g++ -std=c++11 main.cpp -o RNAwrap

3.    time ./RNAwrap fileList.txt (it's a main wrapper we create for RNAfold)

4.    time hackthon.sh (to run a simple RNAfold code)

5.    see the time difference between them and also compare the results of both of them




