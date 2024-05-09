#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define CLEAR_SCREEN "\x1B[2J"
#define ANSI_COLOR_BLUE "\033[34m"
void drawboxes(int* rand_arr, int* a, int loc);
void check(int* count, int* arr);
void repl(int* arr, int a, int b);
int gen(int arr[], int i);
void main()
{
	time_t	t;
	int arr[16] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };
	int rand_arr[16];
	int count[16];
	srand((unsigned)time(&t));
	//generating random integers
	for (int i = 0; i < 15; i++)
	{
		count[i] = i;
		rand_arr[i] = gen(arr, i);
	}
	count[15] = 15;
	rand_arr[15] = 16;
	int cpy_loc = count[15];
	drawboxes(rand_arr, count, cpy_loc);
	check(count, arr);
	// waiting for arrow key
	while (1)
	{
		if (_kbhit())
		{
			int key = _getch();

			// Check for arrow keys
			if (key == 0xE0)
			{
				key = _getch(); // Read the extended key code

				// Handle arrow keys
				switch (key)
				{
				case 72: // Up arrow key
					if (cpy_loc >= 4)
					{
						repl(rand_arr, cpy_loc - 4, cpy_loc);
						cpy_loc -= 4;
					}
					break;
				case 80:// Down arrow key
					if (cpy_loc <= 11)
					{
						repl(rand_arr, cpy_loc + 4, cpy_loc);
						cpy_loc += 4;
					}
					break;
				case 75://Left arrow key
					if (cpy_loc % 4 != 0 || cpy_loc == -1)
					{
						repl(rand_arr, cpy_loc - 1, cpy_loc);
						cpy_loc--;
					}
					break;
				case 77://Right arrow key
					if (cpy_loc % 4 != 3)
					{
						repl(rand_arr, cpy_loc, cpy_loc + 1);
						cpy_loc++;
					}
					break;
				}
			}

			// Clear the screen 
			system("cls"); // Windows-specific, for Unix-like systems, use "clear"
			drawboxes(rand_arr, count, cpy_loc);
		}
	}
}
void check(int* count, int* arr)
{
	bool checker = false;
	for (int i = 0; i < 16; i++)
	{
		if (count[i] == i)
			checker = true;
		else
			checker = false;
	}
	if (checker == true)
	{
		system("cls");
		printf(ANSI_COLOR_RED"Congratulations!\n\n"ANSI_COLOR_RESET);

		printf(ANSI_COLOR_YELLOW"  ********\n");
		printf(" *        *\n");
		printf("*  WINNER  *\n");
		printf(" *        *\n");
		printf("  ********\n"ANSI_COLOR_RESET);
	}
}
int gen(int arr[], int i)
{
	int r = rand() % (15 - i);
	int ret = arr[r];
	if (r < 15 - i)
		repl(arr, r, 15 - i - 1);
	return ret;
}
void drawboxes(int* rand_arr, int* a, int loc)
{
	int cnt = 0;
	for (int k = 0; k < 4; k++)
	{
		//drawing top of pattern
		for (int i = 0; i < 25; i++)
		{
			if (i % 2 == 0)
				printf(ANSI_COLOR_RED "*"ANSI_COLOR_RESET);
			else
				printf(" ");
		}
		printf("\n");
		for (int i = 0; i < 13; i++)
		{
			if ((i % 3 == 0))
			{
				printf(ANSI_COLOR_RED"*"ANSI_COLOR_RESET);
			}
			else if (i % 3 == 1)
			{
				if (cnt == loc)
				{
					//printing current location
					a[cnt] = rand_arr[cnt];
					printf(ANSI_COLOR_YELLOW"x "ANSI_COLOR_RESET);
					cnt++;
				}
				else
				{
					//printing numbers
					if (rand_arr[cnt] > 9)
					{
						a[cnt] = rand_arr[cnt];
						printf(ANSI_COLOR_GREEN"%d"ANSI_COLOR_RESET, rand_arr[cnt]);
					}
					else
					{
						a[cnt] = rand_arr[cnt];
						printf(ANSI_COLOR_GREEN"%d "ANSI_COLOR_RESET, rand_arr[cnt]);
					}
					cnt++;
				}
			}
			printf(" ");
		}
		printf("\n");
	}
	//bottom of pattern
	for (int i = 0; i < 25; i++)
	{
		if (i % 2 == 0)
			printf(ANSI_COLOR_RED "*"ANSI_COLOR_RESET);
		else
			printf(" ");
	}
	printf(ANSI_COLOR_BLUE"\nYou know this old game 'x' is your position\nyou can change positions by"
		"pressing arrow keys in your keyboard\nyou have to put number orderly from 1 to 15 "
		"in the end\nyour position should be in the right bottom corner GOOD LUCK!!!\n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_YELLOW"   *****   \n");
	printf(" *       * \n");
	printf("*  O   O  *\n");
	printf("*    ∆    *\n");
	printf(" * \\___/ * \n");
	printf("   *****   \n"ANSI_COLOR_RESET);
}
void repl(int* arr, int a, int b)
{
	int temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}