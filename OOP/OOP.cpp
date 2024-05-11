#include <iostream>
#include "Application.h"

int main()
{
	Application ob_Application(nullptr);
	return(ob_Application.start_app(ob_Application.build()));
}