#pragma once
#include "baseClass.h"
#include "two.h"
#include "three.h"
#include "four.h"
#include "five.h"
#include "six.h"

class Application : public baseClass {
public:
	Application(baseClass* parent);
	string build();
	int start_app(string failcoordinate = "");
};