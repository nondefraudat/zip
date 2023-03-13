#include <zip.hpp>
#include <iostream>

using namespace std;

int correctEntryNamesReading(int, char* arguments[]) {
	const set<string> correctEntryNames({
				"oneline.txt",
				"multiline.txt",
				"folder/oneline.txt",
				"folder/multiline.txt"
			});
	const string zipPath(string(arguments[1]) + "/in.zip");
	const Zip zip(zipPath);
	const set<string> entryNames = zip.getEntryNames();
	if (entryNames.size() != correctEntryNames.size()) {
		cout << "Expected " + to_string(correctEntryNames.size())
				+ " entries and " + to_string(entryNames.size()) 
				+ " was found!" << endl;
		return EXIT_FAILURE;
	}
	for (const string& entryName : entryNames) {
		if (!correctEntryNames.contains(entryName)) {
			cout << "Unknown entry \"" + entryName + '\"' << endl;
			return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}