/* Assignment: 4
Campus: Ashdod
Author: Patrick lugassy, ID: 319266177
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>                              //include Library //
#include <string.h>

#define Max_chars 80
#define Max_chars_defenition 200

char*** allocate_dictionary(int numOfWords);    // function to allocate memory for dictionary //
void init_entry(char*** Entry, int* entries_sizes, int entry_num);   // function for recive the word and the defenition// 
void low_TO_up_definition(char* Entry); // function convert from lowercase to appercase //
int Sorted_words(char***dictionary, int dictionary_size, int* Entry_sizes);  // function sort the word In a lexicographic order //
void print_dictionary(char*** dictionary, int dictionary_size, int* entries_sizes); // function that print the dictionary //
void freeEntry(char** Entry, int* Size);  // function free the allocate memory of the entry //
void search_word(char***dictionary, int dictionary_size, int* entries_sizes); // function for search if the word are in the dictionary //
int existWord(char ***dictionary, int dictionary_size, char* word); // function the return a value if the word exist in the dictionary //
void free_memory(char***dictionary, int dictionary_size, int* entries_sizes); // function free the allocate memory of the program //
void free_entry(char** entry, int size); // this function free the allocate memory in each entry //

int main() {
	int* entries_sizes; // create pointer //

	int numOfWords, doubles;    // create veriables //
	char*** dictionary;

	printf("Enter dictionary size: \n");  // print to screen  //
	scanf("%d", &numOfWords);  // scan from the user the num of word in the dictionary //
	entries_sizes = (int*)malloc(sizeof(int)*numOfWords);  // allocate memory for the entries according to the number of words the user insert //
	dictionary = allocate_dictionary(numOfWords); // dictionary equeal to the place allocate memory //
	for (int i = 0; i <numOfWords; ++i)  // loop from 0 to the number of words in the dictionary //
	{
		init_entry(dictionary, entries_sizes, i); // call to function init entry //

	}

	Sorted_words(dictionary, numOfWords, entries_sizes);// call a function that sorted the words in the dictionary In a lexicographic order //
	printf("\n");
	print_dictionary(dictionary, numOfWords, entries_sizes); // function print the dictionary //
	printf("\n search words in the dictionary: \n\n"); // print to screen that the search step begin //
	search_word(dictionary, numOfWords, entries_sizes); // call function that search if the word Exists in the dictionary //
	free_memory(dictionary, numOfWords, entries_sizes);  // call function that free the memory we allocate in the program// // call the function that free the dictionary memory //
	return 0;
}

void search_word(char***dictionary, int dictionary_size, int* entries_sizes) {  // function search if the word we choose to search Exist //
	int index;  // creat variable //
	char *x, word[Max_chars];  // create a pointer x and an array with place of 80 chars //

	do   // do - whille loop //
	{
		printf("\n please enter the word you want to search : \n");  // ask the user to insert word to search //
		printf("please insert the first letter appercase!\n");
		scanf("%s", word);  // get the word from the user //


		if ((index = existWord(dictionary, dictionary_size, word)) != -1) // if the index equal to a int we recive fron the function existWord is not -1 it will enter to the condition //
		{
			printf("\n the word : %s - exists in the dictionary \n", dictionary[index][0]); //print to screen that the word we search exist in the dictionary //
			printf("\n defenition : \n");
			printEnrty(dictionary[index], entries_sizes[index]); // this function print the defenition of this word //
		}
		else if (strcmp(word, "exit") != 0 && strcmp(word, "EXIT") != 0)   // mean that the word not exist in the dictionary //
		{
			printf(" \n Unknown word ! \n"); // print to screen that this word we search is a Unknown word //  
		}
		else
		{
			printf("\n You decided to leave the dictionary ! \n"); // if the two condition above dont happend mean that the user choose to exit from the dictionary //

		}

	} while (strcmp(word, "exit") != 0 && strcmp(word, "EXIT") != 0);   // while the user not entered the word 'exit' the loop continue to work //
	return 0;

}

int existWord(char *** dictionary, int dictionary_size, char* word) {  // this function check if the word exist , if it exist it will return the number of the i in the loop //

	int i;  // create variables //
	for (i = 0; i < dictionary_size; ++i) //loop from 0 to the dictionary size, mean the number of word in the dictionary // 
	{
		if (strcmp(word, dictionary[i][0]) == 0)  // check if the word we entered and the word in the dictionary  is equal (with strcmp) //
			return i;  // if the words equal it will return the value of i //
	}

	return -1; // if the word are not equal it will return -1 to the function call it //
}

char*** allocate_dictionary(int numOfWords) {  // this function allocate the memory for the dictionary //

	char*** dictionary;  // create the pointer dictionary  //  
	dictionary = (char***)malloc(numOfWords * sizeof(char**)); // the dictionary is equal to the allocate memory of the numbers of word the user insert //
	if (dictionary == NULL)  // check if the allocation Succeeded //
	{
		return NULL; // if the allocate memory faild it will return NULL //
	}
	return dictionary;// return the dictionary  with the memory we allocate //


}


void reset_arr(char arr[], int size) {   // this function reset all the array to '\0' //
	int i; // create variable //
	for (i = 0; i < size; i++) // loop from 0 to the size we send to the function //
	{
		arr[i] = '\0'; // All elements in the array is with '\0' //
	}

	return;

}

void init_entry(char*** dictionary, int* entries_sizes, int entry_num) { // function that Fills each entry in the dictionary with a word and definition//
	char word[Max_chars];
	char value[Max_chars_defenition];  // creat arrays with ther max chars //
	reset_arr(word, Max_chars);
	reset_arr(value, Max_chars_defenition);   // reset the arrays to Contain '\0' //
	int NumberOFvalues, i, sizeOfword; // create variable //
	printf("How many definition do you want for the word : \n");  // ask the user how many definition he wants for the word //
	printf("\n"); // enter //
	scanf("%d", &NumberOFvalues);  // scan fron user the number of values //
	entries_sizes[entry_num] = NumberOFvalues;   // array  Contain the numbers of definition //
	dictionary[entry_num] = (char**)malloc((1 + NumberOFvalues) * sizeof(char*)); // allocate memory to the entries //
	if (dictionary[entry_num] == NULL)  // check if the allocat memory sucsess //
	{
		printf("the allocate memory faild! \n"); // if the allocate faild it will  print this on screen //
		exit(1); // exit from the program completely //
	}

	printf("Enter your word: \n"); // ask the user to insert a word //
	scanf("%s", word); // recive the word from the user //
	gets();
	sizeOfword = strlen(word);
	low_TO_up_definition(word);  // send to the function "low_TO_up_definition" to convert from lowercase to appercase letter in the word // 
	for (i = 0; word[i] != '\0'; ++i) {} // loop run until the word in her place is '\0' //


	dictionary[entry_num][0] = (char*)malloc((sizeOfword + 1) * sizeof(char));
	if (dictionary[entry_num] == NULL)  // check if the allocat memory sucsess //
	{
		printf("the allocate memory faild! \n"); // if the allocate faild it will  print this on screen //
		exit(1); // exit from the program completely //
	}
	strcpy(dictionary[entry_num][0], word);
	dictionary[entry_num][i] = '\0';
	//printf("%s ...... %d \n", dictionary[entry_num][0], NumberOFvalues);


	for (int j = 1; j <= NumberOFvalues; ++j)
	{                                                                // loop from 1 to numbers of defenition  of the word //
		printf("Enter your %d vlaue: \n", j); // ask user to put defenition //
		gets(value);
		low_TO_up_definition(value);   // call to function that change the lowercase letter to apercase letter in the definitions //
		for (i = 0; value[i] != '\0'; ++i) {}

		dictionary[entry_num][j] = (char*)malloc((i + 1) * sizeof(char));    // allocate memory to the definitions // 
		if (dictionary[entry_num][j] == NULL)
		{
			printf("the allocate memory faild! \n");   // if the allocate memory faild it print this , and exit from the program //
			exit(1);
		}

		strcpy(dictionary[entry_num][j], value);   // copy the definition into the entry in the dictionary in his place //
		dictionary[entry_num][j][i] = '\0';
		reset_arr(value, Max_chars_defenition);  // reset all the array with '\0' //
		printf("%s \n", dictionary[entry_num][j]); // print to screen the definition, after the change of the low and up letter // 
	}

}





void low_TO_up_definition(char* line) {  // this function change the definition and allso use to change the word from lowercase to appercase letter //
	int i = 0;
	if ((line)[0] >= 'a' && (line)[0] <= 'z')
	{
		(line)[0] -= 'a' - 'A';                       // if the first letter is a small letter it will change it to capital letter //
	}
	for (i = 1; line[i] != '\0'; ++i)
	{
		if (line[i] == ' ' && line[i - 1] == '.')         // if in the definition we have space it will check if 1 char befor is a point //
		{
			if ((line)[i + 1] >= 'a' && (line)[i + 1] <= 'z')         // if the char in the place +1 is a small letter it will change it to capital letter //
			{
				(line)[i + 1] -= 'a' - 'A';
			}
		}
		else
		{
			if (line[i - 1] != ' ')
			{
				if ((line)[i] >= 'A' && (line)[i] <= 'Z')    // if the last char in the definition is a capital letter it will change is to small letter //
				{
					(line)[i] += 'a' - 'A';
				}

			}
		}
	}


}
int Sorted_words(char***dictionary, int dictionary_size, int* Entry_sizes) {   // This function sorts the words in a lexicographic order //
	int i, j, k, m;   // create variables //
	char** temp;
	int counter = 0;

	for (i = 0; i< dictionary_size; ++i)  // loop from 0 to the number of the dictionary size //
	{
		for (j = i + 1; j <dictionary_size; ++j)  // loop start in the second word //
		{
			if (strcmp(dictionary[i][0], dictionary[j][0]) > 0) // compare between two word if it return number bigger than 0 it mean that the second word is bigger  //
			{
				temp = dictionary[i];
				dictionary[i] = dictionary[j];      // swap between the word //
				dictionary[j] = temp;

				m = Entry_sizes[i];
				Entry_sizes[i] = Entry_sizes[j];      // the definition also move to ther place with the words sorted // 
				Entry_sizes[j] = m;

			}
		}
	}

	printf("\n Input NamestSorted names\n");

	for (i = 0; dictionary[i] < dictionary_size; ++i)      // print the sorted words //
	{
		printf("%s\n", dictionary[i][0]);
	}

}

printEnrty(char** entry, int size) {   // this function print the entry in the dictionary //
	int j; // create variable //

	for (j = 0; j < size; j++)
	{
		printf("%d) %s \n", (j + 1), entry[j + 1]);     // loop that print the defenitions //
	}
	printf("\n");
}


void print_dictionary(char*** dictionary, int dictionary_size, int* entries_sizes) {     // function print the dictionary //

	int i, j;   // create variables //

	for (i = 0; i < dictionary_size; i++)          // loop from 0 to the number of word in the dictionary //
	{
		printf("%s \n", (dictionary)[i][0]);       // print the word //

		for (j = 0; j < entries_sizes[i]; j++)
		{
			printf("%s \n", (dictionary)[i][j + 1]);   // this loop print the definition of the word in this current place // 
		}
		printf("\n");
	}
}

void freeEntry(char** Entry, int* Size) {     // this function free the entry in the dictionary //
	int i;
	for (i = 0; i < Size; i++)  // loop from i in place 0 to the size of the entry //
	{
		free(Entry[i]);   // free all the allocate memory of the word and the defenitions in this Entry //
	}

}




void free_entry(char** entry, int size) { // function free the entry in the dictionary //

	for (int i = 0; i < size; ++i)
	{
		free(entry[i]);   // free all the definition and the word in each Entry //
	}
	free(entry); //free the entry//

}



void free_memory(char***dictionary, int dictionary_size, int* entries_sizes) {  // function free the allocate memory //
	for (int i = 0; i < dictionary_size; ++i)
	{
		free_entry(dictionary[i], entries_sizes[i]);   // call function "free_entry " that free the allocate memory in the entry  //
		free(dictionary[i]);   // free the pointer to each entry //
	}
	free(dictionary);  //free the allocate memory of dictionary //
}
