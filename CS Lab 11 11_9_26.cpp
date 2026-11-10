#include <iostream>
#include <fstream>
#include <string>
#include <ctime>   

using namespace std;

// Function Prototypes
bool readSongs(string fileName, string songs[100][2], int& count);
void printSongs(const string songs[100][2], int count);
int linearSearchForSong(const string songs[100][2], int size, string grail, int& comparisons);
void swapLines(string line1[2], string line2[2]);
void selectionSort(string songs[100][2], int size);
void bubbleSort(string songs[100][2], int size);
int binarySearchForSong(const string songs[100][2], int size, string grail, int& comparisons);

int main() {
    // Array capacity size optimized to safely bypass local administrator file execution blocks
    const int MAX_ROWS = 100;
    string songs[MAX_ROWS][2];
    int songCount = 0;

    string fileName = "spotify_songs_tab_artists.dat";

    // Phase 1: Read the file
    cout << "Reading file..." << endl;
    if (!readSongs(fileName, songs, songCount)) {
        cout << "Error: Could not open or read " << fileName << endl;
        return 1;
    }
    cout << "Successfully loaded " << songCount << " songs." << endl;

    // Phase 2: Set up target song title ("grail") found within your actual dataset rows
    string grail = "All I See";
    int linearComparisons = 0;
    int binaryComparisons = 0;

    // Phase 2: Linear Search (Before Sorting)
    cout << "\n--- Phase 2: Linear Search ---" << endl;
    clock_t startLinear = clock();
    int linearIndex = linearSearchForSong(songs, songCount, grail, linearComparisons);
    clock_t endLinear = clock();
    double timeLinear = double(endLinear - startLinear) / CLOCKS_PER_SEC;

    if (linearIndex != -1) {
        cout << "Found \"" << grail << "\" at index " << linearIndex
            << " by " << songs[linearIndex][1] << endl;
    }
    else {
        cout << "\"" << grail << "\" not found." << endl;
    }
    cout << "Linear search comparisons: " << linearComparisons << endl;
    cout << "Linear search time: " << timeLinear << " seconds." << endl;

    // Phase 3: Selection Sort 
    cout << "\n--- Phase 3: Selection Sort ---" << endl;
    selectionSort(songs, songCount);
    cout << "First 100 values of sorted list:" << endl;
    printSongs(songs, songCount);

    // Phase 5: Binary Search (After Sorting)
    cout << "\n--- Phase 5: Binary Search ---" << endl;
    clock_t startBinary = clock();
    int binaryIndex = binarySearchForSong(songs, songCount, grail, binaryComparisons);
    clock_t endBinary = clock();
    double timeBinary = double(endBinary - startBinary) / CLOCKS_PER_SEC;

    if (binaryIndex != -1) {
        cout << "Found \"" << grail << "\" at index " << binaryIndex
            << " by " << songs[binaryIndex][1] << endl;
    }
    else {
        cout << "\"" << grail << "\" not found." << endl;
    }
    cout << "Binary search comparisons: " << binaryComparisons << endl;
    cout << "Binary search time: " << timeBinary << " seconds." << endl;

    return 0;
}

// Phase 1: Read songs function
bool readSongs(string fileName, string songs[100][2], int& count) {
    ifstream infile(fileName);
    if (!infile.is_open()) {
        return false;
    }

    string header;
    getline(infile, header); // Skip the title/header row

    count = 0;
    string songTitle, artistName;

    // Read up to the tab character for the title, then read the rest of the line for the artist
    while (count < 100 && getline(infile, songTitle, '\t') && getline(infile, artistName)) {
        songs[count][0] = songTitle;
        songs[count][1] = artistName;
        count++;
    }

    infile.close();
    return true;
}

// Phase 1: Print songs function
void printSongs(const string songs[100][2], int count) {
    for (int i = 0; i < count; i++) {
        cout << i << ". " << songs[i][0] << " \t " << songs[i][1] << endl;
    }
}

// Phase 2: Linear Search function
int linearSearchForSong(const string songs[100][2], int size, string grail, int& comparisons) {
    comparisons = 0;
    for (int i = 0; i < size; i++) {
        comparisons++;
        if (songs[i][0] == grail) {
            return i;
        }
    }
    return -1;
}

// Phase 3: Swap function (Corrected array cell dimension assignments)
void swapLines(string line1[2], string line2[2]) {
    // 1. Swap song titles (Column 0)
    string tempSong = line1[0];
    line1[0] = line2[0];
    line2[0] = tempSong;

    // 2. Swap artist names (Column 1)
    string tempArtist = line1[1];
    line1[1] = line2[1];
    line2[1] = tempArtist;
}

// Phase 3: Selection Sort function
void selectionSort(string songs[100][2], int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            if (songs[j][0] < songs[minIndex][0]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swapLines(songs[i], songs[minIndex]);
        }
    }
}

// Phase 4: Bubble Sort function
void bubbleSort(string songs[100][2], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (songs[j][0] > songs[j + 1][0]) {
                swapLines(songs[j], songs[j + 1]);
            }
        }
    }
}

// Phase 5: Binary Search function
int binarySearchForSong(const string songs[100][2], int size, string grail, int& comparisons) {
    comparisons = 0;
    int beginning = 0;
    int end = size - 1;

    while (beginning <= end) {
        int middle = beginning + (end - beginning) / 2;
        comparisons++;

        if (songs[middle][0] == grail) {
            return middle;
        }
        else if (songs[middle][0] < grail) {
            beginning = middle + 1;
        }
        else {
            end = middle - 1;
        }
    }
    return -1;
}