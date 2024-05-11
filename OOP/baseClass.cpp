#include "baseClass.h"

baseClass::baseClass(baseClass* parent, string name) : parent(parent), name(name) {
	if (parent != nullptr) {
		parent->children.push_back(this);
	}
}

baseClass::~baseClass() {
	for (int ChildIndex = 0; ChildIndex < children.size(); ChildIndex++) delete children[ChildIndex];
}

string baseClass::getName() { return name; }
baseClass* baseClass::getParent() { return parent; }

bool baseClass::setName(string newName) {
	if (getParent() != nullptr && getParent()->getChild(newName)) return false;
	name = newName;
	return true;
}

void baseClass::printNames(int countSpaces) /* Edited */
{
	cout << endl << string(countSpaces, ' ') << this->getName();
	for (baseClass* child : this->children)
		child->printNames(countSpaces + 4);
}

baseClass* baseClass::getChild(string name) {
	for (baseClass* child : children) {
		if (child->name == name) return child;
	}
	return nullptr;
}

baseClass* baseClass::goUpToTheObject(string name)
{
	for (int childIndex = 0; childIndex < children.size(); childIndex++)
	{
		if (name == children[childIndex]->getName())
			return children[childIndex];
		if (children[childIndex]->children.size() > 0)
		{
			baseClass* resultFromUp = children[childIndex]->goUpToTheObject(name);
			if (resultFromUp != nullptr) return resultFromUp;
		}
	}
	return nullptr;
}

baseClass* baseClass::goDownToTheObject(string name)
{
	if (name == getName()) return this;
	if (parent == nullptr) return goUpToTheObject(name);
	return parent->goDownToTheObject(name);
}

void baseClass::setReadyCode(int code)
{
	if (parent == nullptr || parent->readyCode != 0)
		this->readyCode = code;
	if (!code)
	{
		this->readyCode = code;
		for (int childIndex = 0; childIndex < children.size(); childIndex++)
			children[childIndex]->setReadyCode(code);
	}
}

void baseClass::printReadyStatus(int countSpaces) /* Edited */
{
	cout << endl << string(countSpaces, ' ') << this->getName();
	if (this->readyCode) cout << " is ready";
	else cout << " is not ready";
	for (baseClass* child : this->children)
		child->printNames(countSpaces + 4);
}

baseClass* baseClass::findObjectByCoordinate(string coordinate) /* Added */
{
	if (coordinate == "/")
	{
		baseClass* temp_root = this;
		while (temp_root->getParent())
			temp_root = temp_root->getParent();
		return temp_root;
	}

	if (coordinate == ".") return this;

	if (coordinate[0] == '/' && coordinate[1] == '/')
		return findObjectByCoordinate("/")->getChild(coordinate.substr(2));

	if (coordinate[0] == '.')
		return this->goUpToTheObject(coordinate.substr(1));

	if (coordinate[0] != '/')
	{
		string cutCoordinate = coordinate.substr(coordinate.find('/') + 1);
		if (cutCoordinate.find('/') == -1)
			return this->getChild(coordinate.substr(0, coordinate.find('/')))->getChild(cutCoordinate);
		else
			return this->getChild(coordinate.substr(0, coordinate.find('/')))->findObjectByCoordinate(cutCoordinate);
	}
	else
	{
		if (coordinate.substr(1).find('/') == -1)
			return findObjectByCoordinate("/")->getChild(coordinate.substr(1));
		return findObjectByCoordinate("/")->findObjectByCoordinate(coordinate.substr(1));
	}
}

void baseClass::removeChild(string name) /* Added */
{
	for (int i = 0; i < children.size(); i++)
	{
		if (children[i]->getName() == name)
		{
			children.erase(children.begin() + i);
			break;
		}
	}
}

bool baseClass::changeNewParent(baseClass* newParent) /* Added */
{
	if (this->getParent() == nullptr) return false;
	if (newParent == nullptr) return false;
	if (newParent->getChild(this->getName()) != nullptr) return false;
	if (this->goUpToTheObject(newParent->getName()) != nullptr) return false;

	this->getParent()->removeChild(this->getName());
	this->parent = newParent;
	newParent->children.push_back(this);
	return true;
}