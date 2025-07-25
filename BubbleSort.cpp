#include<iostream>
#include<stdlib.h>
#include<omp.h>

using namespace std;

void bubble_sequential(int *, int);
void bubble_parallel(int *, int);
void swap(int &, int &);

void bubble_sequential(int *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
            }
        }
    }
}

void bubble_parallel(int *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        int first = i % 2;
        #pragma omp parallel for shared(a, first)
        for (int j = first; j < n - 1; j += 2)
        {
            if (a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
            }
        }
    }
}

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int main()
{
    int *a, n, choice;

    cout << "\nChoose the sorting method: ";
    cout << "\n1. Sequential Bubble Sort";
    cout << "\n2. Parallel Bubble Sort";
    cout << "\nEnter your choice: ";
    cin >> choice;

    if (choice == 1 || choice == 2) {
        cout << "\nEnter total number of elements: ";
        cin >> n;

        a = new int[n];

        cout << "\nEnter elements: ";
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }

        double start_time = omp_get_wtime(); // Start timer

        if (choice == 1)
            bubble_sequential(a, n);
        else
            bubble_parallel(a, n);

        double end_time = omp_get_wtime(); // End timer

        cout << "\nSorted array: ";
        for (int i = 0; i < n; i++)
        {
            cout << a[i] << " ";
        }

        // Print the execution time in milliseconds
        cout << "\n\nExecution Time: " << (end_time - start_time) * 1000 << " milliseconds" << endl;

        delete[] a;
    } else {
        cout << "Invalid choice! Exiting program..." << endl;
    }

    return 0;
}
