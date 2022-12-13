#include <iostream>

// сортировка слиянием

void merge(int list[], int start, int end, int mid, int doneList[]) // (массив, начальное положение, конечно положение, середина)
{
	int i = start, k = start, j = mid + 1; // i - индекс 1 пути, j - индекс 2 пути
	// k - индекс элемента в результатирующей последовательности 

	while (i <= mid && j <= end) // пока не дошли до конца
	{
		if (list[i] < list[j]) // заполняем след. элемент последовательности меньшим
		{
			doneList[k] = list[i];
			k++;
			i++;
		}
		else 
		{
			doneList[k] = list[j];
			k++;
			j++;
		}
	}

	while (i <= mid) // если 2 путь кончился раньше => переписываем оставшиеся элементы 1 пути
	{
		doneList[k] = list[i];
		k++;
		i++;
	}

	while (j <= end) // если 1 путь кончился раньше => переписываем оставшиеся элементы 2 пути
	{
		doneList[k] = list[j];
		k++;
		j++;
	}

	for (i = start; i < k; i++) // переносим упорядоченную последовательность
	{
		list[i] = doneList[i];
	}
}

void mergeSort(int list[], int start, int end, int donelist[]) // (массив, начальное положение, конечное положение = размер массива - 1)
{
	int mid;
	if (start < end) 
	{
		mid = (start + end) / 2; // положение посередине
		mergeSort(list, start, mid, donelist); // проход по массиву до середины
		mergeSort(list, mid + 1, end, donelist); // проход по массиву с середины до конца
		merge(list, start, end, mid, donelist); // 
	}
}

int main()
{
	int list[] = {1, 2, 5, 6, 7, 10, 9, 4, 3, 8, 0, 15, 12, 11, 13, 18, 14, 16, 17, 20, 19}; // задаём массив чисел
	
	const int end = (sizeof(list) / sizeof(int)) - 1;
	int donelist[end + 1] = { 0 }; // будущий отсортированный массив (промежуточный)
	mergeSort(list, 0, end, donelist); // вызов сортировки слиянием

	std::cout << "Result:\n";
	for (int i = 0; i < end + 1; i++)
		std::cout << list[i] << " "; // вывод отсортированного массива
}