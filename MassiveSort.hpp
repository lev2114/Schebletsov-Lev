#ifndef MASSIVESORT
#define MASSIVESORT

namespace MassiveSort {
enum class MenuOption : int {
    Static = 1,
    Dynamic,
};

struct SortData {
    int swaps = 0;
    int comparisons = 0;
};

void TaskChoose();
void MainLoop();

void StaticApp();
void DynamicApp();

[[nodiscard]] SortData BubbleSort(int* array, int arrLen, bool ascending);
[[nodiscard]] SortData SelectionSort(int* array, int arrLen, bool ascending);

}  // namespace MassiveSort
#endif
