#include<stdio.h>
#include<iostream>
using namespace std;
#include<stdlib.h>
#include<string.h>
#include<fstream>
#include<string>

void reverse(char *str, int len);
int intToStr(int x, char str[], int d);
char* ftoa(float n, int afterpoint);
int returnint(char ch);
int returngrade(int n);
int converttoint(char* str);
bool is_equal(char* right, char* left);
char inttochar(int n);
char* converttostring(int num);

struct hashTable{
	char* key;
	char* value;
	hashTable* next;
};

#define SIZE 50;
unsigned long hash_function(char *str);
struct hashTable * createNewNode(char *key, char *value);
void put(struct hashTable** hashTable, char *key, char *value);
struct hashTable * get(struct hashTable** hashTable, char* key, char *value);
void display(hashTable** hashtable);
void clearHashtable(hashTable** hashtable);
void remove_pair(hashTable** hashtable, char* key, char* value);

struct record{
	char** data;
};

struct tableMetadata{
	record** tableData;
	char* tableName;
	int number_of_columns;
	char** column_names;
	int index;
	int capacity;
	char* value;
	char* query_operation;
};

