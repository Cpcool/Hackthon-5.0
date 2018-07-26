#include"parser.h"

int main(int args,char** argv){
	if(args!=2) {
		cout<<"INVALID COMMMAND\nUSAGE : RNAwrap <filename>\n";
		return -1;
	}

	string fileName="families.fms",inputFilelist=argv[1],familyName,replaceString="---",outputFile="example.txt";	//filename
	size_t no_of_pattern;
	vector<family> fms;
	vector<string> fileList;
	vector<seqInfo> seqData,outputData;
	fms=parseFms(fileName);
	fileList=getFileList(inputFilelist);

	for(auto rnafile : fileList){
		outputFile="example.txt";
		seqData.clear();
		outputData.clear();
		familyName=getFamily(rnafile);
		family &thisFamily=getFamilyByName(familyName,fms);
		no_of_pattern=thisFamily.sequence.size();
		readFileToVector(rnafile,seqData);
		size_t pattern_found_info[seqData.size()][no_of_pattern]={0},found,empty=0;
		
		for(int i=0;i<seqData.size();i++)
		{
			for(int j=0;j<no_of_pattern;j++)
			{
				found = seqData[i].sequence.find(thisFamily.sequence[j]);
				seqData[i].sequence.replace(found,thisFamily.sequence[j].size(),replaceString);
				//storing the position of replaced pattern
				// i->sequence no in input file  // j-> store the position of family that is matched	
				if(found!=seqData[i].sequence.size())
				pattern_found_info[i][j]=found;			
				//cout<<"found:"<<found<<endl;
			}
		}
		
		writeVectorToFile(outputFile,seqData);
		system("./RNAfold --noPS < example.txt > output.txt");
		outputFile="output.txt";
		readOutputToVector(outputFile,outputData);
		
		for(int x=0;x<outputData.size();x++)
		{
			int y=no_of_pattern;
			while(y--){
				if(pattern_found_info[x][y]!=empty)
				{	//cout<<"get:"<<pattern_found_info[x][y]<<outputData[x].solution<<endl;
					outputData[x].solution.replace(pattern_found_info[x][y],3,thisFamily.solution[y]);
					outputData[x].sequence.replace(pattern_found_info[x][y],3,thisFamily.sequence[y]);
				}
			}
		}

		stringstream finalOutputFile;
		finalOutputFile<<rnafile<<".out";
		writeOutputToFile(finalOutputFile.str(),outputData);
	}
}