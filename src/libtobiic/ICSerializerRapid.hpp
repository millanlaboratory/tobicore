/*
    Copyright (C) 2010  EPFL (Ecole Polytechnique Fédérale de Lausanne)
    Michele Tavella <michele.tavella@epfl.ch>

    This file is part of the libtobiic library

    The libtobiic library is free software: you can redistribute it and/or
    modify it under the terms of the version 3 of the GNU General Public
    License as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ICSERIALIZERRAPID_HPP
#define ICSERIALIZERRAPID_HPP

#include "ICMessage.hpp"
#include "ICSerializer.hpp"

class ICSerializerRapid : public ICSerializer {
	public:
		ICSerializerRapid(ICMessage* const message = NULL, 
				const bool indent = false, const bool declaration = false);
		virtual ~ICSerializerRapid(void);
		
		virtual std::string* Serialize(std::string* buffer);
		virtual std::string* Deserialize(std::string* const buffer);

	protected:
		bool _indent;
		bool _declaration;
};

#endif
