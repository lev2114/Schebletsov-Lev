#ifndef MASSIVESORT
#define MASSIVESORT

namespace MassiveSort {
enum class MenuOption : int {
    Static = 1,
    Dynamic,
};

struct SortData{
    int replacements = 0;
    int comparasons = 0;
};

void TaskChoose();
void StartCycle();

void StaticApp();
void DynamicApp();

void StaticSortsApp(int* massive, int masLen);
void DynamicSortsApp(int* massive, int masLen);

[[nodiscard]] SortData BubbleSort(int* massive, int masLen, char where);
[[nodiscard]] SortData MinMaxSort(int* massive, int masLen, char where);

}  // namespace MassiveSort
#endif
