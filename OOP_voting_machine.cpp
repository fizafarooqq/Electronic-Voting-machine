#include<iostream>
#include<string>
#include<fstream>
#include <conio.h>
#include<cstring>

using namespace std;


class Province {
	string Pname;
public:
	Province() {}
	Province(string n) {
		Pname = n;
	}
	string GetProvinceName() {
		return Pname;
	}

};
class City {
	string cityname;
public:
	City(string n) {
		cityname = n;
	}
	City() {}
	string GetCityName() {
		return cityname;
	}
};
class District {
	string name;
	Province p;
	City c;
public:
	District(string n, Province p1, City c1) {
		name = n;
		p = p1;
		c = c1;
	}
	void SetDistrict(string n, Province p1, City c1) {
		name = n;
		p = p1;
		c = c1;
	}
	District() {

	}
	string GetDistrictName() {
		return name;
	}
	void SetDistrictName(string n) {
		name = n;
	}
};
class Person {
protected:
	string name;
	string cnic;
	string FatherName;
	int age;
	char gender;
	District district;
public:
	Person(string n, string c, string fName, int age, char g, District d) {
		name = n;
		cnic = c;
		FatherName = fName;

		this->age = age;
		gender = g;
		district = d;
	}
	void set_PersonDetails(string n, string c, string fName, int age, District d) {
		name = n;
		cnic = c;
		FatherName = fName;
		this->age = age;
		district = d;
	}
	void set_PersonDetails(string n, string c, string fName, int age, char g) {
		name = n;
		cnic = c;
		FatherName = fName;
		this->age = age;
		gender = g;
	}

	void setName(string n) {
		name = n;
	}
	void setCnic(string c) {
		cnic = c;
	}
	void setFatherName(string Fn) {
		FatherName = Fn;
	}
	void setAge(int age) {
		this->age = age;
	}
	void setGender(char g) {
		gender = g;
	}
	void setDistrict(District d) {
		district = d;
	}
	string getName() const { return name; }
	string getCnic() const { return cnic; }
	string GetFatherName()const { return FatherName; }
	int getAge() const { return age; }
	char getGender() const { return gender; }
	District GetDistrict() const { return district; }
	//void virtual  printDetails();
	Person() {}

};
class voter : public Person {
	string PartyName;
	bool is_voted;
public:
	voter(string n, string c, string fName, int age, char g, District d) :Person(n, c, fName, age, g, d) {
		is_voted = 0;

	}
	voter() {}
	void setVote(string Pname) {
		is_voted = 1;
		PartyName = Pname;
	}

	void store_UnCastVoterData() {
		ofstream fout;
		fout.open("UnCastVoterData.txt", ios::app | ios::binary);
		fout.write((char*)this, sizeof(*this));
		fout.close();
	}
	void store_CastVoterData() {
		ofstream fout;
		fout.open("VoterData.txt", ios::app | ios::binary);
		fout.write((char*)this, sizeof(*this));
		fout.close();
	}
	void Read_RigisteredVoterData() {
		ifstream fin;
		fin.open("UnCastVoterData.txt", ios::in | ios::binary);
		if (!fin) {
			cout << "File Is not Found" << endl;
		}
		else {
			fin.read((char*)this, sizeof(*this));
			while (!fin.eof()) {
				DispalyDetails();
				fin.read((char*)this, sizeof(*this));

			}
			fin.close();
		}
	}
	void Read_RigisteredVoterData(string c) {
		ifstream fin;
		fin.open("UnCastVoterData.txt", ios::in | ios::binary);
		if (!fin) {
			cout << "File Is not Found" << endl;
		}
		else {

			while (fin.read((char*)this, sizeof(*this))) {
				if (c == cnic) {
					DispalyDetails();
				}
			}
			fin.close();
		}
	}
	void Read_VoterData() {
		ifstream fin;

		fin.open("VoterData.txt", ios::in | ios::binary);
		if (!fin) {
			cout << "File Is not Found" << endl;
		}
		else {
			;
			while (fin.read((char*)this, sizeof(*this))) {
				DispalyDetails();
			}
			fin.close();
		}
	}
	void DispalyDetails() {
		cout << "\n---------------------------------------------------" << endl;
		cout << "Name : " << name << endl
			<< "Father Name :" << FatherName << endl
			<< "Gender: " << gender << endl
			<< "Cnic : " << cnic << endl
			<< "Age: " << age << endl
			<< "District: " << district.GetDistrictName() << endl
			<< "Voted To :" << PartyName << endl;
		cout << "\n---------------------------------------------------" << endl;

	}
	int Search_VoterByCnic(string c) {
		ifstream fin;
		int m = 0;
		fin.open("VoterData.txt", ios::in | ios::binary);
		if (!fin) {
			cout << "File Is not Found" << endl;
		}
		else {

			while (fin.read((char*)this, sizeof(*this))) {
				if (c == cnic && this->is_voted == 1) {
					m = 1;
				}
			}
			fin.close();
		}
		return m;
	}
	string DistrictWinner(District d) {
		ifstream fin;
		int countPmln = 0, countJI = 0, countPPP = 0, countMQM = 0, countPTI = 0;
		fin.open("VoterData.txt", ios::in | ios::binary);
		if (!fin) {
			cout << "File Is not Found" << endl;
		}
		else {

			while (fin.read((char*)this, sizeof(*this))) {
				if (PartyName == "PTI" && district.GetDistrictName() == d.GetDistrictName()) {
					countPTI++;
				}
				else if (PartyName == "JI" && district.GetDistrictName() == d.GetDistrictName()) {
					countJI++;
				}
				else if (PartyName == "PPP" && district.GetDistrictName() == d.GetDistrictName()) {
					countPPP++;
				}
				else if (PartyName == "MQM" && district.GetDistrictName() == d.GetDistrictName()) {
					countMQM++;
				}
				else if (PartyName == "PmlN" && district.GetDistrictName() == d.GetDistrictName()) {
					countPmln++;
				}
			}
			fin.close();
		}
		cout << "Total PTI Votes = " << countPTI << endl;;
		cout << "Total PMLN Votes = " << countPmln << endl;
		cout << "Total PPP Votes = " << countPPP << endl;
		cout << "Total MQM Votes = " << countMQM << endl;
		cout << "Total JI Votes = " << countJI << endl;

		if (countPTI > countPmln && countPTI > countPPP && countPTI > countMQM && countPTI > countJI) {
			return "PTI";
		}
		else if (countPmln > countPTI && countPmln > countPPP && countPmln > countMQM && countPmln > countJI) {
			return "PmlN";

		}
		else if (countPPP > countPTI && countPPP > countPmln && countPPP > countMQM && countPPP > countJI) {
			return "PPP";

		}
		else if (countMQM > countPTI && countMQM > countPmln && countMQM > countPPP && countMQM > countJI) {
			return  "MQM";

		}
		else if (countJI > countPTI && countJI > countPmln && countJI > countPPP && countJI > countMQM) {
			return "JI";

		}
		else {
			return  "Undecideable";

		}
	}
	string Search_VoterDistrict(string c) {
		ifstream fin;
		District d;
		fin.open("UnCastVoterData.txt", ios::in | ios::binary);
		if (!fin) {
			cout << "File Is not Found" << endl;
		}
		else {

			while (fin.read((char*)this, sizeof(*this))) {
				if (c == cnic) {
					d = this->GetDistrict();

				}

			}
			fin.close();
			return d.GetDistrictName();
		}
	}
	void Show_VoterByCnic(string c) {
		ifstream fin;
		fin.open("VoterData.txt", ios::in | ios::binary);
		if (!fin) {
			cout << "File Is not Found" << endl;
		}
		else {

			while (fin.read((char*)this, sizeof(*this))) {
				if (c == cnic && is_voted == 1) {
					DispalyDetails();
				}

			}
			fin.close();
		}
	}
	int countTotalVoters() {
		ifstream fin;
		int count = 0;
		fin.open("VoterData.txt", ios::in | ios::binary);
		if (!fin) {
			cout << "File Is not Found" << endl;
		}
		else {

			while (fin.read((char*)this, sizeof(*this))) {
				if (is_voted == 1) {
					count++;
				}
			}
			fin.close();
		}
		return count;

	}
	voter* SetVoter(voter* temp, string c) {
		ifstream fin("UnCastVoterData.txt", ios::binary);
		if (!fin) {
			cout << "File not found" << endl;
			exit(1);
		}


		while (fin.read((char*)this, sizeof(*this))) {
			if (this->cnic == c) {
				temp->name = this->name;
				temp->age = this->age;
				temp->district = this->district;
				temp->FatherName = this->FatherName;
				temp->cnic = this->cnic;
				temp->gender = this->gender;
				temp->is_voted = this->is_voted;
				temp->PartyName = this->PartyName;
			}
		}

		fin.close();
		return temp;
	}
	int countTotalVotesPartyWise(string Pname) {
		ifstream fin;
		int count = 0;
		fin.open("VoterData.txt", ios::in | ios::binary);
		if (!fin) {
			cout << "File Is not Found" << endl;
		}
		else {

			while (fin.read((char*)this, sizeof(*this))) {
				if (PartyName == Pname && is_voted == 1) {
					count++;
				}


			}
			fin.close();
		}
		return count;
	}
	void GenderWiseVotersRecord() {
		ifstream fin;
		int mcount = 0;
		int fcount = 0;
		fin.open("VoterData.txt", ios::in | ios::binary);
		if (!fin) {
			cout << "File Is not Found" << endl;
		}
		else {

			while (fin.read((char*)this, sizeof(*this))) {
				if ('M' == gender && is_voted == 1) {
					mcount++;
				}
				if ('F' == gender && is_voted == 1) {
					fcount++;
				}


			}
			fin.close();
			int TotalVoters = countTotalVoters();
			float avgMale = (((float)mcount / (float)TotalVoters) * 100);
			float avgFemale = (((float)fcount / (float)TotalVoters) * 100);
			cout << "\n-------------------------------------------------------------------------------" << endl;
			cout << "-------------------------------------------------------------------------------\n" << endl;
			cout << "TotalVotes By Females " << fcount << " Out Of " << TotalVoters << endl;
			cout << "TotalVotes By Males " << mcount << " Out Of " << TotalVoters << endl;
			cout << "\n\n---------------------------------------------------------------------------" << endl;
			cout << "Avearge Male (in Percentage) : " << avgMale << "%\tAvearage Female (in Percentage)" << avgFemale << "%" << endl;
			cout << "---------------------------------------------------------------------------" << endl;
			cout << "\n\n-------------------------------------------------------------------------------" << endl;;
			cout << "-------------------------------------------------------------------------------" << endl;
		}

	}
	int TotalVotersRecord_ageWise(int AGE) {
		ifstream fin;
		int count = 0;
		fin.open("VoterData.txt", ios::in | ios::binary);
		if (!fin) {
			cout << "File Is not Found" << endl;
		}
		else {

			while (fin.read((char*)this, sizeof(*this))) {
				if (age == AGE) {
					count++;
				}


			}
			fin.close();
		}
		return count;
	}
	/*	void showleadingCandidate(candidate c1) {
			ifstream fin;
			double count = 0;
			fin.open("VoterData.txt", ios::in | ios::binary);
			if (!fin) {
				cout << "File Is not Found" << endl;
			}
			else {

				while (fin.read((char*)this, sizeof(*this))) {
					if(PartyName)

				}
				fin.close();
			}
			return count;

		}*/
};
class Party {
protected:
	string Partyname;
	string sign;
	Person chairman;
	double votes;
public:

	Party(string n, string code, Person c) {
		Partyname = n;
		this->sign = code;
		chairman = c;
	}
	Party() {

	}
	string GetPartyName() {
		return Partyname;
	}
	string GetChairmanName() {
		return chairman.getName();
	}

};


class candidate : public Person, public Party {
	bool is_rgistered;// in a district 
	bool OnlyOneDistrict;// can be fought for 1 district only//
public:
	candidate(string n, string c, string fName, int age, char g, District d, string name, string code, Person C) :Person(n, c, fName, age, g, d), Party(name, code, C) {

	}
	candidate() {

	}
	string GetCandidateName() {
		return name;
	}
	string ReadAllCandidates() {
		ifstream fin;
		fin.open("CandidateData.txt", ios::in | ios::binary);
		if (!fin) {
			cout << "File Is not Found" << endl;
		}
		else {
			while (fin.read((char*)this, sizeof(*this))) {
				DisplayDetails();

			}
			fin.close();
		}
	}
	void RigisterCandidate() {
		ofstream fout;
		fout.open("CandidateData.txt", ios::app | ios::binary);
		fout.write((char*)this, sizeof(*this));
		fout.close();
	}
	void DisplayDetails() {
		cout << "\n-------------------------------------------------------------------------------" << endl;
		cout << "Name : " << name << endl;
		cout << "Party : " << Partyname << endl;
		cout << "Chairman : " << chairman.getName() << endl;
		cout << "Sign : " << sign << endl;
		cout << "\n-------------------------------------------------------------------------------" << endl;
	}
};
//Important parties PTI,JI,PML-N,PPP,MqM// 
/////////////////////////////////Declearation Of District karachi , parties and Candidates/////////////
Province Punjab("Punjab");
City Islamabad("Islamabad");
District IslamabadCapitalTerritory("Islamabad Capital Territory", Punjab, Islamabad);
Province Sindh("Sindh");
City Karachi("Karachi");
City lahore("Lahore");
District KarchiCentral("KarachiCentral", Sindh, Karachi);
District Korangi("Korangi", Sindh, Karachi);
District KarachiEast("KarachiEast", Sindh, Karachi);
District KarachiWest("KarachiWest", Sindh, Karachi);
District KarachiSouth("KarachiSouth", Sindh, Karachi);
District Keemari("Keemari", Sindh, Karachi);
District Raiwind("Raiwind", Punjab, lahore);
District Larkana("Larkana", Punjab, Islamabad);
District IqbalTehsil("IqbalTehsil", Punjab, lahore);
Person NawazShareef("NawazSarif", "52013-1342018-0", "MuhammadSharif", 73, 'M', Raiwind);
Person BilawalBhutto("BilawalBhutto", "45402-9818540-5", "Zardari", 34, 'M', Larkana);
Person SirajUlHaq("Siraj-Ul-Haq", "17031 - 1496065 - 7", "Haji KhairMuhammad", 60, 'M', IqbalTehsil);
Person KhalidMaqbool("KhalidMaqboolSiddiqui", "45300-2109090-1", "Maqbool Ahmed Siddiqui", 53, 'M', KarchiCentral);
Person ImranKhan("ImranKhan", "38302-6264991-9", "Ikramullah Khan Niazi", 70, 'M', IslamabadCapitalTerritory);
Party PTI("PTI", "Bat", ImranKhan);
Party PmlN("PmlN", "Loin", NawazShareef);
Party PPP("PPP", "Arrow", BilawalBhutto);
Party MQM("MQM", "Kite", KhalidMaqbool);
Party JI("JI", "WeighingMachine", SirajUlHaq);

///////////////////////////////////////////////////////////////////////////////// 
void Dis_KarachiCentral_Candidates() {
	candidate* c1 = new candidate("Khawaja Muhammad Baqar", "45673-2103490-3", "Muhammad Saleem", 70, 'M', KarchiCentral, "MQM", "Kite", KhalidMaqbool);
	candidate* c2 = new candidate("Syed Aminul Haque", "45978-1009890-5", "syed Jamal", 65, 'M', KarchiCentral, "JI", "WeighingMachine", SirajUlHaq);
	candidate* c3 = new candidate("Abdul Qadir Patel", "46934-2623590-1", "Farooq Patel", 45, 'M', KarchiCentral, "PPP", "Arrow", BilawalBhutto);
	candidate* c4 = new candidate("Mansoor Ahmed", "46454-2667323-1", "Ahmed Haqq", 55, 'M', KarchiCentral, "PTI", "Bat", ImranKhan);
	candidate* c5 = new candidate("Salahuddin", "47854-7136323-5", "Muhammad Ayub", 55, 'M', KarchiCentral, "PmlN", "Loin", NawazShareef);
	cout << "Candidate of District Karachi central are:" << endl;
	c1->DisplayDetails();
	c2->DisplayDetails();
	c3->DisplayDetails();
	c4->DisplayDetails();
	c5->DisplayDetails();
}
void Dis_Korangi_Candidates() {
	candidate* c1 = new candidate("Syed Hashim Raza", "45123-2468940-1", "Muhammad Saleem", 70, 'M', Korangi, "MQM", "Kite", KhalidMaqbool);
	candidate* c2 = new candidate("Muhammad Yusuf Shaikh", "42278-2357240-5", "Muhammad Rahim", 65, 'M', Korangi, "JI", "WeighingMachine", SirajUlHaq);
	candidate* c3 = new candidate("Muhammad Aslam Khan", "44534-2122123-1", "Farooq khan", 55, 'M', Korangi, "PPP", "Arrow", BilawalBhutto);
	candidate* c4 = new candidate("Amjad Ali Khan", "49754-6672351-1", "Anjeer Ali", 40, 'M', Korangi, "PTI", "Bat", ImranKhan);
	candidate* c5 = new candidate("Zahid Hussain Mughal", "42354-7324423-5", "Junaid Hussain", 54, 'M', Korangi, "PmlN", "Loin", NawazShareef);
	cout << "Candidate of District Korangi are:" << endl;
	c1->DisplayDetails();
	c2->DisplayDetails();
	c3->DisplayDetails();
	c4->DisplayDetails();
	c5->DisplayDetails();
}
void Dis_KarachiWest_Candidates() {
	candidate* c1 = new candidate("Dr. Muhammad Farooq Sattar", "41234-2984270-5", " Muhammad Sattar", 63, 'M', KarachiWest, "MQM", "Kite", KhalidMaqbool);
	candidate* c2 = new candidate("Naseem Ahmad Siddiqui", "42352-5734350-1", "Hamza Siddique", 50, 'M', KarachiWest, "JI", "WeighingMachine", SirajUlHaq);
	candidate* c3 = new candidate("Muhammad Shahbaz", "43477-1987985-9", "Gulam Muhammad", 72, 'M', KarachiWest, "PPP", "Arrow", BilawalBhutto);
	candidate* c4 = new candidate("Iqbal Muhammad Ali Khan", "423419-6192836-1", "Abdul Rauf Khan", 50, 'M', KarachiWest, "PTI", "Bat", ImranKhan);
	candidate* c5 = new candidate("Iftikhar Alam", "44568-1234443-5", "Junaid Alam", 39, 'M', KarachiWest, "PmlN", "Loin", NawazShareef);
	cout << "Candidate of District Karachi West are:" << endl;
	c1->DisplayDetails();
	c2->DisplayDetails();
	c3->DisplayDetails();
	c4->DisplayDetails();
	c5->DisplayDetails();
}
void Dis_KarachiEast_Candidates() {
	candidate* c1 = new candidate("Syed Ali Raza Abidi", "42345-2124940-5", "Ghulam Abidi", 70, 'M', KarachiEast, "MQM", "Kite", KhalidMaqbool);
	candidate* c2 = new candidate("Muhammad Kamran", "42135-2311350-5", "Muhammad Dawood", 60, 'M', KarachiEast, "JI", "WeighingMachine", SirajUlHaq);
	candidate* c3 = new candidate("Rafiullah", "43477-2122965-9", "Haroon", 55, 'M', KarachiEast, "PPP", "Arrow", BilawalBhutto);
	candidate* c4 = new candidate("Abdul Majeed", "41249-6982351-1", "Abdul Hameed", 53, 'M', KarachiEast, "PTI", "Bat", ImranKhan);
	candidate* c5 = new candidate("Abdul Rasheed", "44568-8765443-5", "Junaid Hussain", 45, 'M', KarachiEast, "PmlN", "Loin", NawazShareef);
	cout << "Candidate of District Karachi East are:" << endl;
	c1->DisplayDetails();
	c2->DisplayDetails();
	c3->DisplayDetails();
	c4->DisplayDetails();
	c5->DisplayDetails();
}
void Dis_KarachiSouth_Candidates() {
	candidate* c1 = new candidate("Syed Murtaza Abbas", "41234-2112340-5", "Ghulam Abbas", 70, 'M', KarachiSouth, "MQM", "Kite", KhalidMaqbool);
	candidate* c2 = new candidate("Muhammad Hussain", "42345-3123450-1", "Muhammad Uzair", 60, 'M', KarachiSouth, "JI", "WeighingMachine", SirajUlHaq);
	candidate* c3 = new candidate("Javed Ali Mahar", "41347-2900965-7", "Ali Akhtar", 45, 'M', KarachiSouth, "PPP", "Arrow", BilawalBhutto);
	candidate* c4 = new candidate("Mustafa Arif", "41249-6928642-5", "Muhammad Arif", 50, 'M', KarachiSouth, "PTI", "Bat", ImranKhan);
	candidate* c5 = new candidate("Muhammad Ali Rashid", "44568-8765443-5", "Rashid Khan", 45, 'M', KarachiSouth, "PmlN", "Loin", NawazShareef);
	cout << "Candidate of District Karachi South are:" << endl;
	c1->DisplayDetails();
	c2->DisplayDetails();
	c3->DisplayDetails();
	c4->DisplayDetails();
	c5->DisplayDetails();
}
void Dis_Keemari_Candidates() {
	candidate* c1 = new candidate("Syed Asif Hasnain", "41244-2174430-5", "Muhammad Ali", 35, 'M', Keemari, "MQM", "Kite", KhalidMaqbool);
	candidate* c2 = new candidate("Muhammad Sajid", "42467-3164450-3", "Muhammad Waqas", 30, 'M', Keemari, "JI", "WeighingMachine", SirajUlHaq);
	candidate* c3 = new candidate("Najeeb Haroon", "42355-2911965-7", "Haroon", 55, 'M', Keemari, "PPP", "Arrow", BilawalBhutto);
	candidate* c4 = new candidate("Muhammad Imran", "41249-6928642-5", "Muhammad Kashif", 55, 'M', Keemari, "PTI", "Bat", ImranKhan);
	candidate* c5 = new candidate("Muhammad Ali", "42368-8762343-1", "Nabeel Shiekh", 45, 'M', Keemari, "PmlN", "Loin", NawazShareef);
	cout << "Candidate of District Karachi keemari are:" << endl;
	c1->DisplayDetails();
	c2->DisplayDetails();
	c3->DisplayDetails();
	c4->DisplayDetails();
	c5->DisplayDetails();
}
int CnicSearch(string cnic, string FileName) {
	ifstream fopen;
	fopen.open(FileName);
	string line;
	int result = 0;
	while (getline(fopen, line))
	{
		if (line.find(cnic) != std::string::npos) {
			result = 1;
		}
	}
	fopen.close();
	return result;
}
void winnerParty() {
	int c;
	voter* v;
	v = new voter;
	cout << "Enter the District Which You want To see Elections Result\nSelect District:\n1-KarachiEast\t2-KarachiCentral\t3-KarachiSouth\n4-KarachiWest\t5-Korangi\t6-Keemari" << endl;
	cin >> c;
	switch (c) {
	case 1:
		cout << "Therefore, Winner in District " << KarachiEast.GetDistrictName() << " :" << v->DistrictWinner(KarachiEast) << endl;
		break;
	case 2:
		cout << "Therefore, Winner in District " << KarchiCentral.GetDistrictName() << " :" << v->DistrictWinner(KarchiCentral) << endl;
		break;
	case 3:
		cout << "Therefore, Winner in District " << KarachiSouth.GetDistrictName() << " :" << v->DistrictWinner(KarachiSouth) << endl;
		break;
	case 4:
		cout << "Therefore, Winner in District " << KarachiWest.GetDistrictName() << " :" << v->DistrictWinner(KarachiWest) << endl;
		break;
	case 5:
		cout << "Therefore, Winner in District " << Korangi.GetDistrictName() << " :" << v->DistrictWinner(Korangi) << endl;
		break;
	case 6:
		cout << "Therefore, Winner in District " << Keemari.GetDistrictName() << " :" << v->DistrictWinner(Keemari) << endl;
		break;
	default:
		cout << "OPPS!You Entered Wrong choice!" << endl;
		c = 0;
		break;
	}
}
////////////////////////////////////////////////////////////////////////////

void VoterRegistration() {
	string cnic;
	//District d;
	voter* v1 = new voter;
	int age;
	string name, fname, Gender;
	cout << "Enter Cnic Which You want To Register" << endl;
	cin >> cnic;
	int i = CnicSearch(cnic, "VoterData.txt");
	if (i == 1) {
		cout << "OOPS!The voter is already Voted!..." << endl;
	}
	i = CnicSearch(cnic, "UnCastVoterData.txt");
	if (i == 1) {
		cout << "OOPS!The voter is already Rigistered!..." << endl;
	}
	if (i == 0) {
		cout << "Voter is eligible for Registration" << endl;
		cout << "-----------------------------------------------------" << endl;
		cout << "Enter Voter's Name" << endl;
		cin >> name;
		cout << "Enter Voter's Father Name" << endl;
		fflush(stdin);
		cin >> fname;
		fflush(stdin);
		char c;

		cout << "Enter Age\n";
		fflush(stdin);
		cin >> age;
		if (age < 18 || age>150) {
			for (i = 0; age < 18 || age >150; i++) {
				cout << "Your age is must be greater than 17\nEnter Age again\n";
				fflush(stdin);
				cin >> age;
			}
		}
		do {
			cout << "Select Gender M for Male and F for Female" << endl;
			cin >> c;
			switch (c) {
			case 'M':
				v1->set_PersonDetails(name, cnic, fname, age, 'M');
				break;
			case 'm':
				v1->set_PersonDetails(name, cnic, fname, age, 'M');
				break;
			case 'F':
				v1->set_PersonDetails(name, cnic, fname, age, 'F');
				break;
			case 'f':
				v1->set_PersonDetails(name, cnic, fname, age, 'F');
				break;
			default:
				cout << "You Write Worng Option..\nSelect Gender M for Male and F for Female AGAIN" << endl;
				cin >> c;
				break;

			}
		} while (c != 'm' && c != 'M' && c != 'F' && c != 'f');	cout << "Enter Voter'sDistrict " << endl;
		int choice;
		cout << "Select District:\n1-KarachiEast\t2-KarachiCentral\t3-KarachiSouth\n4-KarachiWest\t5-Korangi\t6-Keemari" << endl;
		cin >> choice;
		fflush(stdin);
		switch (choice) {
		case 1:
			v1->set_PersonDetails(name, cnic, fname, age, KarachiEast);
			break;
		case 2:
			v1->set_PersonDetails(name, cnic, fname, age, KarchiCentral);

			break;
		case 3:
			v1->set_PersonDetails(name, cnic, fname, age, KarachiSouth);
			break;
		case 4:
			v1->set_PersonDetails(name, cnic, fname, age, KarachiWest);
			break;
		case 5:
			v1->set_PersonDetails(name, cnic, fname, age, Korangi);
			break;
		case 6:
			v1->set_PersonDetails(name, cnic, fname, age, Keemari);
			break;
		default:
			cout << "OOPS!! You Entered Something Wrong" << endl;
			choice = 0;
			break;
		}
		if (choice != 0) {
			v1->store_UnCastVoterData();
			cout << "\n" << name << " having cnic: " << cnic << " is Rigistered In a Voting Machine Sucessfully!!.." << endl;
		}
		else {
			cout << "Enter All Details Again" << endl;
		}
	}
}
void ViewLiveVotes() {
	voter* v;
	int countPmln = 0, countJI = 0, countPPP = 0, countMQM = 0, countPTI = 0;
	v = new voter;
	countPTI = v->countTotalVotesPartyWise("PTI");
	countJI = v->countTotalVotesPartyWise("JI");
	countPmln = v->countTotalVotesPartyWise("PmlN");
	countMQM = v->countTotalVotesPartyWise("MQM");
	cout << "--------------------------- Welcome To View Live Votes -------------------------------------" << endl;
	cout << "\n*********************************************************************************\n";
	cout << "TotalVotes : " << v->countTotalVoters() << endl;
	cout << "PTI : " << countPTI << endl;
	cout << "JI : " << countJI << endl;
	cout << "PMLN : " << countPmln << endl;
	cout << "MQM : " << countMQM << endl;
	cout << "\n*********************************************************************************\n";
	if (countPTI > countPmln && countPTI > countPPP && countPTI > countMQM && countPTI > countJI) {
		cout << "\nPTI candidate " << ImranKhan.getName() << " is on leading\n\n";
	}
	else if (countPmln > countPTI && countPmln > countPPP && countPmln > countMQM && countPmln > countJI) {
		cout << "\nPmln candidate " << NawazShareef.getName() << " is on leading\n\n";
	}
	else if (countPPP > countPTI && countPPP > countPmln && countPPP > countMQM && countPPP > countJI) {
		cout << "\nPPP candidate " << BilawalBhutto.getName() << " is on leading\n\n";
	}
	else if (countMQM > countPTI && countMQM > countPPP && countMQM > countPmln && countMQM > countJI) {
		cout << "\nMQM candidate " << KhalidMaqbool.getName() << " is on leading\n\n";
	}
	else if (countJI > countPTI && countJI > countPPP && countJI > countMQM && countJI > countPmln) {
		cout << "\nJI candidate " << SirajUlHaq.getName() << "is on leading\n\n";
	}
	else {
		cout << "\nUndecidable condition\n\n";
	}
	cout << "**************************************************************\n";
}
void MainAdmin() {
	voter* v1 = new voter;
	int ch, age;
	string cnic;
	int administratorchoice = 0, district_choice, n, dis;
	int n1, c;
	while (administratorchoice != 6) {
		cout << "\n*******************************************\n";

		cout << "\n--------WELCOME TO ADMINISTRATION----------\n";
		cout << "\n*******************************************\n";
		cout << "1. Leading Party\n";
		cout << "2. Voter's log.\n";
		cout << "3. Voter's Registration\n";
		cout << "4. Statistics\n";
		cout << "5. Winner Party in each District.\n";
		cout << "6. Exit\n";
		cout << "Kindly, Enter your choice: ";
		cin >> administratorchoice;
		system("cls");
		switch (administratorchoice) {
		case 1:
			ViewLiveVotes();
			break;
		case 2:
			cout << "\n----------------------------------\n";
			cout << "1. For all voters data.\n";
			cout << "2. For specfic voter.\n";
			cin >> ch;
			if (ch == 1) {
				v1->Read_VoterData();
			}
			else if (ch == 2) {
				cout << "Enter CNIC number: ";
				cin >> cnic;
				v1->Show_VoterByCnic(cnic);
				cin.get();
			}
			else {
				break;
			}
			cout << "Press Any Key To Proceed..." << endl; cin.get(); cin.get(); system("cls");
			break;
		case 3:
			VoterRegistration();
			cout << "Press Any Key To Proceed..." << endl; cin.get(); cin.get(); system("cls");
			break;
		case 4:
			cout << "\n------------------------------------\n";
			cout << "1. For age wise.\n";
			cout << "2. For gender wise.\n";
			cout << "3. For exit.\n";
			cin >> ch;
			if (ch == 1) {
				cout << "Enter age number for which you want to see: ";
				cin >> age;
				cout << "Total Votes casted Of the " << age << " are " << v1->TotalVotersRecord_ageWise(age) << endl;
			}
			else if (ch == 2) {
				v1->GenderWiseVotersRecord();
			}
			else {
				break;
			}
			cout << "Press Any Key To Proceed..." << endl; cin.get(); cin.get(); system("cls");
			break;
		case 5:
			winnerParty();
			cout << "Press Any Key To Proceed..." << endl; cin.get(); cin.get(); system("cls");
			break;
		case 6:
			break;
		defualt:
			cout << "Invalid Choice!........" << endl;
			cout << "Press Any Key To Proceed..." << endl; cin.get();; cin.get(); system("cls");
			break;
		}
	}
}
int FrontPage() {
	cout << "\n\n**************************************************************************\n";
	cout << "*****************************************************************************\n";
	cout << "------------------------ELECTRONIC VOTING MACHINE----------------------------\n";
	cout << "*****************************************************************************\n";
	cout << "****************************************************************************\n";
	cout << "\n\n_____________________REPRESENTED BY_________________________________\n\n";
	cout << "\t\t(22k-4591) Ayesha Abdul Rahman\n";
	cout << "\t\t(22k-4546) Fiza Farooq\n";
	cout << "\n\n\n\n\n\n\n\n\nEnter any key to proceed." << endl;
	cin.get();
	system("Cls");
	return 0;
}

void castVote() {
	string cnic;
	voter* v;
	v = new voter;
	cout << "For This Enter Your cnic:(Including - )" << endl;
	cin >> cnic;
	int i = v->Search_VoterByCnic(cnic);//CnicSearch(cnic, "VoterData.txt");
	if (i == 1) {
		cout << "OOPs! " << cnic << " has already found Voted......." << endl;
	}
	else {
		int j = CnicSearch(cnic, "UnCastVoterData.txt");
		if (j == 1) {
			cout << "\nVoter's Data........." << endl;

			v->Read_RigisteredVoterData(cnic);
			cout << "Press Any Key To Proceed..." << endl; cin.get(); cin.get();
			if (v->Search_VoterDistrict(cnic) == "KarachiCentral") {
				Dis_KarachiCentral_Candidates();
			}
			else if (v->Search_VoterDistrict(cnic) == "KarachiEast") {
				Dis_KarachiEast_Candidates();
			}
			else if (v->Search_VoterDistrict(cnic) == "KarachiWest") {
				Dis_KarachiWest_Candidates();
			}

			else if (v->Search_VoterDistrict(cnic) == "KarachiSouth") {
				Dis_KarachiWest_Candidates();
			}

			else if (v->Search_VoterDistrict(cnic) == "Korangi") {
				Dis_Korangi_Candidates();
			}

			else if (v->Search_VoterDistrict(cnic) == "Keemari") {
				Dis_Keemari_Candidates();
			}
			voter* v1;

			v1 = new voter;

			v = (v->SetVoter(v1, cnic));
			cout << "\n\n***********************************************************\n\n";
			cout << "Enter your vote...\n";
			cout << "\t Press 1,2,3,4,5 \n";
			cout << "1.PTI\n";
			cout << "2.PMLN\n";
			cout << "3.JamateIslami\n";
			cout << "4.MQM\n5.PPP\n ";
			cout << "\n\n***********************************************************\n\n";
			fflush(stdin);
			int vote;
			fflush(stdin);
			cin >> vote;
			switch (vote) {
			case 1:
				v->setVote("PTI");
				v->store_CastVoterData();
				cout << "Your Vote Has Been Cast Sucessfully!!.." << endl;
				break;
			case 2:
				v->setVote("PmlN");
				v->store_CastVoterData();
				cout << "Your Vote Has Been Cast Sucessfully!!.." << endl;
				break;
			case 3:
				v->setVote("JI");
				v->store_CastVoterData();
				cout << "Your Vote Has Been Cast Sucessfully!!.." << endl;
				break;
			case 4:
				v->setVote("MQM");
				v->store_CastVoterData();
				cout << "Your Vote Has Been Cast Sucessfully!!.." << endl;
				break;
			case 5:
				v->setVote("PPP");
				v->store_CastVoterData();
				cout << "Your Vote Has Been Cast Sucessfully!!.." << endl;
				break;
			default:
				cout << "\nYou Entered Wrong Option!!..." << endl;
			}

			//deallocate v1
			//delete(v1);

		}
		else {
			cout << "Opps! Voter is not Rigistered yet!!" << endl;
		}


	}
	//delete(v);
}
void Admin() {
	string pwd = "fast@pk#";//pwd = password
	string entered_pwd;
	int i;
	cout << "\n***********************************************************************************************";
	cout << "\n----------------------------------------------------------------------------------------------\n";
	cout << "\n\nInstruction:\nYou cannot enter Passward more than 4 times otherwise Administration will be blocked\n";
	cout << "\n************************************************************************************************";
	cout << "\n----------------------------------------------------------------------------------------------\n";
	cout << "Enter the password: ";
	cin >> entered_pwd;
	if (pwd == entered_pwd) {
		cout << "Right Password!...\nEnter any key to Proceed!!" << endl;
		cin.get();
		system("cls");
		MainAdmin();

	}
	if (pwd != entered_pwd) {
		for (i = 3; (pwd != entered_pwd) && i > 0; i--) {
			cout << "Please enter the correct password you have" << i << " choices : " << endl;
			cin >> entered_pwd;
			if (pwd == entered_pwd) {
				cout << "Right Password!...\nEnter any key to Proceed!!" << endl;
				cin.get();
				system("cls");
				MainAdmin();

			}
		}
	}
	else {
		cout << "\nYou entered so many wrong passwords. This account is locked now." << endl;
	}
	system("cls");
}



int main() {
	int i;
	int choice;
	FrontPage();
	do {
		cout << "*****************************************************************************\n";
		cout << "*****************************************************************************\n";
		cout << "\n\n ###### Welcome to Election/Voting 2023 #####\n" << endl;
		cout << "*****************************************************************************\n";
		cout << "*****************************************************************************\n";
		cout << "\n\n 1. Cast the Vote";
		cout << "\n\n 2. Login as an Administrator";
		cout << "\n\n 3. View live Voting Score.";
		cout << "\n\n 0. Exit.";
		cout << "\n\n Please enter your choice : ";
		fflush(stdin);
		cin >> choice;
		system("cls");

		switch (choice)
		{
		case 1: castVote(); cout << "Press Any Key To Proceed..." << endl; cin.get(); cin.get(); system("cls"); break;
		case 2: Admin(); cout << "Press Any Key To Proceed..." << endl; cin.get(); cin.get(); system("cls"); break;
		case 3: ViewLiveVotes(); cout << "Press Any Key To Proceed..." << endl; cin.get(); cin.get(); system("cls");; break;
		case 0: cout << "Closing Machine!!.." << endl; break;
		default: cout << "\n Error: Invalid Choice" << endl; break;
		}

	} while (choice != 0);
	cin.get();

	return 0;
}
