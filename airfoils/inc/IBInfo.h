/*
* --------------------------------------------------------------
*
* ------ Lattice Boltzmann @ The University of Manchester ------
*
* -------------------------- L-U-M-A ---------------------------
*
* Copyright 2019 The University of Manchester
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.*
*/

#ifndef IBINFO_H
#define IBINFO_H

#include "stdafx.h"


/// \brief Owner-side comm class for marker-owner communications
///
///			Class for arranging marker-owner MPI communication.
class MarkerCommOwnerSideClass {

	/************** Friends **************/
	friend class MpiManager;
	friend class IBBody;
	friend class ObjectManager;

public:

	/************** Constructors **************/
	MarkerCommOwnerSideClass();

	// Custom constructor for creating epsCommOwnerSideClass object
	MarkerCommOwnerSideClass(int rank, int body, int marker);

private:

	/************** Member Data **************/
	int rankComm;				///< Rank to be communicating with
	int bodyID;				///< Global body ID for communicating
	int markerID;				///< Marker ID for communicating
	int nSupportSites;			///< Number of support sites that need to be communicated
};


/// \brief Marker-side comm class for marker-owner communications
///
///			Class for arranging marker-owner MPI communication.
class MarkerCommMarkerSideClass {

	/************** Friends **************/
	friend class MpiManager;

public:

	/************** Constructors **************/
	MarkerCommMarkerSideClass();

	// Custom constructor for creating epsCommMarkerSideClass object
	MarkerCommMarkerSideClass(int rank, int body, int idx);

private:

	/************** Member Data **************/
	int rankComm;				///< Rank to be communicating with
	int bodyID;					///< Global body ID for communicating
	int markerIdx;				///< Local (rank) index of marker for communicating
};



/// \brief Support-side comm class for marker-support communications
///
///			Class for arranging marker-support MPI communication.
class SupportCommSupportSideClass {

public:

	/************** Constructors **************/
	SupportCommSupportSideClass();

	// Custom constructor for creating supportCommSupportSide object
	SupportCommSupportSideClass(int rankID, int bodyID, std::vector<int> &idx);

public:

	/************** Member Data **************/
	int rankComm;						///< Rank to be communicating with
	int bodyID;							///< Global body ID for communicating
	std::vector<int> supportIdx;		///< Local (rank) grid indices of support point
};


/// \brief Marker-side comm class for marker-support communications
///
///			Class for arranging marker-support MPI communication.
class SupportCommMarkerSideClass {

public:

	/************** Constructors **************/
	SupportCommMarkerSideClass();

	// Custom constructor for creating supportCommMarkerSide object
	SupportCommMarkerSideClass(int rankID, int body, int marker, int support);

public:

	/************** Member Data **************/
	int rankComm;					///< Rank to be communicating with
	int bodyID;						///< Global body ID for communicating
	int markerIdx;					///< Local (rank) index of marker for communicating
	int supportID;					///< Support index within the marker
};
#endif	// L_IBINFO_H
