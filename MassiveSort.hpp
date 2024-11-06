namespace MassiveSort {
enum class MenuOption : int {
    Static = 1,
    Dynamic,
};

enum class MethodOption : int {
    minMax = 1,
    bubble,
};

void TaskChoose();
void StartCyle();

void StaticApp();
void DynamicApp();

void BubbleSort(int* massive);
void MinMaxSort(int* massive);
}  // namespace MassiveSort
