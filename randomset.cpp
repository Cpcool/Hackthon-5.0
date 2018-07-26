#include"parser.h"

char psbl[]="augc";
char rset[10000];

void randomizeSet(int minl,int maxl){
	int r=minl+rand()%(maxl-minl+1);
	rset[r]='\0';
	while(r--) rset[r]=psbl[rand()%4];
}

int main(int argc, char **argv){
	if(argc!=3) {
		cout<<"INVALID COMMMAND\nUSAGE : rset <no. of files> <max seqs per file>\n";
		return -1;
	}
	system("rm *fa");
	ofstream newFile;
	int num=atoi(argv[1]);
	int maxseq=atoi(argv[2]),seqs;
	string fileName="families.fms";	//filename
	vector<family> fms;
	
	fms=parseFms(fileName);

	//cout<<"Parsing Complete"<<endl;

	while(num--){
		family &thisF=fms[rand()%fms.size()];
		stringstream ss,ss_filecontents;
		ss<<thisF.familyName<<"_"<<rand()<<".fa";
		string newFileName=ss.str();
		
		newFile.open(newFileName.c_str());
		seqs=(rand()%maxseq)+1;
		while(seqs--){
			newFile<<">"<<rand()<<endl;
			for(int i=0;i<thisF.sequence.size();i++){
				randomizeSet(thisF.sequence[i].size()-5,thisF.sequence[i].size()+5);
				newFile<<rset<<thisF.sequence[i];
			}
			randomizeSet(8,15);
			newFile<<rset<<endl;
		}
		newFile.close();
	}
	system("ls -1 *fa > fileList.txt");
}