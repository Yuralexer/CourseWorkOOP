#include "Application.h"
#include <iostream>
#include <string>

using namespace std;

Application::Application(baseClass* parent) : baseClass(parent) {}

int Application::start_app(string failcoordinate) { /* Edited */
	cout << "Object tree";
	printNames();
	cout << endl;
	if (failcoordinate.size() != 0)
	{
		cout << "The head object " << failcoordinate << " is not found";
		return 1;
	}
	string commandCode, secondParameter, coordObject;
	baseClass* pointer = this;
	baseClass* temp;
	while (true)
	{
		cin >> commandCode;
		if (commandCode == "END")
		{
			cout << "Current object hierarchy tree";
			printNames();
			break;
		}
		cin >> secondParameter;
		temp = pointer->findObjectByCoordinate(secondParameter);
		if (commandCode == "SET")
		{
			if (temp != nullptr)
			{
				pointer = temp;
				cout << "Object is set: " << pointer->getName() << endl;
			}
			else
			{
				cout << "The object was not found at the specified coordinate: " << secondParameter << endl;
			}
		}
		if (commandCode == "FIND")
		{
			if (temp != nullptr)
				cout << secondParameter << "     Object name: " << temp->getName() << endl;
			else
				cout << secondParameter << "     Object is not found\n";
		}
		if (commandCode == "MOVE")
		{
			if (pointer->changeNewParent(temp))
				cout << "New head object: " << temp->getName() << endl;
			else if (temp == nullptr) cout << secondParameter << "     Head object is not found\n";
			else if (temp->getChild(pointer->getName()) != nullptr) cout << secondParameter << "     Dubbing the names of subordinate objects\n";
			else cout << secondParameter << "     Redefining the head object failed\n";
		}
		if (commandCode == "DELETE")
		{
			temp = pointer->getChild(secondParameter);
			if (temp != nullptr)
			{
				if (temp->getParent() == nullptr) coordObject = "/";
				else
				{
					temp->getParent()->removeChild(temp->getName());
					coordObject = "/" + temp->getName();
					while (temp->getParent()->getParent() != nullptr)
					{
						temp = temp->getParent();
						coordObject = "/" + temp->getName() + coordObject;
					}
				}
				delete this->findObjectByCoordinate(coordObject);
				cout << "The object " << coordObject << " has been deleted\n";
			}
		}
	}
	return 0;
}

string Application::build() { /* Edited */
	baseClass* selectedObject = this;
	string parentName, childName, parentCoordinate;
	int classNum;
	cin >> parentName;
	setName(parentName);
	while (true) {
		cin >> parentCoordinate;
		if (parentCoordinate == "endtree") return "";
		cin >> childName >> classNum;
		if (classNum < 2 || classNum > 6) continue;
		selectedObject = findObjectByCoordinate(parentCoordinate);
		if (selectedObject != nullptr)
		{
			if (selectedObject->getChild(childName) == nullptr)
			{
				switch (classNum)
				{
				case 2:
					new two(selectedObject, childName);
					break;
				case 3:
					new three(selectedObject, childName);
					break;
				case 4:
					new four(selectedObject, childName);
					break;
				case 5:
					new five(selectedObject, childName);
					break;
				case 6:
					new six(selectedObject, childName);
					break;
				default:
					break;
				}
			}
			else cout << parentCoordinate << "    Dubbing the names of subordinate objects\n";
		}
		else return parentCoordinate;
	}
}

