#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <string>


/**
 * Responsible for dealing with the unbounded knapsack problem.
 */
class UnboundedKnapsack
{
	//-------------------------------------------------------------------------
	//		Attributes
	//-------------------------------------------------------------------------
	/**
	 * Stores maximum value of the knapsack for a certain capacity.
	 */
	std::vector<int> maxValue;

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


public:
	//-------------------------------------------------------------------------
	//		Constructor
	//-------------------------------------------------------------------------
	UnboundedKnapsack()
	{
		maximumCapacity = -1;
	}


	//-------------------------------------------------------------------------
	//		Destructor
	//-------------------------------------------------------------------------
	~UnboundedKnapsack()
	{
		delete this;
	}


	//-------------------------------------------------------------------------
	//		Methods
	//-------------------------------------------------------------------------
	/**
	 * Unbounded knapsack allows to use one or more occurrences of an item.
	 *
	 * @param		w Weight of the elements
	 * @param		v Value of the elements
	 * @param		N Number of itens
	 * @param		W Maximum weight capacity
	 * @return		This object to allow chained calls
	 */
	UnboundedKnapsack* knapsack_unbounded(std::vector<int>& w, std::vector<int>& v, int N, int W)
	{
		// Stores the maximum value which can be reached with a certain capacity
		maxValue.clear();
		maxValue.resize(W + 1);

		maximumCapacity = W + 1;

		// Stores selected elements with a certain capacity
		selectedElements.resize(W + 1);

		// Initializes maximum value vector with zero
		for (int i = 0; i < W + 1; i++) {
			maxValue[i] = 0;
		}

		// Computes the maximum value that can be reached for each capacity
		for (int capacity = 0; capacity < W + 1; capacity++) {
			// Goes through all the elements
			for (int n = 0; n < N; n++) {
				if (w[n] <= capacity) {
					// max(maxValue[capacity], maxValue[capacity - w[n]] + v[n])
					if (maxValue[capacity] <= maxValue[capacity - w[n]] + v[n]) {
						maxValue[capacity] = maxValue[capacity - w[n]] + v[n];

						// Stores selected elements
						selectedElements[capacity].clear();
						selectedElements[capacity].push_back(n + 1);

						for (int elem : selectedElements[capacity - w[n]]) {
							selectedElements[capacity].push_back(elem);
						}
					}
				}
			}
		}

		return this;
	}

	/**
	 * Returns maximum value for a certain number of elements and a certain
	 * capacity.
	 *
	 * @param		capacity Capacity of the knapsack
	 * @return		Maximum possible value with capacity provided
	 * @throws		std::invalid_argument If capacity provided is out of bounds
	 */
	int getMaximumValue(int capacity)
	{
		if (capacity < 0 || capacity >= maximumCapacity)
			throw std::invalid_argument("Capacity out of bounds");

		return maxValue[capacity];
	}

	/**
	 * Returns elements that belong to the knapsack with a certain capacity.
	 *
	 * @param		capacity Capacity of the knapsack
	 * @return		Elements that are part of the knapsack with the capacity
	 * provided
	 * @throws		std::invalid_argument If capacity provided is out of bounds
	 * @apiNote		Elements are referenced by their index + 1
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
	 * @apiNote		Elements are referenced by their index + 1
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
/**
 * Example made based on this exercise:
 * {@link https://www.urionlinejudge.com.br/repository/UOJ_1487_en.html}
 */
int main()
{
	UnboundedKnapsack* knapsack = new UnboundedKnapsack();
	int totalCapacity = 60, elements = 5;
	std::vector<int> elements_weight = { 10, 20, 5, 50, 22 };
	std::vector<int> elements_values = { 30, 32, 4, 90, 45 };

	knapsack->knapsack_unbounded(elements_weight, elements_values, elements, totalCapacity);

	std::cout	<< "Maximum value: "
				<< knapsack->getMaximumValue(totalCapacity)
				<< std::endl;
	std::cout	<< "Selected elements: " 
				<< knapsack->selectedElements_toString(totalCapacity)
				<< std::endl;

	system("pause");

	return 0;
}