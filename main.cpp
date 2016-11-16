#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

enum Gender {
	male,
	female,
	other
};

struct Person {
	string name;
	double GPA;
	int CST;
	Gender gender;
	string github;
	double score;
	bool picked;
	Person * next;
};

Person * newPerson(string name, double GPA, int CST, Gender gender, string github)
{
	Person * p = new Person;
	p->name = name;
	p->GPA = GPA;
	p->CST = CST;
	p->gender = gender;
	p->github = github;
	p->picked = false;
	p->next = NULL;
	return p;
}

void printPerson(Person * p)
{
	cout << p->name << "\t" << p->GPA << "\t" << p->CST << "\t" << p->gender << "\t" << p->github << p->picked << "\t" <<  p->score << endl;
}

void gpaPrint(Person * p)
{
	cout << p->name << "\t" << p->score << endl;
}

void printList(Person ** p, int size)
{
	for(int i = 0; i < size; i++)
	{
		printPerson(p[i]);
	}
}

void simplePrint(Person ** p, int size)
{
	for(int i = 0; i < size; i++)
	{
		gpaPrint(p[i]);
	}
}

Gender getGender(string s)
{
	if(s.compare("male") == 0) return male;
	if(s.compare("female") == 0) return female;
	return other;
}

Person * createPerson(string line)
{
	stringstream ss(line);
	string name, github, g;
	Gender gender;
	double gpa;
	int cst;
	ss >> name;
	ss >> gpa;
	ss >> cst;
	ss >> g;
	ss >> github;
	gender = getGender(g);

	return newPerson(name,gpa,cst,gender,github);
}

double scorePerson(Person * p, int x)
{
	if(p->picked) return -1;
	double res = p->GPA * 10 * (20 - x) + p->CST - x * 2;
	if(p->github.length() != 0) res += 10;
	return res;
	// return p->GPA;
}

int filesize(string filename)
{
	ifstream file (filename);
	string line;
	int count = 0;

	while(getline(file, line))
	{
		if(line.length() != 0 && line.at(0) != '#' && line.find("instructions") != 0)
		{
			count++;
		}
	}

	return count;
}

double fRand()
{
    return (double)rand() / RAND_MAX;
}

void quicksort(Person * p, int begin, int end)
{
	if(p->next == NULL) return;
	
	concat(quicksort(
}

void scoreAll(Person ** p, int size, int iter)
{
	for(int x = 0; x < size; x++)
	{
		p[x]->score = scorePerson(p[x], iter);
		//if((p[x]->name.compare("Zednanreh") == 0 || p[x]->name.compare("Noskcaj") == 0) && !p[x]->picked) printPerson(p[x]);
	}
}

void PickTopType(Person ** ppl, int size, Gender g, int num)
{
	for(int iter = 0, x = 0; iter < num && x < size; x++)
	{
		if(ppl[x]->score > 0 && ppl[x]->gender == g && !ppl[x]->picked)
		{
			cout << ppl[x]->name << endl;
			ppl[x]->picked = true;
			iter++;
		}
	}
}

void PickTop(Person ** ppl, int size, int f, int m, int un)
{
	PickTopType(ppl,size,female,f);
	PickTopType(ppl,size,male,m);
	PickTopType(ppl,size,other,un);
}

int main(int argc, char ** argv)
{
	string filename = argv[1];
	filename = filename.substr(6);
	ifstream file(filename);
	string line;
	int size = filesize(filename);
	Person ** arr = new Person*[size];
	int nfemales;
	int nmales;
	int nunspec;

	for(int i = 0; getline(file,line); )
	{
		if(line.length() != 0 && line.at(0) != '#')
		{
			stringstream ss(line);
			string first;
			ss >> first;

			if(first.compare("instructions") == 0)
			{
				ss >> nfemales;
				ss >> nmales;
				ss >> nunspec;
			}
			else
			{
				arr[i] = createPerson(line);
				i++;
			}
		}
	}
	
	for(int i = 0; i < 20; i += 3)
	{
//		cout << "Round " << i << endl;
		scoreAll(arr,size,i);
		quicksort(arr,0,size-1);
		simplePrint(arr,size);
		PickTop(arr,size,nfemales,nmales,nunspec);	
	}
}
