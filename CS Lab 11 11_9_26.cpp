#include <iostream>
#include <fstream>
#include <string>
#include <chrono> // Optional: For tracking execution time

using namespace std;

// Function Prototypes
bool readSongs(string fileName, string songs[][2], int& count);
void printSongs(const string songs[][2], int count);
int linearSearchForSong(const string songs[][2], int size, string grail, int& comparisons);
void swapLines(string line1[], string line2[]); // Named swapLines to avoid conflicts with std::swap
void selectionSort(string songs[][2], int size);
void bubbleSort(string songs[][2], int size);
int binarySearchForSong(const string songs[][2], int size, string grail, int& comparisons);

int main() {
    // Array size matching Phase 1 requirements
    const int MAX_SONGS = 120450;
    static string songs[MAX_SONGS][2]; // 'static' prevents stack overflow for large local arrays
    int songCount = 0;

    string fileName = "spotify_songs_tab_artists.dat";

    // Phase 1: Read the file
    cout << "Reading file..." << endl;
    if (!readSongs(fileName, songs, songCount)) {
        cout << "Error: Could not open or read " << fileName << endl;
        return 1;
    }
    cout << "Successfully loaded " << songCount << " songs." << endl;

    // Set up search target (the "grail")
    string grail = "Your Target Song Title Here";
    int linearComparisons = 0;
    int binaryComparisons = 0;

    // Phase 2: Linear Search (Before Sorting)
    cout << "\n--- Phase 2: Linear Search ---" << endl;
    int linearIndex = linearSearchForSong(songs, songCount, grail, linearComparisons);
    if (linearIndex != -1) {
        cout << "Found \"" << grail << "\" at index " << linearIndex
            << " by " << songs[linearIndex][1] << endl;
    }
    else {
        cout << "\"" << grail << "\" not found." << endl;
    }
    cout << "Linear search comparisons: " << linearComparisons << endl;

    // Phase 3 & 4: Sorting 
    // WARNING: Sorting 120k elements using O(N^2) algorithms like Bubble Sort 
    // or Selection Sort takes a highly intensive amount of processing time.
    // Uncomment the one you want to test.

    /*
    cout << "\n--- Phase 3: Selection Sort ---" << endl;
    selectionSort(songs, songCount);
    cout << "First 100 sorted songs:" << endl;
    printSongs(songs, 100);
    */

    /*
    cout << "\n--- Phase 4: Bubble Sort ---" << endl;
    bubbleSort(songs, songCount);
    cout << "First 100 sorted songs:" << endl;
    printSongs(songs, 100);
    */

    // Phase 5: Binary Search (Requires sorted list!)
    // Note: To properly test this, uncomment one of the sorting methods above.
    cout << "\n--- Phase 5: Binary Search ---" << endl;
    int binaryIndex = binarySearchForSong(songs, songCount, grail, binaryComparisons);
    if (binaryIndex != -1) {
        cout << "Found \"" << grail << "\" at index " << binaryIndex
            << " by " << songs[binaryIndex][1] << endl;
    }
    else {
        cout << "\"" << grail << "\" not found." << endl;
    }
    cout << "Binary search comparisons: " << binaryComparisons << endl;

    return 0;
}

// Phase 1: Read songs from tab-delimited file
bool readSongs(string fileName, string songs[][2], int& count) {
    ifstream infile(fileName);
    if (!infile.is_open()) {
        return false;
    }

    string header;
    getline(infile, header); // Skip the title/header row

    count = 0;
    string songTitle, artistName;

    // Read song title up to the tab character, then read the rest of the line as the artist
    while (getline(infile, songTitle, '\t') && getline(infile, artistName)) {
        songs[count][0] = songTitle;
        songs[count][1] = artistName;
        count++;
    }

    infile.close();
    return true;
}

// Phase 1: Print subset of songs
void printSongs(const string songs[][2], int count) {
    for (int i = 0; i < count; i++) {
        cout << i << ". " << songs[i][0] << " - " << songs[i][1] << endl;
    }
}

// Phase 2: Linear Search
int linearSearchForSong(const string songs[][2], int size, string grail, int& comparisons) {
    comparisons = 0;
    for (int i = 0; i < size; i++) {
        comparisons++;
        if (songs[i][0] == grail) {
            return i;
        }
    }
    return -1;
}

// Phase 3: Swap utility function for arrays
void swapLines(string line1[], string line2[]) {
    string tempSong = line1[0];
    string tempArtist = line1[1];

    line1[0] = line2[0];
    line1[1] = line2[1];

    line2[0] = tempSong;
    line2[1] = tempArtist;
}

// Phase 3: Selection Sort
void selectionSort(string songs[][2], int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            // Compare song titles alphabetically
            if (songs[j][0] < songs[minIndex][0]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swapLines(songs[i], songs[minIndex]);
        }
    }
}

// Phase 4: Bubble Sort
void bubbleSort(string songs[][2], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            // Swap if elements are out of order
            if (songs[j][0] > songs[j + 1][0]) {
                swapLines(songs[j], songs[j + 1]);
            }
        }
    }
}

// Phase 5: Binary Search
int binarySearchForSong(const string songs[][2], int size, string grail, int& comparisons) {
    comparisons = 0;
    int beginning = 0;
    int end = size - 1;

    while (beginning <= end) {
        int middle = beginning + (end - beginning) / 2;
        comparisons++;

        if (songs[middle][0] == grail) {
            return middle; // Found the grail
        }
        else if (songs[middle][0] < grail) {
            beginning = middle + 1; // Discard left half
        }
        else {
            end = middle - 1; // Discard right half
        }
    }
    return -1; // Element not found
}