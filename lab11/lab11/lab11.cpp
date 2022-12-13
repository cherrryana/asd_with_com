#include <iostream>

// быстрая сортировка

int pivot(int list[], int start, int end) // pivot - опорная точка, делит на 2 подмассива (левый < pivot, правый >= pivot)
{
	int p = list[end]; // выбираем крайний правый элемент в кач-ве опорного
	int pId = start; // элементы < p будут перемещены влево от pId
	// элементы >= p справо от pId
	
	for (int i = start; i < end; i++)
	{
		if (list[i] <= p) // когда находим элемент <= p наш pId увеличивается, элемент помещается перед опорной точкой
		{
			std::swap(list[i], list[pId]);
			pId++;
		}
	}

	std::swap(list[pId], list[end]); // меняем pId с p
	return pId; // возвращаем индекс опорного элемента
}

void quickSort(int list[], int start, int end) // (массив, начальное положение, конечное положение = размер массива - 1
{
	if (start < end)
	{
		int p = pivot(list, start, end); // переставляем элементы

		quickSort(list, start, p - 1); // повторям подмассив с элементами < опорной точки
		quickSort(list, p + 1, end); // повторям подмассив с элементами >= точки опоры
	}
}

int main()
{
	int list[] = {1, 2, 11, 10, 55, 2, 12, 289, 28}; 

	quickSort(list, 0, sizeof(list) / sizeof(int) - 1);

	std::cout << "Result: ";
	for (int i = 0; i < sizeof(list) / sizeof(int); i++) // вывод отсортированного массива
		std::cout << list[i] << " ";

	return 0;
}