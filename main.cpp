//***********************************************************//
//** Author:Saakshi More **//
//** University ID: N13275625 **//
//** Date Created: November 10, 2021 **//
//** Assignment 2: Concordance of a File **//
//** UH-1000 Computer Programming for Engineers, NYUAD **//
//** Problem: **//
//** a program that processes a text fileand produces a concordance : 
// an alphabetical listing of the words in the fileand the number of 
// times each word appears(frequency)**//
//***********************************************************//

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>//library to use set flag and set width
#include <ctype.h>

using namespace std;

void readwords(string fname, string*& a, int& size, int*& freq);
string* resize(string*& oldarr, int size, string word);
int* fresize(int*& oldarr, int size);
bool checkrepetition(string word, string* a, int size);
int findpos(string word, string* a, int size);
void sortarray(string*& a, int*& freq, int size);
void output(string*& a, int*& freq, int size);
void print(string*& a, int*& freq, int size);

int main()
{
	string filename;
	cout << "Enter file name: " << endl;
	cin >> filename;
	int size = 0;
	string* a= new string[size];//allocate array of string pointers of size 0 to store unique words
	int* freq = new int[size];// allocate array of integer pointers of size 0 to store the frequency of each word
	readwords(filename,a,size,freq);
	sortarray(a, freq, size);
	output(a, freq, size);
	print(a, freq, size);
	delete[]a;//deallocate a
	delete[]freq;//deallocate freq
	return 0;
}

//function to read tokens from input text file
void readwords(string fname, string*& a, int& size, int*& freq)//a, freq and size are passed by reference
{
	ifstream in;//opening an input file stream
	in.open(fname, ios::in);//opening a pre-existing file whose name is given by the user
	if (in.fail())//file cannot be opened
	{
		cerr << "Error opening file" << endl;
		exit(-1);
	}
	string word="";//initializing a string variable to store words obtained from the file
	cout << "\n";
	char temp;//declaring a temporary character variable
	in.get(temp);//temporary character variable retrieves characters from the file, including white spaces
	while(!in.eof())//iterate till the end of file is reached
	{
		temp = tolower(temp);//convert retrieved character into its lower case to avoid case-senstivity issues. Non-alphabetic characters remain the same.
		if (((int)temp>=97)&&((int)temp<=122))//using ASCII values to determine whether the character is an alphabet
		{
			word = word + temp;//append the character to string if the character is an alphabet
		}
		if(((int)temp<97)||((int)temp>122)||(in.eof()==true))//if the file pointer encounters a non-alphabetic character or end of file condition
		{
			if (word!="")//to avoid garbage value in case non-alphabetic characters appear consecutively
			{
				if (checkrepetition(word, a, size) == false)//if word is not found in the concordance database
				{
					size++;
					a = resize(a, size, word);//dynamically increase the size of concordance database by 1
					freq = fresize(freq, size);//dynamically increase the size of frequency database by 1
				}
				else
				{
					int pos = findpos(word, a, size);//find what position the word is at
					(freq[pos])++;//increment the corresponding frequency value by 1
				}			
			}
			word = "";//set word to null after the previous word has been processed and added to the database
		}
		in.get(temp);//retrieve the next character in the file
	}
	in.close();//close file
}
//function to check if the word formed is already present in the concordance database
bool checkrepetition(string word, string* a, int size)
{
	int count = 0;
	for (int i = 0;i < size;i++)
	{
		if (word == a[i])
		{
			return true;//return true as soon as string matches
		}
	}
	return false;
}

//function to increase size of concordance database
string* resize(string*& oldarr, int size, string word)
{
	string* newarr = new string [size];//dynamically allocate new block of string memory
	for (int i = 0;i < (size - 1);i++)
	{
		newarr[i] = oldarr[i];//assign values from the previous array to the new one
	}
	delete[]oldarr;//deallocate the old array copy memory
	oldarr = new string[size];
	for (int i = 0;i < (size - 1);i++)
	{
		oldarr[i] = newarr[i];//assign values from the previous array to the new one
	}
	oldarr[size - 1] = word;
	delete[]newarr;
	return oldarr;//return the string pointer pointing to the new array of increased size
}

//function to increase size of frequency database
int* fresize(int*& oldarr, int size)
{
	int* newarr = new int[size];//dynamically allocate new block of integer memory
	for (int i = 0;i < (size - 1);i++)
	{
		newarr[i] = oldarr[i];//assign values from the previous array to the new one
	}
	delete[]oldarr;//deallocate the old array copy memory
	oldarr = new int[size];
	for (int i = 0;i < (size - 1);i++)
	{
		oldarr[i] = newarr[i];//assign values from the previous array to the new one
	}
	oldarr[size - 1] = 1;
	delete[]newarr;
	return oldarr;//return the integer pointer pointing to the new array of increased size
}

//function to find the position of word already in the database
int findpos(string word, string* a, int size)
{
	for (int i = 0;i < size;i++)
	{
		if (word.compare(a[i]) == 0)
			return i;
	}
	return -1;//return -1 in case word is not found. Will not execute unless there is a bug in the program.
}

//function to sort the concordance databse using bubble sort
void sortarray(string*& a, int*& freq, int size)
{
	for (int i = 0;i < size;i++)
	{
		for (int j = 0;j < ((size - 1)-i);j++)
		{
			if (a[j] > a[j + 1])
			{
				string temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
				int tem = freq[j];//the frequency database must be sorted along with the word list
				freq[j] = freq[j + 1];
				freq[j + 1] = tem;
			}
		}
	}

}

//function to output concordance data to file
void output(string*& a, int*& freq, int size)
{
	ofstream out;
	cout << "Enter output text file name" << endl;
	string filename;
	cin >> filename;
	out.open(filename, ios::out);//opening a file in output mode
	if (out.fail())//opening fails
	{
		cerr << "Error opening file" << endl;
		exit(-1);
	}
	out.setf(ios_base::right);//right adjustment formatting (adds fill characters to the left)
	out << "\nConcordance of file:" << endl;
	for (int i = 0;i < size;i++)
	{
		out << setw(20) << a[i] << setw(10) << freq[i] << endl;//sets the width parameter of the stream out to 20 before the word data and 10 before the frequency data
	}
	cout << "Data stored in concordance file!\n" << endl;//Confirmatory message
	out.close();//close file
}

//function to print concordance on output screen
void print(string*& a, int*& freq, int size)
{
	cout.setf(ios_base::right);//right adjustment formatting (adds fill characters to the left)
	cout << "Concordance of file:" << endl;
	for (int i = 0;i < size;i++)
	{
		cout << setw(20) << a[i] << setw(10) << freq[i] << endl;//sets the width parameter of the stream out to 20 before the word data and 10 before the frequency data
	}
	
}

