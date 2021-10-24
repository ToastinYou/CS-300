#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include<sstream>

using namespace std;

struct Course {
	string courseNum;
	string courseName;
	vector<string> coursePrerequisites;

	Course(string num) {
		this->courseNum = num;
	}

	Course(string num, string name) {
		this->courseNum = num;
		this->courseName = name;
	}

	Course(string num, string name, vector<string> prerequisites) {
		this->courseNum = num;
		this->courseName = name;
		this->coursePrerequisites = prerequisites;
	}
};

vector<Course> ReadFile() {
	ifstream file("ABCU_Advising_Program_Input.txt");
	vector<Course> courses;
	vector<string> lines;
	vector<string> phrases;

	while (!file.eof()) {
		string line = "";
		getline(file, line, '\n');
		lines.push_back(line);
	}

	for (string line : lines) {
		stringstream s_stream(line);
		while (!s_stream.eof()) {
			string phrase = "";
			getline(s_stream, phrase, ',');
			phrases.push_back(phrase);
		}

		string courseNum = phrases[0];
		string courseName = phrases[1];
		vector<string> prerequisites;
		for (int i = 0; i < phrases.size(); i++)
		{
			if (i == 0 || i == 1) continue;
			prerequisites.push_back(phrases[i]);
		}

		courses.push_back(Course(courseNum, courseName, prerequisites));
		phrases.clear();
	}

	file.close();
	return courses;
}

void PrintCourseList(vector<Course> courses) {
	cout << endl;
	for (Course c : courses) {
		cout << c.courseNum << ", " << c.courseName << endl;
	}
	cout << endl;
}

vector<Course> SelectionSort(vector<Course>& courses) {
	//define min as int (index of the current minimum course)
	int min = 0;

	// check size of courses vector
	// set size_t platform-neutral result equal to courses.size()
	int size_t = courses.size();

	// pos is the position within courses that divides sorted/unsorted
	// for size_t pos = 0 and less than size -1 
	for (int pos = 0; pos < size_t - 1; pos++) {
		// set min = pos
		min = pos;
		// loop over remaining elements to the right of position
		for (int i = pos + 1; i < courses.size(); i++) {
			// if this element's title is less than minimum title
			if (courses[i].courseNum < courses[min].courseNum) {
				// this element becomes the minimum
				min = i;
			}
		}
		// swap the current minimum with smaller one found
		// swap is a built in vector method
		swap(courses[pos], courses[min]);
	}

	return courses;
}

void GetCourse(vector<Course> courses) {
	cout << "What course do you want to know about? ";
	string courseNum = "";
	cin >> courseNum;
	for (Course c : courses) {
		if (c.courseNum == courseNum) {
			cout << c.courseNum << ", " << c.courseName << endl;
			cout << "Prerequisites: ";
			for (string s : c.coursePrerequisites) {
				cout << s << ", ";
			}
		}
	}
	cout << "\n\n";
}

void DisplayMenu() {
	cout << "1. Load Data Structure.\n";
	cout << "2. Print Course List.\n";
	cout << "3. Print Course.\n";
	cout << "9. Exit\n\n";
}

int GetInput() {
	cout << "What would you like to do? ";
	try
	{
		int input = -1;
		cin >> input;
		return input; // TODO: int validation
	}
	catch (const std::exception&)
	{
		return -1;
	}
}

int main(int argc, char* argv[]) {
	vector<Course> courses;
	vector<Course> coursesSorted;
	bool finished = false;
	while (!finished) {
		cout << "Welcome to the course planner.\n\n";
		DisplayMenu();
		int input = GetInput();

		switch (input)
		{
		case 1: // Load Data Structure.
			courses = ReadFile();
			break;
		case 2: // Print Course List.
			coursesSorted = SelectionSort(courses);
			PrintCourseList(coursesSorted);
			break;
		case 3: // Print Course.
			GetCourse(courses);
			break;
		case 9: // Exit
			finished = true;
			break;
		default: // Unknown Input
			cout << input << " is not a valid option.\n\n";
			break;
		}
	}

	return 0;
}