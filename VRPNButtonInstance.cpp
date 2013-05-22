/* ========================================================================
 * PROJECT: UART
 * ========================================================================
 * Portions of this work are built on top of VRPN which was developed by
 *   Russell Taylor
 *   University of North Carolina
 * http://www.cs.unc.edu/Research/vrpn/
 *
 * We acknowledge the CISMM project at the University of North Carolina at Chapel Hill, supported by NIH/NCRR
 * and NIH/NIBIB award #2P41EB002025, for their ongoing  * support and maintenance of VRPN.
 *
 * Portions of this work are also built on top of the VideoWrapper,
 * a BSD licensed video access library for MacOSX and Windows.
 * VideoWrapper is available at SourceForge via
 * http://sourceforge.net/projects/videowrapper/
 *
 * Copyright of VideoWrapper is
 *     (C) 2003-2010 Georgia Tech Research Corportation
 *
 * Copyright of the new and derived portions of this work
 *     (C) 2010 Georgia Tech Research Corporation
 *
 * This software released under the Boost Software License 1.0 (BSL1.0), so as to be
 * compatible with the VRPN software distribution:
 *
 * Permission is hereby granted, free of charge, to any person or organization obtaining a copy
 * of the software and accompanying documentation covered by this license (the "Software") to use,
 * reproduce, display, distribute, execute, and transmit the Software, and to prepare derivative
 * works of the Software, and to permit third-parties to whom the Software is furnished to do so,
 * all subject to the following:
 *
 * The copyright notices in the Software and this entire statement, including the above license grant,
 * this restriction and the following disclaimer, must be included in all copies of the Software, in
 * whole or in part, and all derivative works of the Software, unless such copies or derivative works
 * are solely in the form of machine-executable object code generated by a source language processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE FOR ANY DAMAGES OR
 * OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * For further information regarding UART, please contact
 *   Blair MacIntyre
 *   <blair@cc.gatech.edu>
 *   Georgia Tech, School of Interactive Computing
 *   85 5th Street NW
 *   Atlanta, GA 30308
 *
 * For further information regarding VRPN, please contact
 *   Russell M. Taylor II
 *   <taylor@cs.unc.edu>
 *   University of North Carolina,
 *   CB #3175, Sitterson Hall,
 *   Chapel Hill, NC 27599-3175
 *
 * ========================================================================
 ** @author   Alex Hill (ahill@gatech.edu)
 *
 * ========================================================================
 *
 * VRPNButtonInstance.cpp
 *
 * Usage:
 *
 *
 * Notes:
 *
 * ========================================================================*/

#if _MSC_VER // this is defined when compiling with Visual Studio
#define EXPORT_API __declspec(dllexport) // Visual Studio needs annotating exported functions with this
#else
#define EXPORT_API // XCode does not need annotating exported functions, so define is empty
#endif

#include "VRPNButtonInstance.h"

void VRPN_CALLBACK handle_button(void *userdata, const vrpn_BUTTONCB t)
{
	VRPNButtonInstance *button = (VRPNButtonInstance*)userdata;
	button->addReport(t);
}


VRPNButtonInstance::VRPNButtonInstance(const char* name, vrpn_Connection* connection)
{
	button = new vrpn_Button_Remote(name, connection);
	button->register_change_handler(this,handle_button);
	maxReports = 1000;
}

VRPNButtonInstance::~VRPNButtonInstance()
{
	purgeReports();
	delete button;
}

void VRPNButtonInstance::purgeReports()
{
	ButtonList::iterator itr;
	for ( itr = data.begin(); itr != data.end(); itr++ )
	{
		vrpn_BUTTONCB* curr = *itr;
		delete curr;
	}
	data.erase(data.begin(),data.end());
}

vrpn_Button_Remote* VRPNButtonInstance::getButton()
{
	return button;
}


void VRPNButtonInstance::setMaxReports(int max)
{
	maxReports = max;
}

void VRPNButtonInstance::addReport(const vrpn_BUTTONCB& rep)
{
	vrpn_BUTTONCB* cpy = new vrpn_BUTTONCB;
	*cpy = rep;
	data.push_front(cpy);
	if ((int)data.size() > maxReports)
	{
		vrpn_BUTTONCB* rem = data.back();
		data.pop_back();
		delete rem;
	}
}

int VRPNButtonInstance::getNumReports()
{
	return (int)data.size();
}

void VRPNButtonInstance::getReports(vrpn_BUTTONCB** cpy, int& cnt, timeval* ts, int btn_num, bool clearReport)
{
	ButtonList::iterator it = data.end();
	int i = 0;

	while (it != data.begin())
	{
		it--;
		if (i < cnt)
		// Don't Add Too Many
		{
			vrpn_BUTTONCB* curr = *it;

			if ((btn_num < 0) || (curr->button == btn_num))
			// Make sure its the button we are looking for
			{
				if ((ts == NULL) || vrpn_TimevalGreater(curr->msg_time, *ts))
				// Check to make sure its newer
				{
					*cpy[i] = *curr;
					i++;

					if(clearReport)
					{
						delete curr;
						it = data.erase(it);
					}
				}
			}
		}
		else break;
	}

	cnt = i;
}