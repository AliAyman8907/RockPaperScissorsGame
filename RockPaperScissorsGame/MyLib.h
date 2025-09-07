#pragma once
#include<iostream>
#include<vector>

using namespace std;

namespace MyLib {

	void fillLineWithHypens() {
		cout << string(133, '-') << '\n';
	}

	void printCentered(string text) {
		short columns = 133;
		short padding = (columns - text.size()) / 2;
		if (padding > 0) cout << string(padding, ' ');
		cout << text;
	}

	vector<string> splitString(string clientInfo, string delimiter = "#//#") {
		vector<string> parts;
		size_t pos = 0;
		string token;

		while ((pos = clientInfo.find(delimiter)) != string::npos) {
			token = clientInfo.substr(0, pos);
			parts.push_back(token);
			clientInfo.erase(0, pos + delimiter.length());
		}
		parts.push_back(clientInfo);
		return parts;
	}

}