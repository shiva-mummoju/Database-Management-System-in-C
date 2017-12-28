#include"Header.h"

int returnint(char ch){
	if (ch == '0'){
		return 0;
	}if (ch == '1'){
		return 1;
	}if (ch == '2'){
		return 2;
	}if (ch == '3'){
		return 3;
	}if (ch == '4'){
		return 4;
	}if (ch == '5'){
		return 5;
	}if (ch == '6'){
		return 6;
	}if (ch == '7'){
		return 7;
	}if (ch == '8'){
		return 8;
	}if (ch == '9'){
		return 9;
	}
}


int returngrade(int n){
	if (n >= 91){
		return 10;
	}
	else if (n >= 81 && n <= 90){
		return 9;
	}
	else if (n >= 71 && n <= 80){
		return 8;
	}
	else if (n >= 61 && n <= 70){
		return 7;
	}
	else if (n >= 51 && n <= 60){
		return 6;
	}
	else if (n >= 41 && n <= 50){
		return 5;
	}
	else if (n >= 31 && n <= 40){
		return 4;
	}
	else if (n >= 21 && n <= 30){
		return 3;
	}
	else if (n >= 11 && n <= 20){
		return 2;
	}
	else if (n >= 1 && n <= 10){
		return 1;
	}
	else{
		return 0;
	}
}

int converttoint(char* str){
	int len = strlen(str);

	int sum = 0;

	for (int i = 0; i<len; i++){
		if (str[i] != '\0' && str[i] != '\n'){

			sum = (sum * 10) + returnint(str[i]);

		}
	}

	return sum;
}

bool is_equal(char* right, char* left){
	int l = strlen(left);
	int r = strlen(right);
	if (l != r){
		return false;
	}
	for (int i = 0; i < l; i++){
		if (right[i] != left[i]){
			return false;
		}
	}
	return true;
}




char inttochar(int n)
{
	if (n == 0){
		return '0';
	}if (n == 1){
		return '1';
	}if (n == 2){
		return '2';
	}if (n == 3){
		return '3';
	}if (n == 4){
		return '4';
	}if (n == 5){
		return '5';
	}if (n == 6){
		return '6';
	}if (n == 7){
		return '7';
	}if (n == 8){
		return '8';
	}if (n == 9){
		return '9';
	}
}
char* converttostring(int num){
	int copy = num;
	int count = 0;
	while (copy>0){
		count++;
		copy = copy / 10;
	}
	copy = num;
	char* str = (char*)malloc(count*sizeof(char) + 1);
	str[count] = '\0';
	for (int i = count - 1; i >= 0; i--){
		str[i] = inttochar(copy % 10);
		copy = copy / 10;
	}
	return str;
}
void reverse(char *str, int len)
{
	int i = 0, j = len - 1, temp;
	while (i<j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++; j--;
	}
}

// Converts a given integer x to string str[].  d is the number
// of digits required in output. If d is more than the number
// of digits in x, then 0s are added at the beginning.
int intToStr(int x, char str[], int d)
{
	int i = 0;
	while (x)
	{
		str[i++] = (x % 10) + '0';
		x = x / 10;
	}

	// If number of digits required is more, then
	// add 0s at the beginning
	while (i < d)
		str[i++] = '0';

	reverse(str, i);
	str[i] = '\0';
	return i;
}

// Converts a floating point number to string.
char* ftoa(float n, int afterpoint)
{
	char* res = (char*)malloc(20 * sizeof(char));
	// Extract integer part
	int ipart = (int)n;

	// Extract floating part
	float fpart = n - (float)ipart;

	// convert integer part to string
	int i = intToStr(ipart, res, 0);

	// check for display option after point
	if (afterpoint != 0)
	{
		res[i] = '.';  // add dot

		// Get the value of fraction part upto given no.
		// of points after dot. The third parameter is needed
		// to handle cases like 233.007
		fpart = fpart * pow(10, afterpoint);

		intToStr((int)fpart, res + i + 1, afterpoint);
	}
	return res;
}