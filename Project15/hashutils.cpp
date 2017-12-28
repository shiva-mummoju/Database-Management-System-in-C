#include"Header.h";



unsigned long hash_function(char *str)
{
	unsigned long hash = 5381;
	int c;
	while (c = *str++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	return hash%SIZE;
}

struct hashTable * createNewNode(char *key, char *value){
	struct hashTable *newnode = (struct hashTable *)calloc(1, sizeof(struct hashTable));
	newnode->key = (char*)malloc(sizeof(char) * 100);
	newnode->value = (char*)malloc(sizeof(char) * 100);
	strcpy(newnode->key, key);
	newnode->value = value;
	newnode->next = NULL;
	return newnode;
}

void put(struct hashTable** hashTable, char *key, char *value)
{
	struct  hashTable *temp = NULL;
	temp = createNewNode(key, value);

	int hash = hash_function(key);

	if (hashTable[hash] == NULL){
		hashTable[hash] = temp;
		return;
	}
	else
	{
		struct hashTable *cur = NULL;
		cur = hashTable[hash];
		struct hashTable *pre = NULL;
		while (cur != NULL){
			if (strcmp(cur->value, temp->value) == 0){
				return;
			}
			pre = cur;
			cur = cur->next;
		}
		pre->next = temp;
	}
}

 hashTable * get(hashTable** hashTable, char* key, char *value){

	int hash = hash_function(key);
	if (hashTable[hash] != NULL)
	{
		if (strcmp(hashTable[hash]->value, value) == 0){
			return hashTable[hash];
		}

		struct hashTable *temp = hashTable[hash];
		while (temp != NULL){
			if (strcmp(temp->value, value) == 0)
				return temp;
			temp = temp->next;
		}
		return NULL;
	}
	else{
		return NULL;
	}
}

 void display(hashTable** hashtable){
	 for (int i = 0; i < 50; i++){
		 if (hashtable[i] == NULL){
			 continue;
		 }
		 else{
			 hashTable* temp = NULL;
			 temp = hashtable[i];
			 while (temp != NULL){
				 cout << temp->key << " " << temp->value << endl;
				 temp = temp->next;
			 }
		 }
	 }
 }

 void clearHashtable(hashTable** hashtable){
	 for (int i = 0; i < 50; i++){
		 if (hashtable[i] == NULL){
			 continue;
		 }
		 else{
			 hashtable[i] = NULL;
		 }
	 }
 }


 void remove_pair(hashTable** hashtable, char* key, char* value){
	 int hash = hash_function(key);
	 hashTable* cur = hashtable[hash];
	 hashTable* pre = cur;
	 if (strcmp(hashtable[hash]->key, key) == 0 && strcmp(hashtable[hash]->value, value)){
		 hashtable[hash] = NULL;
		 return;
	 }
	 while (cur != NULL && strcmp(cur->key, key) == 0 && strcmp(cur->value, value) == 0){
		 

		 pre = cur;
		 cur = cur->next;
	 }

	 if (cur == NULL)
		 return;
	 pre->next = cur->next;
 }