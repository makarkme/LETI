#pragma once

#include <iostream>
#include <stack>

namespace TimSortClass {
    class TimSort {
    private:
        long long *sortArray{};
        int lengthSortArray{};
        int minrun{};

        struct RangeRun {
            // нужна для хранения каждого run + удобно хранить в стеке
            int start;
            int length;
        };

    public:
        explicit TimSort() = default;

        explicit TimSort(long long &array, int lengthArray);

        static int getMinrun(int lengthArray);

        void insertionSortRun(int start, int end) const;

        void mergeSortRun(int firstRunStart, int firstRunLength, int secondRunStart, int secondRunLength) const;

        [[nodiscard]] std::stack<RangeRun> splitToRuns() const;

        void mergeRuns(std::stack<RangeRun>) const;

        [[nodiscard]] long long *getSortedArray();

        ~TimSort() = default;
    };
}
