#include "TimSort.h"

TimSortClass::TimSort::TimSort(long long &array, const int lengthArray) {
    sortArray = &array;
    lengthSortArray = lengthArray;
}

// берем 6 старших бит lengthArray и отбрасываем их
// смотрим на оставшиеся биты
// если среди них есть хотя бы один "0", то flag = 1
int TimSortClass::TimSort::getMinrun(int lengthArray) {
    int flag = 0;
    while (lengthArray >= 64) {
        // до тех пор, пока длина больше 2^6 (1000000)
        flag |= (lengthArray & 1); // flag побитовоеИЛИ= (длина побитовоеИ 1)
        lengthArray >>= 1; // побитовый сдвиг вправо (по сути это просто lengthArray / 2)
    }
    return lengthArray + flag; // 6 старших бит lengthArray +
}

// Пример работы:
// lengthArray = 300 = 100101100
// 1) lengthArray >= 64 (т.к. 100101100 >= 001000000)
// 2)   100101100
//      000000001
// res: 000000000 - это (lengthArray & 1)
//      000000000
//      000000000
// res: 000000000 - это записалось в flag
// 3) был lengthArray =  100101100 (300)
//    стал lengthArray = 010010110 (150)
//
// и по новой
//
// 1) lengthArray >= 64 (т.к. 010010110 >= 001000000)
// 2)   010010110
//      000000001
// res: 000000000 - это (lengthArray & 1)
//      000000000
//      000000000
// res: 000000000 - это записалось в flag
// 3) был lengthArray =  010010110 (150)
//    стал lengthArray = 001001011 (75)
//
// 1) lengthArray >= 64 (т.к. 001001011 >= 001000000)
// 2)   001001011
//      000000001
// res: 000000001 - это (lengthArray & 1)
//      000000001
//      000000000
// res: 000000001 - это записалось в flag
// 3) был lengthArray =  001001011 (75)
//    стал lengthArray = 000100101 (37)
// 37 < 64, цикл закончен
// return 37 + 1 = 38

void TimSortClass::TimSort::insertionSortRun(const int start, const int end) const {
    for (int i = start + 1; i < end; ++i) {
        const long long current = sortArray[i];
        int j = i - 1;
        while ((j >= start) and (current < sortArray[j])) {
            std::swap(sortArray[j], sortArray[j + 1]);
            --j;
        }
    }
}

void TimSortClass::TimSort::mergeSortRun(const int firstRunStart, const int firstRunLength, const int secondRunStart, const int secondRunLength) const {
    long long *tempArray =  new long long[firstRunLength];

    // memcpy(tempArray, &sortArray[firstRunStart], sizeof(int)*(firstRunLength)); // копирование данных из sortArray в tempArray (учитывая размер)
    for (int i = 0; i < firstRunLength; ++i) {
        tempArray[i] = sortArray[firstRunStart + i];
    }

    int firstIndex = 0;
    int secondIndex = secondRunStart;
    int i = firstRunStart;

    while (i < secondRunStart + secondRunLength - 1) {
        if (sortArray[secondIndex] > tempArray[firstIndex]) {
            sortArray[i] = tempArray[firstIndex];
            firstIndex += 1;
            firstIndex = std::min(firstIndex, firstRunLength);
        } else if (sortArray[secondIndex] <= tempArray[firstIndex]) {
            sortArray[i] = sortArray[secondIndex];
            secondIndex += 1;
            secondIndex = std::min(secondIndex, secondRunStart+secondRunLength);
        }
        if (secondIndex == secondRunStart + secondRunLength) {
            if (firstIndex != firstRunLength) {
                // memcpy(&sortArray[i + 1], &tempArray[firstIndex], sizeof(int)*(firstRunLength - firstIndex));
                for (int j = 0; j < (firstRunLength - firstIndex); ++j) {
                    sortArray[i + 1 + j] = tempArray[firstIndex + j];
                }
                i = secondRunStart + secondRunLength;
            }
        }
        if (firstIndex == firstRunLength) {
            i = secondRunStart + secondRunLength;
        }
        i += 1;
    }
    delete [] tempArray;
}

std::stack<TimSortClass::TimSort::RangeRun> TimSortClass::TimSort::splitToRuns() const {
    std::stack<RangeRun> stackRuns;
    int currentIndex = 0;
    while (currentIndex < lengthSortArray - 1) {
        // length - 1 - т.к. счёт с "0" и строгое сравнение
        int currRunIndex = currentIndex;
        int nextRunIndex = currRunIndex + 1;

        if (sortArray[currRunIndex] > sortArray[nextRunIndex]) {
            std::swap(sortArray[currRunIndex], sortArray[nextRunIndex]);
        }

        bool moveNextElement = true;
        while (moveNextElement) {
            if (sortArray[currRunIndex] > sortArray[nextRunIndex]) {
                moveNextElement = false;
            }
            if (!(moveNextElement) and (currRunIndex - currentIndex < minrun)) {
                // если не хватает до конца run (добираем элементы)
                moveNextElement = true;
            }
            if (currRunIndex == lengthSortArray - 1) {
                // если дошли до конца массива
                moveNextElement = false;
            }
            if (moveNextElement) {
                ++currRunIndex;
                ++nextRunIndex;
            }
        }
        insertionSortRun(currentIndex, currRunIndex + 1);

        RangeRun run{};
        run.start = currentIndex;
        run.length = currRunIndex - currentIndex;

        stackRuns.push(run);

        currentIndex = currRunIndex;
    }
    return stackRuns;
}

void TimSortClass::TimSort::mergeRuns(std::stack<RangeRun> stackRuns) const {
    while (stackRuns.size() > 1) {
        RangeRun firstRun = stackRuns.top();
        stackRuns.pop();
        RangeRun secondRun = stackRuns.top();
        stackRuns.pop();
        if (firstRun.start > secondRun.start) {
            std::swap(firstRun.start, secondRun.start);
            std::swap(firstRun.length, secondRun.length);
        }
        if (secondRun.start != firstRun.start + firstRun.length) {
            stackRuns.push(secondRun);
            stackRuns.push(firstRun);
            continue;
        }
        mergeSortRun(firstRun.start, firstRun.length, secondRun.start, secondRun.length);
        firstRun.length = firstRun.length + secondRun.length;
        stackRuns.push(firstRun);
    }
}

long long *TimSortClass::TimSort::getSortedArray() {
    minrun = getMinrun(lengthSortArray);
    mergeRuns(splitToRuns());
    return sortArray;
}