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
void StartCyle();

void StaticApp();
void DynamicApp();

void StaticSortsApp(int* massive, int masLen);
void DynamicSortsApp(int* massive, int masLen);

[[nodiscard]] SortData BubbleSort(int* massive, char where);
[[nodiscard]] SortData MinMaxSort(int* massive, char where);

}  // namespace MassiveSort
