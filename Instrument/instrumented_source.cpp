#include<iostream>
//in the name of allah
#include <fstream>
std::ofstream logFile("log_file.txt");

usingnamespacestd;intmain(){
logFile << "main1" << std::endl;intin;cin>>in;if(in>0){
logFile << "main2" << std::endl;for(inti=0;i<10;i++){
logFile << "main3" << std::endl;
cout<<in+i;
}
logFile << "main4" << std::endl;
while(in<10){
logFile << "main5" << std::endl;
in+=1;
}
logFile << "main6" << std::endl;
if(in>9){
logFile << "main7" << std::endl;
cout<<"ya_allah";
}else{
logFile << "main8" << std::endl;
in=10;
}
logFile << "main9" << std::endl;
if(in<10){
logFile << "main10" << std::endl;
cout<<"ya_ali";
}
logFile << "main11" << std::endl;
}else{
logFile << "main12" << std::endl;
cout<<"ya_ali";
}
logFile << "main13" << std::endl;
intx=(in>1)?10:11;cout<<x<<endl;do{
logFile << "main14" << std::endl;
cout<<"ya_allah";
}while(1);
logFile << "main15" << std::endl;
return0;}
