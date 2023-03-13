#include <zip.hpp>
#include <iostream>

using namespace std;

int logError(const string& message) {
	cout << message << endl;
	return EXIT_FAILURE;
}

int correctEntryDataReading(int, char* arguments[]) {
	const string correctOneLineText({
				"Text Data One Line"
			});
	const string correctMultilineText({
				"Text Data\n"
				"Multiline\n"
			});
	const string zipPath(string(arguments[1]) + "/in.zip");
	const Zip zip(zipPath);
	const string oneLineText = zip.getEntryData("folder/oneline.txt");
	if (oneLineText != correctOneLineText) {
		cout << "Uncorrect Line: {\n" + oneLineText + "}" << endl;
		cout << "Expected: {\n" << correctOneLineText << "}" << endl;
		return EXIT_FAILURE;
	}
	const string multilineText = zip.getEntryData("multiline.txt");
	if (strcmp(multilineText.c_str(), correctMultilineText.c_str()) == 0) {
		cout << "Uncorrect Multiline: {\n" + multilineText + "}" << endl;
		cout << "Expected: {\n" << correctMultilineText << "}" << endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}