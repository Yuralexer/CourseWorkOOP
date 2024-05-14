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
	void build();
	int start_app();
};