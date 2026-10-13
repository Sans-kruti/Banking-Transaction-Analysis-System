
#include <stdio.h>
#include <string.h>

#define MAX 1000

typedef struct {
    int transactionID;
    int customerID;
    char date[11];
    char type[10];
    double amount;
} Transaction;

Transaction transactions[MAX];
Transaction temp[MAX];

int n;
int sortField;
long long comparisons;
long long recursionCalls;

/* Compare transactions using the selected field */
int compareTransactions(Transaction a, Transaction b) {
    comparisons++;

    if (sortField == 1) {
        return (a.transactionID > b.transactionID) -
               (a.transactionID < b.transactionID);
    } else if (sortField == 2) {
        return (a.customerID > b.customerID) -
               (a.customerID < b.customerID);
    } else {
        return (a.amount > b.amount) -
               (a.amount < b.amount);
    }
}

/* Display all transactions */
void displayTransactions(Transaction arr[], int size) {
    printf("\n%-12s %-12s %-12s %-10s %-12s\n",
           "Trans. ID", "Customer ID", "Date", "Type", "Amount");
    printf("--------------------------------------------------------------\n");

    for (int i = 0; i < size; i++) {
        printf("%-12d %-12d %-12s %-10s Rs. %-9.2f\n",
               arr[i].transactionID,
               arr[i].customerID,
               arr[i].date,
               arr[i].type,
               arr[i].amount);
    }
}

/* MERGE SORT */
void merge(Transaction arr[], int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;

    while (i <= mid && j <= right) {
        if (compareTransactions(arr[i], arr[j]) <= 0) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid)
        temp[k++] = arr[i++];

    while (j <= right)
        temp[k++] = arr[j++];

    for (i = left; i <= right; i++)
        arr[i] = temp[i];
}

void mergeSort(Transaction arr[], int left, int right) {
    recursionCalls++;

    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

/* QUICK SORT */
int partition(Transaction arr[], int low, int high) {
    Transaction pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (compareTransactions(arr[j], pivot) <= 0) {
            i++;

            Transaction t = arr[i];
            arr[i] = arr[j];
            arr[j] = t;
        }
    }


    Transaction t = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = t;

    return i + 1;
}

void quickSort(Transaction arr[], int low, int high) {
    recursionCalls++;

    if (low < high) {
        int pivotIndex = partition(arr, low, high);

        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

/* BINARY SEARCH: transaction ID */
int binarySearch(Transaction arr[], int size, int key,
                 long long *searchComparisons) {
    int low = 0, high = size - 1;

    *searchComparisons = 0;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        (*searchComparisons)++;

        if (arr[mid].transactionID == key)
            return mid;

        if (arr[mid].transactionID < key)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

/* Find highest and lowest transaction amounts */
void findHighestLowest(Transaction arr[], int size) {
    int highest = 0, lowest = 0;

    for (int i = 1; i < size; i++) {
        if (arr[i].amount > arr[highest].amount)
            highest = i;

        if (arr[i].amount < arr[lowest].amount)
            lowest = i;
    }

    printf("\nHighest-value transaction:\n");
    printf("Transaction ID: %d, Amount: Rs. %.2f\n",
           arr[highest].transactionID, arr[highest].amount);

    printf("\nLowest-value transaction:\n");
    printf("Transaction ID: %d, Amount: Rs. %.2f\n",
           arr[lowest].transactionID, arr[lowest].amount);
}

int main(void) {
    int choice, key, result;
    long long searchComparisons;

    printf("=== BANKING TRANSACTION ANALYSIS SYSTEM ===\n");

    printf("Enter number of transactions (1-%d): ", MAX);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid number of transactions.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("\nEnter details for transaction %d:\n", i + 1);

        printf("Transaction ID (integer): ");
        if (scanf("%d", &transactions[i].transactionID) != 1)
            return 1;

        printf("Customer ID (integer): ");
        if (scanf("%d", &transactions[i].customerID) != 1)
            return 1;

        printf("Date (DD-MM-YYYY): ");
        if (scanf("%10s", transactions[i].date) != 1)
            return 1;

        printf("Type (Credit/Debit): ");
        if (scanf("%9s", transactions[i].type) != 1)
            return 1;

        printf("Amount: ");
        if (scanf("%lf", &transactions[i].amount) != 1 ||
            transactions[i].amount < 0) {
            printf("Invalid amount.\n");
            return 1;
        }
    }

    printf("\n--- Original Transaction Records ---\n");
    displayTransactions(transactions, n);

    do {
        printf("\n========== MENU ==========\n");
        printf("1. Merge Sort\n");
        printf("2. Quick Sort\n");
        printf("3. Binary Search by Transaction ID\n");
        printf("4. Find Highest and Lowest Transaction\n");
        printf("5. Display All Transactions\n");
        printf("0. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1)
            break;

        switch (choice) {
            case 1:
            case 2: {
                printf("\nSort by:\n");
                printf("1. Transaction ID\n");
                printf("2. Customer ID\n");
                printf("3. Transaction Amount\n");
                printf("Enter sort field: ");

                if (scanf("%d", &sortField) != 1)
                    return 1;

                if (sortField < 1 || sortField > 3) {
                    printf("Invalid sort field.\n");
                    break;
                }

                comparisons = 0;
                recursionCalls = 0;

                if (choice == 1) {
                    mergeSort(transactions, 0, n - 1);
                    printf("\nSorted using Merge Sort.\n");
                } else {
                    quickSort(transactions, 0, n - 1);
                    printf("\nSorted using Quick Sort.\n");
                }

                displayTransactions(transactions, n);

                printf("\nPerformance Statistics:\n");
                printf("Element comparisons: %lld\n", comparisons);
                printf("Recursive function calls: %lld\n",
                       recursionCalls);
                break;
            }

            case 3:
                /*
                 * Binary search requires records sorted by
                 * transaction ID.
                 */
                sortField = 1;
                comparisons = 0;
                recursionCalls = 0;
                mergeSort(transactions, 0, n - 1);

                printf("Enter Transaction ID to search: ");
                if (scanf("%d", &key) != 1)
                    return 1;

                result = binarySearch(transactions, n, key,
                                      &searchComparisons);

                if (result != -1) {
                    printf("\nTransaction Found!\n");
                    displayTransactions(&transactions[result], 1);
                } else {
                    printf("\nTransaction ID %d not found.\n", key);
                }

                printf("Binary search comparisons: %lld\n",
                       searchComparisons);
                break;

            case 4:
                findHighestLowest(transactions, n);
                break;

            case 5:
                displayTransactions(transactions, n);
                break;

            case 0:
                printf("Exiting Banking Transaction Analysis System.\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (choice != 0);

    return 0;
}
