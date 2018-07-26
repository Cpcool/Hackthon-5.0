import sys
fileList =open(sys.argv[1],"r")
filename=fileList.readline()
while filename:
	fres1 =open(filename.rstrip()+".out2","r")
	fres2 =open(filename.rstrip()+".out","r")

	l1=fres1.readline()
	l2=fres2.readline()

	count=1
	success=0
	fp=0.;tp=0.;tn=0.;fn=0.
	while l1:
		if count%3==0:
			sol1=l1.split(" ")[0]
			sol2=l2.split(" ")[0]
			for i in range(len(sol1)):
				if sol1[i]=='.' and sol2[i]!=sol1[i]:#unwanted predicted brackets
					fp+=1
				if sol1[i]=='.' and sol2[i]==sol1[i]:#matched dots
					tn+=1
				if sol1[i]!='.' and sol2[i]==sol1[i]:#matched brackets
					tp+=1
				if sol2[i]=='.' and sol2[i]!=sol1[i]:#unwanted predicted dots
					fn+=1


			if sol1==sol2:
				success+=1
		count+=1

		l1=fres1.readline()
		l2=fres2.readline()
	filename=fileList.readline()	
count/=3

print("success rate = "+str(success*100/count)+" %")
print("tp="+str(tp))
print("fp="+str(fp))
print("tn="+str(tn))
print("fn="+str(fn))

print("sensitivity="+str(tp*100/(tp+fn)))
print("specificity="+str(tn*100/(tn+fp)))
print("ppv="+str(tp/(tp+fp)))
print("npv="+str(tn/(tn+fn)))