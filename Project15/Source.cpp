#include"Header.h"


hashTable** hashtable;
tableMetadata** allTables = NULL;
int table_count = 3;

void loadGlobalTables(){
	allTables = (tableMetadata**)malloc(sizeof(tableMetadata*) * 3);
	table_count = 3;
	allTables[0] = NULL;
	allTables[0] = (tableMetadata*)malloc(sizeof(tableMetadata));
	allTables[0]->tableName = "marks";
	allTables[0]->number_of_columns = 8;
	allTables[0]->capacity = 10;
	allTables[0]->index = 0;
	allTables[0]->tableData = NULL;
	allTables[0]->tableData = (record**)malloc(sizeof(record*)*allTables[0]->capacity);
	allTables[0]->column_names = (char**)malloc(sizeof(char*)*allTables[0]->number_of_columns);
	allTables[0]->column_names[0] = "roll";
	allTables[0]->column_names[1] = "name";
	allTables[0]->column_names[2] = "m1";
	allTables[0]->column_names[3] = "m2";
	allTables[0]->column_names[4] = "m3";
	allTables[0]->column_names[5] = "m4";
	allTables[0]->column_names[6] = "avg";
	allTables[0]->column_names[7] = "cgpa";
	allTables[1] = NULL;
	allTables[1] = (tableMetadata*)malloc(sizeof(tableMetadata));
	allTables[1]->tableName = "infos";
	allTables[1]->number_of_columns = 5;
	allTables[1]->capacity = 10;
	allTables[1]->column_names = (char**)malloc(sizeof(char*)*allTables[0]->number_of_columns);
	allTables[1]->column_names[0] = "roll";
	allTables[1]->column_names[1] = "phone";
	allTables[1]->column_names[2] = "address";
	allTables[1]->column_names[3] = "city";
	allTables[1]->column_names[4] = "pincode";
	allTables[1]->tableData = NULL;
	allTables[1]->index = 0;
	allTables[1]->tableData = (record**)malloc(sizeof(record*)*allTables[1]->capacity);
	hashtable = (hashTable**)malloc(sizeof(hashTable*) * 50);
	for (int i = 0; i < 50; i++){
		hashtable[i] = NULL;
	};
 }






void increase_capacity_mark(int i){
	record** s = (record**)malloc((allTables[i]->capacity * 2) * sizeof(record*));
	for (int j = 0; j<allTables[i]->index; j++){
		s[j] = allTables[i]->tableData[j];
	}
	allTables[i]->tableData = s;
	allTables[i]->capacity = allTables[i]->capacity*2;
}

	record** duplicate_mark;
	int duplicate_mark_index = 0;
	int duplicate_mark_capacity = 10;
	


void overwrite_mark(int k){

	for (int i = 0; i<(duplicate_mark_index); i++){
		for (int j = 0; j<allTables[k]->index; j++){
			if (strcmp(duplicate_mark[i]->data[0], allTables[k]->tableData[j]->data[0])){

				allTables[k]->tableData[allTables[k]->index] = duplicate_mark[i];

				break;
			}
		}
	}
}



void add_to_duplicate_mark(record* m){

	if (duplicate_mark_index == duplicate_mark_capacity){
		record** s = (record**)calloc((duplicate_mark_capacity)* 2, sizeof(record*));
		for (int i = 0; i<(duplicate_mark_index); i++){

			s[i] = (duplicate_mark[i]);
		}
		duplicate_mark = s;
		duplicate_mark_capacity = (duplicate_mark_capacity)* 2;
	}
	duplicate_mark[duplicate_mark_index] = m;
	(duplicate_mark_index) = (duplicate_mark_index)+1;

}


bool not_duplicate_mark(int j,record* l){
	for (int i = 0; i<allTables[j]->index ; i++){
		if (strcmp(allTables[j]->tableData[i]->data[0], l->data[0])==0){
			add_to_duplicate_mark(l);
			return false;
		}
	}
	return true;
}

void add_row(int i, record* r){
	if (allTables[i]->index == allTables[i]->capacity){
		increase_capacity_mark(i);
	}
	if (not_duplicate_mark(i, r)){
		allTables[i]->tableData[allTables[i]->index] = r;
		allTables[i]->index = allTables[i]->index + 1;
	}
}

void add_to_mark_array(int i,char* temp){
	char* tmp = strtok(temp, ",");
	record* l = (record*)malloc(sizeof(record));
	l->data = (char**)malloc(sizeof(char*)*allTables[i]->number_of_columns);
	l->data = (char**)malloc((allTables[i]->number_of_columns)*sizeof(char*));
	int j = 0;
	for (j = 0; j < allTables[i]->number_of_columns; j++){
		if (tmp != NULL){
			l->data[j] = tmp;

			tmp = strtok(NULL, ",\n");
		}
		else{
			l->data[j] = "NA";
		}
	}
	add_row(i, l);
}

void loadmarksarray(int i,char* filename){
	FILE * stream = fopen(filename, "r");
	if (stream == NULL){
		cout << "Error in file name. " << endl;
		return;
	}
	char line[1024];
	int choice = 0;
	int jump = 0;
	duplicate_mark = (record**)malloc(10 * sizeof(record));
	while (fgets(line, 1024, stream))
	{
		char* temp = _strdup(line);
		if (jump == 0){
			jump = 1;
			continue;
		}
		add_to_mark_array(i,temp);
	}
	if (duplicate_mark_index>0){

		cout << duplicate_mark_index << " Number of duplicates detected! 1 for drop 2 for update: ";
		cin >> choice;
		if (choice == 2){
			overwrite_mark(i);
		}
	}
	duplicate_mark_index = 0;
	duplicate_mark = NULL;
	cout << "File loaded successflly" << endl;
	fclose(stream);
}


void savetofilemark(){
	FILE* fp = NULL;
	char filename[200];
	cout << "Enter the filename: ";
	cin >> filename;
	fp = fopen(filename, "w");
	fprintf(fp, "Roll,name,m1,m2,m3,m4,avg,cgpa\n");
	for (int i = 0; i<allTables[0]->index; i++){
		fprintf(fp, "%s,%s,%s,%s,%s,%s,%s,%s\n", allTables[0]->tableData[i]->data[0], allTables[0]->tableData[i]->data[1], allTables[0]->tableData[i]->data[2], allTables[0]->tableData[i]->data[3], allTables[0]->tableData[i]->data[4], allTables[0]->tableData[i]->data[5], allTables[0]->tableData[i]->data[6], allTables[0]->tableData[i]->data[7]);
	}
}

void savetofileinfo(){
	FILE* fp2 = NULL;
	char filename[200];
	cout << "Enter the filename: ";
	cin >> filename;
	fp2 = fopen(filename, "w");
	fprintf(fp2, "Roll,phone,address,city,pincode\n");
	for (int i = 0; i<allTables[1]->index; i++){
		fprintf(fp2, "%d,%s,%s,%s,%d\n", allTables[1]->tableData[i]->data[0], allTables[1]->tableData[i]->data[1], allTables[1]->tableData[i]->data[2], allTables[1]->tableData[i]->data[3], allTables[1]->tableData[i]->data[4]);
	}
}
void showmarkarray(int j){
		for (int i = 0; i<allTables[j]->number_of_columns; i++)
		{
			cout << allTables[j]->column_names[i] << "\t";
		}
		cout << endl;
		for (int i = 0; i<allTables[j]->number_of_columns; i++)
		{
			cout << "---------";
		}
		cout << endl;
	for (int i = 0; i<allTables[j]->index; i++){
		for (int k = 0; k < allTables[j]->number_of_columns; k++){
				cout << allTables[j]->tableData[i]->data[k] << "\t";
		}
		cout << endl;
	}
	cout << endl;
	
}

void compute_avg(){
	float temp = 0.0; 
	char* b = NULL;
	for (int i = 0; i<allTables[0]->index; i++){
		temp = (float)(converttoint(allTables[0]->tableData[i]->data[2]) + converttoint(allTables[0]->tableData[i]->data[3]) + converttoint(allTables[0]->tableData[i]->data[4]) + converttoint(allTables[0]->tableData[i]->data[5])) / 4;		
		b = ftoa(temp, 3);
		record* t = (record*)malloc(sizeof(record));
		for (int j = 0; j < allTables[0]->number_of_columns; i++){
			t->data[j] = allTables[0]->tableData[i]->data[j];
		}
		t->data[6] = b;
		allTables[0]->tableData[i] = t;

	}
}
void compute_cgpa(){
//	for (int i = 0; i<marks->mark_index; i++){
//		marks->studentmarkarray[i]->cgpa = (float)(returngrade(marks->studentmarkarray[i]->m1) + returngrade(marks->studentmarkarray[i]->m2) + returngrade(marks->studentmarkarray[i]->m3) + returngrade(marks->studentmarkarray[i]->m4)) / 4;
//	}
}


void dojoin(){
	int found = 0;
	int j = 0;
	for (int i = 0; i<allTables[0]->index; i++){
		found = 0;
		j = 0;
		for (j = 0; j<allTables[1]->index; j++){
			if (strcmp(allTables[0]->tableData[i]->data[0], allTables[1]->tableData[j]->data[0])==0){
				found = 1;
				break;
			}
		}

		if (found == 1){
			cout << allTables[0]->tableData[i]->data[0] << "\t" << allTables[0]->tableData[i]->data[1] << "\t" << allTables[1]->tableData[j]->data[1] << "\t" << allTables[1]->tableData[j]->data[2] << endl;
			continue;
		}if (found == 0){
			cout << allTables[0]->tableData[i]->data[0] << "\t" << allTables[0]->tableData[i]->data[1] << "\t" << "N/A" << "\t" << "N/A" << endl;
		}
	}
}

int index_of(int k,char* col){
	//cout << "inside index of" << endl;
	for (int i = 0; i < allTables[k]->number_of_columns; i++){
		if (strcmp(col, allTables[k]->column_names[i]) == 0){
		//	cout << "returning index " << i << endl;
			return i;
		}
	}
	return -1;
}

void load_project_cols(char* col){
	put(hashtable, "select", col);
}


void if_all_zero_operate(int table_code){
	for (int i = 0; i < 8; i++){
		if (get(hashtable,"where",allTables[table_code]->column_names[i])){
			return;
		}
	}
	put(hashtable, "where", "*");
	return;
}
 
void show_heading(int j){
		int count = 0;
		//cout << "inside do_rpojection" << endl;
		for (int i = 0; i < allTables[j]->number_of_columns; i++){
			if (get(hashtable, "select", allTables[j]->column_names[i]) || get(hashtable, "select", "*")){
				cout <<"\t"<< allTables[j]->column_names[i];
				count++;
		}
		}
		cout << endl<<"\t";
for (int i = 0; i < count; i++){
	cout << "--------";
}
cout << endl;
}

void do_projection_mark(int table_code,record* row){
	for (int j = 0; j < allTables[table_code]->number_of_columns; j++){
		if (get(hashtable,"select",allTables[table_code]->column_names[j]) || get(hashtable,"select","*")){
			cout << "\t" << row->data[j];
			}
		}
	cout << endl;
	
}

bool validate(int table_code,record* row){
	if (get(hashtable, "where", "*")){
		return true;
	}

	for (int i = 0; i < allTables[table_code]->number_of_columns; i++){
		if (get(hashtable,"where",allTables[table_code]->column_names[i])){
			if (strcmp(allTables[table_code]->query_operation, "GT") == 0 || strcmp(allTables[table_code]->query_operation, "gt") == 0 || strcmp(allTables[table_code]->query_operation, ">") == 0){
				if (!(converttoint(row->data[i]) > converttoint(allTables[table_code]->value))){
					return false;
				}
			}
			if (strcmp(allTables[table_code]->query_operation, "LT") == 0 || strcmp(allTables[table_code]->query_operation, "lt") == 0 || strcmp(allTables[table_code]->query_operation, "<") == 0){
				if (!(converttoint(row->data[i]) < converttoint(allTables[table_code]->value))){
					return false;
				}
			}
			if (strcmp(allTables[table_code]->query_operation, "EQ") == 0 || strcmp(allTables[table_code]->query_operation, "eq") == 0 || strcmp(allTables[table_code]->query_operation, "=") == 0){
				if (!(converttoint(row->data[i]) == converttoint(allTables[table_code]->value)) &&  (strcmp(allTables[table_code]->value,row->data[i])!=0) ){
					return false;
				}
			}
			if (strcmp(allTables[table_code]->query_operation, "LE") == 0 || strcmp(allTables[table_code]->query_operation, "le") == 0 || strcmp(allTables[table_code]->query_operation, "<=") == 0){
				if (!(converttoint(row->data[i]) <= converttoint(allTables[table_code]->value))){
					return false;
				}
			}
			if (strcmp(allTables[table_code]->query_operation, "GE") == 0 || strcmp(allTables[table_code]->query_operation, "ge") == 0 || strcmp(allTables[table_code]->query_operation, ">=") == 0){
				if (!(converttoint(row->data[i]) >= converttoint(allTables[table_code]->value))){
					return false;
				}
			}

			//code for starts with contains equals etc
			if (strcmp(allTables[table_code]->query_operation, "contains") == 0){
				if (strstr(row->data[i], allTables[table_code]->value) == NULL){
					return false;
				}
			}
			if (strcmp(allTables[table_code]->query_operation, "startswith") == 0){
				char* temp = strstr(row->data[i], allTables[table_code]->value);
				if (temp == NULL){
					return false;
				}
				int position = temp - row->data[i];
				if (position != 0){
					return false;
				}
			}

		}
	}
	return true;
}

void send_row_to_project(int table_code){
	if_all_zero_operate(table_code);
	for (int i = 0; i < allTables[table_code]->index; i++){
		if (validate(table_code,allTables[table_code]->tableData[i])){
			do_projection_mark(table_code,allTables[table_code]->tableData[i]);
		}
	}
}

int load_operation_cols(int i,char* col){
	//cout << "operation on: " << col << endl;
	int req_index = index_of(i,col);
	if (req_index == -1){
		cout << "Error in where clause" << endl;
		return -1;
	}
	put(hashtable, "where", col);
}

int load_from(char* tablename){
	int count = 0;
	int tablecode = -1;
	for (int i = 0; i < table_count-1; i++){
		if (get(hashtable, "from", allTables[i]->tableName)){
			count++;
		} 
		else if (strcmp(tablename, allTables[i]->tableName) == 0){
				put(hashtable, "from", tablename);
				count++;
				tablecode = i;
			}
		
	}
	if (count == 1){
		return tablecode;
	}
	else if(count == 2){
		return 2;
	}
	else{
		return -1;
	}
}


void query_engine(char* query){
	char* temp;
	char* select = "select";
	char* from = "from";
	char* wher = "where";
	int where_count = 0;
	int table_code = 0;
	temp = strtok(query, " ,.");
	if (strcmp(temp, select) != 0){
		cout << "Error in syntax. Select keyword not written properly" << endl;
		return;
	}
	if (strcmp(temp, select) == 0){
		temp = strtok(NULL, " ,.\n");
		while (temp != NULL && (strcmp(temp, from) != 0)){
			load_project_cols(temp);
			temp = strtok(NULL, " ,.\n");
			}
	}
	if (temp==NULL || (strcmp(temp, from) != 0)){
		cout << "Error in syntax. From keyword not written properly " << endl;
		return;
	}
	if (strcmp(temp, from) == 0){	
		temp = strtok(NULL, " ,;.\n");
		while (temp != NULL && strcmp(temp, wher) != 0){
			table_code = load_from(temp);
			if (table_code == -1){
				cout << "Error in from clause." << endl;
				return;
			}if (table_code == 2){
				cout << "Queries on joined table not yet implemented" << endl;
				return;
				
			}
			temp = strtok(NULL, " ;,.\n");
		}
	}
	if (temp != NULL && strcmp(temp, wher) == 0){
		temp = strtok(NULL, " ,.\n");
		int i = load_operation_cols(table_code,temp);
		if (i == -1){
			return;
		}
		temp = strtok(NULL, " ,.\n");
		allTables[table_code]->query_operation = temp;
		temp = strtok(NULL, " ,\"\';.\n");
		if (temp == NULL){
			cout << "Error in where clause: Give space between operator and values." << endl;
			return;
		}
		allTables[table_code]->value = temp;
	}
	cout << endl;
	show_heading(table_code);
	send_row_to_project(table_code);
	cout << endl;
}



int main(){
	loadGlobalTables();
	char query[30];
	bool check = true;
	int choice = 0;
	char tempfilename[100];
	loadmarksarray(0,"marks1.txt");
	loadmarksarray(1, "info1.txt");
	

	while (check){
		fflush(stdout);
		fflush(stdin);
		cout << "The available table names are \"marks\" and \"infos\" " << endl;
		cout << "Select 8 to enter query" << endl;
		cout << ">> 1: load  | 2: display all | 3: Ten entries | 4: avg | 5: cgpa | 6: save | 7: Join | 8: Query |9: exit" << endl;
		cout << ">> ";
		cin >> choice;
		if (choice == 1){
			cout << ">> 1: Marks | 2: Info " << endl << ">> ";

			int filechoice = 0;
			cin >> filechoice;
			cout << "Enter filename: ";
			if (filechoice == 1){
				cin >> tempfilename;
				loadmarksarray(0,tempfilename);
			}
			else if (filechoice == 2){
				cin >> tempfilename;
				loadmarksarray(1, tempfilename);
				
			}
			//mark_array_checkpoint = 0;
			//info_array_checkpoint = 0;
		}
		else if (choice == 2){
			cout << ">> 1: Marks | 2: Info " << endl << ">> ";
			int displaychoice = 0;
			cin >> displaychoice;
			if (displaychoice == 1){
				showmarkarray(0);
			}if (displaychoice == 2){
				showmarkarray(1);
			}

		}
		else if (choice == 3){
			cout << ">> 1: Marks | 2: Info " << endl << ">> ";
			int threechoice = 0;
			cin >> threechoice;
			if (threechoice == 1){
			//	show_ten_mark(mark_array_checkpoint);
			//	mark_array_checkpoint = mark_array_checkpoint + 10;
			}if (threechoice == 2){
				//show_ten_info(info_array_checkpoint);
				//info_array_checkpoint = info_array_checkpoint + 10;
			}
		}
		else if (choice == 4){
			compute_avg();
		}
		else if (choice == 5){
			compute_cgpa();
		}
		else if (choice == 6){
			cout << ">> 1: Marks | 2: Info " << endl << ">> ";
			int savechoice = 0;
			cin >> savechoice;
			if (savechoice == 1){
				savetofilemark();
			}if (savechoice == 2){
				savetofileinfo();
			}
		}
		else if (choice == 9){
			check = false;
		}
		else if (choice == 7){
			dojoin();

		}
		else if (choice == 8){
			fflush(stdout);
			cout << ">> Enter query: ";
			fflush(stdin);
			fgets(query, 100, stdin);
			query_engine(query);
			clearHashtable(hashtable);
		}
		else{
			fflush(stdout);
			system("CLS");
		}
		fflush(stdout);
	}

	return 0;
}