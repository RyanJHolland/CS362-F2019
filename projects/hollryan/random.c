// Ryan Holland
// Quiz 3
// 11/10/19

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>



//char *charSet = "[({ ax})]rest";
int charList[14] = { 40, 41, 32, 91, 93, 123, 124, 125, 97, 120, 114, 101, 115, 116 };


// Not having a function like this built in is why I hate using c. It's like coding in the stone age.
// source:https://cboard.cprogramming.com/c-programming/154145-random-number-interval-[0-1].html
int randInRange(int min, int max)
{
	int num;
	num = rand() % (max - min + 1) + min;
	return num;
}


// Generates a random ASCII character that can possibly trigger the fail conditions in testme().
char inputChar()
{
	int num;
	num = randInRange(0, 13); 
	return charList[num];
}


// Generates a random ASCII character array that can possibly trigger the fail conditions in testme().
// We need at least 6 chars in the array since some of the conditions check its index 5.
char arr[4];
char *inputString()
{
	int num, i;
	for (i = 0; i < 5; i++) {
		arr[i] = inputChar();
	}

	return arr;
}


void testme()
{
	int tcCount = 0;
	char *s;
	char c;
	int state = 0;
	while (1)
	{
		tcCount++;
		c = inputChar();
		s = inputString();
		printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);
		
		if (c == '[' && state == 0) state = 1;
		if (c == '(' && state == 1) state = 2;
		if (c == '{' && state == 2) state = 3;
		if (c == ' ' && state == 3) state = 4;
		if (c == 'a' && state == 4) state = 5;
		if (c == 'x' && state == 5) state = 6;
		if (c == '}' && state == 6) state = 7;
		if (c == ')' && state == 7) state = 8;
		if (c == ']' && state == 8) state = 9;
		if (s[0] == 'r' && s[1] == 'e'
			&& s[2] == 's' && s[3] == 'e'
			&& s[4] == 't' && s[5] == '\0'
			&& state == 9)
		{
			printf("error ");
			exit(200);
		}
	}
}


int main(int argc, char *argv[])
{
	srand(time(NULL));
	testme();
	return 0;
}
