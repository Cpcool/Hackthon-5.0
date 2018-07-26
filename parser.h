#pragma once

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<bits/stdc++.h>

using namespace std;

class family
{
public:
	string familyName;
	vector<string> sequence,solution;
	size_t len;
	family(string pfName){len=0;familyName=pfName;}
	void add(string &seq,string &sol){
		sequence.push_back(seq);
		solution.push_back(sol);
		//cout<<familyName<<seq<<sol<<endl;
		len++;
	}
};

class seqInfo
{
public:
	string name,sequence,solution,score;
	seqInfo(string &pName,string &pSeq){name=pName;sequence=pSeq;}
	seqInfo(string &pName,string &pSeq,string &pSol,string &pScore){name=pName;sequence=pSeq;solution=pSol;score=pScore;}
};

void readFileToVector(string &filename,vector<seqInfo> &seqData){
	string name,seq;
	ifstream input_file;
	input_file.open(filename.c_str());
	while(input_file>>name)
	{
		input_file>>seq;
		seqData.push_back(seqInfo(name,seq));
	}
	input_file.close();
}

void readOutputToVector(string &filename,vector<seqInfo> &seqData){
	string name,seq,sol,score;
	ifstream input_file;
	input_file.open(filename.c_str());
	while(input_file>>name)
	{
		input_file>>seq;
		input_file>>sol;
		//input_file>>score>>score;
		getline(input_file,score);
		seqData.push_back(seqInfo(name,seq,sol,score));
	}
	input_file.close();
}

void writeVectorToFile(string &filename,vector<seqInfo> &seqData){
	ofstream myfile;
  	myfile.open(filename.c_str());
	for(int k=0;k<seqData.size();k++)  
	{
		myfile<<seqData[k].name<<endl;
		myfile<<seqData[k].sequence<<endl;
	}
	myfile.close();
}

void writeOutputToFile(string filename,vector<seqInfo> &seqData){
	ofstream myfile;
  	myfile.open(filename.c_str());
	for(int k=0;k<seqData.size();k++)  
	{
		myfile<<seqData[k].name<<endl;
		myfile<<seqData[k].sequence<<endl;
		myfile<<seqData[k].solution;
		myfile<<" "<<seqData[k].score<<endl;
	}
	myfile.close();
}

family &getFamilyByName(string &familyName,vector<family> &fms){
	for(int i=0;i<fms.size();i++) if(fms[i].familyName==familyName) return fms[i];
	throw std::logic_error("INVALID NAME");
}

vector<family> parseFms(string &fName){
	vector<family> f;
	ifstream fi;
	size_t lastpos=0,pos,index=0;
	string::iterator substart, subend;
	string line,seq,sol,colon=":",comma=",",hyphen="-",familyName;
	fi.open(fName.c_str());
	while(fi>>line){
		lastpos=0;
		if(line.size()==0) break;
		//cout<<line.size()<<endl;
		//cout<<line<<endl;
		substart=line.begin();
		subend=search(substart,line.end(),colon.begin(),colon.end());
		familyName=string(substart,subend);
		f.push_back(family(familyName));
		substart=subend+1;
		while(substart<line.end()){
			
			subend=search(substart,line.end(),hyphen.begin(),hyphen.end());
			seq=string(substart,subend);
			substart=subend+1;

			subend=search(substart,line.end(),comma.begin(),comma.end());
			sol=string(substart,subend);
			substart=subend+1;
			//if(seq.size()!=sol.size()) cout<<"ERROR DETECTED AT INDEX="<<index<<endl<<endl;
			f[index].add(seq,sol);
		}
		//cout<<familyName<<endl;
		index++;
	}
	fi.close();
	return f;
}


string getFamily(string &filename){
	string delim="_";
	string::iterator pos=search(filename.begin(),filename.end(),delim.begin(),delim.end());
	delim=string(filename.begin(),pos);
	return delim;
}

vector<string> getFileList(string &filename){
	ifstream fi;
	vector<string> fileList;
	string str;
	fi.open(filename.c_str());
	while(fi>>str) fileList.push_back(str);
	return fileList;
}
