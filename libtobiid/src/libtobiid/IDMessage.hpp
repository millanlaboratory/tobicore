/*
    Copyright (C) 2010  EPFL (Ecole Polytechnique Fédérale de Lausanne)
    Michele Tavella <michele.tavella@epfl.ch>

    This file is part of the libtobiid library

    The libtobiid library is free software: you can redistribute it and/or
    modify it under the terms of the version 3 of the GNU General Public
    License as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTIDULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef IDMESSAGE_HPP
#define IDMESSAGE_HPP

#include "IDTypes.hpp"
#include <libtobicore/TCBlock.hpp>

//class DLLEXPORT IDMessage {
class IDMessage : public TCBlock {
	friend class IDSerializerRapid;
	public:
		IDMessage(void);
		IDMessage(IDMessage* const other);
		IDMessage(IDFtype familyType, IDevent event);
		virtual ~IDMessage(void);
		
		virtual void Copy(IDMessage* const other);
		virtual std::string GetDescription(void) const;
		virtual void SetDescription(const std::string& description);
		virtual IDFvalue GetFamily(void) const;
		virtual void SetFamilyType(const IDFtype type);
		virtual IDFtype GetFamilyType(void) const;
		virtual void SetEvent(const IDevent event);
		virtual IDevent GetEvent(void) const;
		virtual void Dump(void) const;
		static const IDFtype FamilyType(IDFvalue family);
	private:
		virtual void Init(void);

	public:
		static const IDFtype FamilyUndef = -1;
		static const IDFtype FamilyBiosig = 0;
		static const IDevent EventNull = -1;
	private:
		IDFtype _familyType;
		IDevent _event;
		std::string _description;
};

#endif
