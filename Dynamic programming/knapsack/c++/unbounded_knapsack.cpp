#include <vector>
#include <algorithm>
#include <stdexcept>


/**
* Responsible for dealing with the unbounded knapsack problem.
*/
class Knapsack
{
	//-------------------------------------------------------------------------
	//		Attributes
	//-------------------------------------------------------------------------
	std::vector<int> maxValue;
	std::vector<std::vector<int> > selectedElements;
	int size;


public:
	//-------------------------------------------------------------------------
	//		Constructor
	//-------------------------------------------------------------------------
	Knapsack()
	{
		size = -1;
	}


	//-------------------------------------------------------------------------
	//		Destructor
	//-------------------------------------------------------------------------
	~Knapsack()
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
	Knapsack* knapsack_unbounded(std::vector<int>& w, std::vector<int>& v, int N, int W)
	{
		// Stores the maximum value which can be reached with a certain capacity
		maxValue.clear();
		maxValue.resize(W + 1);

		size = W + 1;

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

	int getMaximumValue(int capacity)
	{
		if (capacity < 0 || capacity >= size)
			throw std::invalid_argument("Capacity out of bounds");

		return maxValue[capacity];
	}

	/**
	 * Returns elements that are part of the knapsack with a certain capacity.
	 *
	 * @param		capacity Capacity of the knapsack
	 * @return		Elements that are part of the knapsack with the capacity
	 * provided
	 */
	std::vector<int>& getSelectedElements(int capacity)
	{
		if (capacity < 0 || capacity >= size)
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
/**
 * Usage example with reference to this example:
 * {@link https://www.urionlinejudge.com.br/repository/UOJ_1487_en.html}
 */
int main()
{
	Knapsack* knapsack = new Knapsack();
	int totalCapacity = 60, elements = 5;
	vector<int> elements_weight(elements) = { 10, 20, 5, 50, 22 };
	vector<int> elements_values(elements) = { 30, 32, 4, 90, 45 };

	knapsack->knapsack_unbounded(elements_weight, elements_values, elements, totalCapacity);

	std::cout	<< "Maximum value: "
				<< knapsack->getMaximumValue()
				<< std::endl;
	std::cout	<< "Selected values: " 
				<< knapsack->selectedElements_toString()
				<< std::endl;

	system("pause");

	return 0;
}