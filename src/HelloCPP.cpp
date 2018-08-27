//============================================================================
// Name        : HelloCPP.cpp
// Author      : Claus
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <utility>
#include <vector>

using namespace std;

int main() {
	// When true don't print comma.
	bool first_element = true;

	// Used when merging back so we remember current merge-vector.
	enum class MergeVector {
		left,
		right
	};

	// Max. elements to merge each round.
	int merge_elements = 2;

	vector<int> input_v = {9, 3, 5, 1, 4};
	vector<int> merge_left_v = {};
	vector<int> merge_right_v = {};
	vector<int> output_v = {};

	// Get size of input-vector.
	int v_size = input_v.size();

	// Resize merge-vectors so they can be accessed using v[] rather than push_back().
	// https://stackoverflow.com/a/15889686/319826
	merge_left_v.resize(v_size + 1, '\0');
	merge_right_v.resize(v_size + 1, '\0');

	if (input_v.size()) { // Only print if vector has elements.
		cout << "unsorted" << endl;
		for (auto ive : input_v) {
			if (first_element == true) {
				first_element = false;
			} else {
				cout << ", ";
			}
			cout << ive;
		}
		cout << endl;
	}

	if (input_v.size() == 0) {
		cout << "empty list" << endl;
	}

	if (input_v.size() == 1) {
		cout << input_v.front() << endl;
	}

	if (input_v.size() == 2) {
		if (input_v.front() > input_v.back()) {
			output_v.push_back(move(input_v.back()));
			output_v.push_back(move(input_v.front()));
		} else {
			output_v.push_back(move(input_v.front()));
			output_v.push_back(move(input_v.back()));
		}
	}

	if (input_v.size() > 2) {
		// Place each element the left merge-vector.
		// Read two elements and put smallest element first.
		int first = 0, second = 0, tmp = 0;
		for (int i = 0; i < v_size; ++i) {
			if (input_v[i]) {
				// First element.
				first = input_v[i];
				++i;
				// Second element. Check if i points to a valid member of the vector.
				if (input_v[i] && i < v_size) {
					second = input_v[i];
					if (first > second) { // Compare and swap if needed.
						tmp = first;
						first = second;
						second = tmp;
					}
					cout << "second: " << second << endl;
					merge_left_v[i] = second;
				}
				cout << "first: " << first << endl;
				merge_left_v[i - 1] = first;
			}
		}

		// Compare first two elements with the third and fourth. Etc.
		// Then take the lowest value and move it to the next merge-vector and move
		// the pointer one unit forward.
		// Then four, eight and so forth.

		int base = 0;
		MergeVector m_v_side = MergeVector::left;
		for (int i = 0; base < v_size && i < v_size; ++i) {
			base = i * 2 * merge_elements;

			// Loop through all elements in intervals of 2 x `merge_elements`.
			for (int first = 0, second = 0; first < merge_elements && second < merge_elements; ) {
				cout << "first element: " << merge_left_v[base + first] << ", second: " << merge_left_v[base + merge_elements + second] << endl;
				// Find lowest number and merge them in that order to the opposite merge-vector.
				if (merge_left_v[base + first] == v_size - 1) { // Sole element in last batch. So just copy it. And break.
					merge_right_v[base + first + second] = merge_left_v[base + first];
					i = v_size;
					break;
				} else if (merge_left_v[base + first] < merge_left_v[base + merge_elements + second]) {
					merge_right_v[base + first + second] = merge_left_v[base + first];
					++first;
				} else if (merge_left_v[base + first] > merge_left_v[base + merge_elements + second]) {
					merge_right_v[base + first + second] = merge_left_v[base + merge_elements + second];
					++second;
				} else if (merge_left_v[base + first] == merge_left_v[base + merge_elements + second]) {
					merge_right_v[base + first + second] = merge_left_v[base + first];
					merge_right_v[base + first + second + 1] = merge_left_v[base + merge_elements + second];
					++first;
					++second;
				}

				// Did we get to the end of the segment? If so merge the other side.
				if (first == merge_elements) { // End of first side.
					for (; second < merge_elements; ++second) {
						cout << "end of first elements" << endl;
						merge_right_v[base + first + second] = merge_left_v[base + merge_elements + second];
					}
				}

				if (second == merge_elements) { // End of second side.
					for (; first < merge_elements; ++first) {
						cout << "end of second elements, base: " << base << ", merge_elements: " << merge_elements << ", first: " << first << ", number: " << merge_left_v[base + first] << endl;
						merge_right_v[base + first + second] = merge_left_v[base + first];
					}
				}

				cout << "index: " << i << ", first: " << first << ", second: " << second << endl << endl;
			}
			// Move lowest.

		}

	}

	// Print right merge-vector just for testing.
	if (merge_right_v.size()) { // Only print if vector has elements.
		first_element = true;
		cout << "sorted" << endl;
		for (int i = 0; i < v_size; ++i) {
			if (first_element == true) {
				first_element = false;
			} else {
				cout << ", ";
			}
			cout << merge_right_v[i];
		}
		cout << endl;
	}

	if (output_v.size()) { // Only print if vector has elements.
		first_element = true;
		cout << "sorted" << endl;
		for (auto ov : output_v) {
			if (first_element == true) {
				first_element = false;
			} else {
				cout << ", ";
			}
			cout << ov;
		}
		cout << endl;
	}


	cout << "Done!" << endl;

	return 0;
}
