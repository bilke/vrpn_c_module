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
 * VRPNAnalogInstance.h
 *
 * Usage:
 *
 *
 * Notes:
 *
 * ========================================================================*/

#include "vrpn_Analog.h"
#include <list>
typedef std::list<vrpn_ANALOGCB* > AnalogList;

class VRPNAnalogInstance {

public:

	VRPNAnalogInstance(const char*, vrpn_Connection*);
	~VRPNAnalogInstance();

	vrpn_Analog_Remote* getAnalog();

	void setMaxReports(int);

	int getNumReports();

	//populate list of all reports based on criteria
	void getReports(vrpn_ANALOGCB**, int&, timeval*, bool);

	//add analog reports to list (delete oldest if list over maxReports)
	void addReport(const vrpn_ANALOGCB&);

	//remove all reports
	void purgeReports();

protected:
	vrpn_Analog_Remote* analog;
	int maxReports;

	AnalogList data;

};

