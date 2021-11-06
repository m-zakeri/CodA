/* C Program to sort an array in ascending order using Insertion Sort */
#include <stdio.h>

//in the name of allah
#include <fstream>
std::ofstream logFile("log_file.txt");

int main()
{
logFile << "1 1" << std::endl;

    int n, i, j, temp;
    int arr[64];
 
    printf("Enter number of elements\n");
    scanf("%d", &n);
 
    printf("Enter %d integers\n", n);
    for (i = 0; logFile << "1 2" << std::endl && (i < n); i++)
    {
logFile << "1 3" << std::endl;

        scanf("%d", &arr[i]);
    }
logFile << "1 4" << std::endl;

    for (i = 1 ; logFile << "1 5" << std::endl && (i <= n - 1); i++)
    {
logFile << "1 6" << std::endl;

	    j = i;
            while ( logFile << "1 7" << std::endl && (j > 0 && arr[j-1] > arr[j]))
            {
logFile << "1 8" << std::endl;
	        
                temp     = arr[j];
                arr[j]   = arr[j-1];
                arr[j-1] = temp;
                j--;
            }
logFile << "1 9" << std::endl;

    }
logFile << "1 10" << std::endl;

    printf("Sorted list in ascending order:\n");
    for (i = 0; logFile << "1 11" << std::endl && (i <= n - 1); i++)
    {
logFile << "1 12" << std::endl;

        printf("%d\n", arr[i]);
    }
logFile << "1 13" << std::endl;

    return 0;
}