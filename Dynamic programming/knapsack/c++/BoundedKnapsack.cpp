#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <string>


/**
 * Responsible for dealing with the bounded knapsack problem.
 */
class BoundedKnapsack
{
	//-------------------------------------------------------------------------
	//		Attributes
	//-------------------------------------------------------------------------
	/**
	 * Stores maximum value of the knapsack for a certain number of elements 
	 * and for a certain capacity.
	 * <li><b>Line:</b> Element index</li>
	 * <li><b>Column:</b> Knapsack capacity</li>
	 */
	std::vector<std::vector<int> > maxValue;

	/**
	 * Stores elements that are part of the knapsack with a certain capacity.
	 * <li><b>Line:</b> Knapsack capacity</li>
	 * <li><b>Column:</b> Elements</li>
	 */
	std::vector<std::vector<int> > selectedElements;

	/**
	 * Stores maximum backpack capacity.
	 */
	int maximumCapacity;

	/**
	 * Stores total of element that can be put in the knapsack.
	 */
	int totalElements;


public:
	//-------------------------------------------------------------------------
	//		Constructor
	//-------------------------------------------------------------------------
	BoundedKnapsack()
	{
		maximumCapacity = -1;
		totalElements = -1;
	}


	//-------------------------------------------------------------------------
	//		Destructor
	//-------------------------------------------------------------------------
	~BoundedKnapsack()
	{
		delete this;
	}


	//-------------------------------------------------------------------------
	//		Methods
	//-------------------------------------------------------------------------
	/**
	 * Bounded knapsack considers only one occurrence of an item (no repeated
	 * elements).
	 *
	 * @param		w Weight of the elements
	 * @param		v Value of the elements
	 * @param		N Number of itens
	 * @param		W Maximum weight capacity
	 * @return		This object to allow chained calls
	 */
	BoundedKnapsack* knapsack_bounded(std::vector<int>& w, std::vector<int>& v, int N, int W)
	{
		// Stores the maximum value which can be reached with a certain capacity 
		// and with a certain number of elements
		maxValue.resize(N + 1);
		selectedElements.resize(W + 1);

		totalElements = N + 1;
		maximumCapacity = W + 1;

		// Initializes first column of the matrix with zeros
		for (int i = 0; i < N + 1; i++) {
			maxValue[i].resize(W + 1);
			maxValue[i][0] = 0;
		}

		// Initializes first line of the matrix with zeros
		for (int i = 1; i < W + 1; i++) {
			maxValue[0][i] = 0;
		}

		// Computes the maximum value that can be reached varying the number of 
		// elements and the capacity
		for (int n = 1; n < N + 1; n++) {
			// Computes the maximum value that can be reached for each capacity 
			// with current number of elements (n)
			for (int capacity = 1; capacity < W + 1; capacity++) {
				if (w[n - 1] <= capacity) {
					// max(maxValue[n - 1][capacity], maxValue[n - 1][capacity - w[n - 1]] + v[n - 1])
					if (maxValue[n - 1][capacity] <= maxValue[n - 1][capacity - w[n - 1]] + v[n - 1]) {
						maxValue[n][capacity] = maxValue[n - 1][capacity - w[n - 1]] + v[n - 1];

						// Stores selected elements
						selectedElements[capacity].clear();
						selectedElements[capacity].push_back(n);

						for (int elem : selectedElements[capacity - w[n - 1]]) {
							selectedElements[capacity].push_back(elem);
						}
					} else {
						maxValue[n][capacity] = maxValue[n - 1][capacity];
					}
				} else
					maxValue[n][capacity] = maxValue[n - 1][capacity];
			}
		}

		return this;
	}

	/**
	 * Returns maximum value for a certain number of elements and a certain 
	 * capacity.
	 *
	 * @param		elements Number of elements
	 * @param		capacity Capacity of the knapsack
	 * @return		Maximum possible value with number of elements and capacity 
	 * provided
	 * @throws		std::invalid_argument If capacity provided is out of bounds or
	 * total elements is out of bounds
	 */
	int getMaximumValue(int elements, int capacity)
	{
		if (capacity < 0 || capacity >= maximumCapacity)
			throw std::invalid_argument("Capacity out of bounds");

		if (elements < 0 || elements >= this->totalElements)
			throw std::invalid_argument("Elements out of bounds");

		return maxValue[elements][capacity];
	}

	/**
	 * Returns elements that are part of the knapsack with a certain capacity.
	 *
	 * @param		capacity Capacity of the knapsack
	 * @return		Elements that are part of the knapsack with the capacity 
	 * provided
	 * @throws		std::invalid_argument If capacity provided is out of bounds
	 */
	std::vector<int>& getSelectedElements(int capacity)
	{
		if (capacity < 0 || capacity >= maximumCapacity)
			throw std::invalid_argument("Capacity out of bounds");

		return selectedElements[capacity];
	}

	/**
	 * Returns elements that are part of the knapsack with a certain capacity. 
	 * This method will return a {@link std::string} with the following format:
	 * <code>[elem1, elem2, elem3...]</code>
	 *
	 * @param		capacity Capacity of the knapsack
	 * @return		Elements that are part of the knapsack with the capacity 
	 * provided
	 */
	std::string selectedElements_toString(int capacity)
	{
		std::string response = "[";

		for (int element : selectedElements[capacity]) {
			response.append(std::to_string(element));
			response.append(", ");
		}

		// Removes last ", "
		response.pop_back();
		response.pop_back();

		response.append("]");

		return response;
	}
};


//-------------------------------------------------------------------------
//		Main
//-------------------------------------------------------------------------
int main()
{
	BoundedKnapsack* knapsack = new BoundedKnapsack();
	int totalCapacity = 50, elements = 3;
	std::vector<int> elements_weight = { 10, 20, 30 };
	std::vector<int> elements_values = { 60, 100, 120 };

	knapsack->knapsack_bounded(elements_weight, elements_values, elements, totalCapacity);

	std::cout	<< "Maximum value: " 
				<< knapsack->getMaximumValue(elements, totalCapacity)
				<< std::endl;
	std::cout	<< "Selected values: "
				<< knapsack->selectedElements_toString(totalCapacity)
				<< std::endl;

	system("pause");

	return 0;
}