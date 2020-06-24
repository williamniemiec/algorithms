#include <iostream>
#include <vector>


/**
* Searches for occurrences of a pattern within a text.
*/
class KMP
{
public:
	//-------------------------------------------------------------------------
	//		Methods
	//-------------------------------------------------------------------------
	/**
	* Searches by a pattern within a string and displays the index in the
	* text where the pattern was found.
	*
	* @param		str Text
	* @param		pattern Pattern that will be searched for within the text
	*/
	static void stringMatcher(std::string str, std::string pattern)
	{
		int idx_str = 0, idx_pattern = 0;
		int len_str = str.size(), len_pattern = pattern.size();
		std::vector<int> aux = prefixProcessing(pattern);


		while (idx_str < len_str) {
			// Checks if the content contained in the current index of the pattern
			// is the same as that contained in the current index of the text
			if (str[idx_str] == pattern[idx_pattern]) {
				idx_str++;
				idx_pattern++;
			}

			// Checks if pattern was found
			if (idx_pattern == len_pattern) {
				std::cout << "Pattern found! - index: " << idx_str - idx_pattern << std::endl;
				idx_pattern = aux[idx_pattern - 1];		// Ex: pattern = ABAB, text = ABABAB 
														// (after finding the first pattern, the pattern will return to index = 2)
			} else if (idx_str < len_str && pattern[idx_pattern] != str[idx_str]) {
				// If there was already a match, the index of the pattern comes back to the
				// last longest prefix suffix value
				if (idx_str > 0)
					idx_pattern = aux[idx_pattern - 1];
				else
					idx_str++;
			}
		}
	}

private:
	/**
	* Performs prefix processing, creating a vector to which for each position
	* contains the length of the longest prefix suffix value for the previous
	* index.
	*
	* @param		pattern Pattern that will be searched for within a text
	*
	* @return		Vector to which each position contains the length of the longest
	* prefix suffix value for the previous index
	*/
	static std::vector<int> prefixProcessing(std::string pattern)
	{
		int i = 1, j = 0; // j: index of the longest prefix suffix value
		int len = pattern.size();
		std::vector<int> aux(len);
		aux[0] = 0;


		while (i < len) {
			if (pattern[i] == pattern[j]) {
				j++;
				aux[i++] = j;
			} else {
				if (j > 0)	// There was already a match
					j = aux[j - 1];
				else {
					aux[i] = 0;
					i++;
				}
			}
		}

		return aux;
	}
};


//--------------------------------------------------------------------------
//		Main
//--------------------------------------------------------------------------
int main()
{
	KMP::stringMatcher("ABABAB", "ABAB");

	system("pause");

	return 0;
}