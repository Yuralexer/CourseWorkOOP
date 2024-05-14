#include <iostream>
#include "Application.h"

int main()
{
	Application ob_Application(nullptr);
	ob_Application.build();
	return(ob_Application.start_app());
}