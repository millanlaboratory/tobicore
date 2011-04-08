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
#ifndef ICCLASS_HPP
#define ICCLASS_HPP

#include <string>
#include "ICTypes.hpp"

#define ICCLASS_CHVALUE_SIZE	64
#define ICCLASS_CHLABEL_SIZE  	64

/*! \brief Pair of ICLabel and ICValue 
 *
 * This class is used to store a single pair of ICLabel and ICValue.
 * It implements methods that will be used later serializers
 * \sa ICSerializer, ICSerializerRapid
 */
class ICClass {
	public:
		/*! \brief Constructor
		 * Raises exceptions.
		 *
		 * \param label	Label type
		 * \param value	Value type
		 * \sa			ICLabel, ICValue
		 */
		ICClass(ICLabel label, ICValue value = 0.00f); 
		//! \brief Destructor
		virtual ~ICClass();

	public:
		/*! \brief Returns value type
		 * \return Value type
		 */
		virtual ICValue GetValue(void) const;
		/*! \brief Returns label type
		 * \return Label type
		 */
		virtual ICLabel GetLabel(void) const;
		/*! \brief Set the value type
		 * \return A pointer to the ICClass instance
		 */
		virtual ICClass* SetValue(ICValue value = 0.00f);
		/*! \brief Set the label type
		 * Raises exceptions.
		 *
		 * \return A pointer to the ICClass instance
		 */
		virtual ICClass* SetLabel(ICLabel label);
		/*! \brief Get ICValue as char array
		 * Raises exceptions.
		 *
		 * \return A pointer to the ICClass instance
		 */
		virtual const char* GetChValue(void);
		/*! \brief Get ICLabel as char array
		 * \return A pointer to the ICClass instance
		 */
		virtual const char* GetChLabel(void);

	private:
		ICValue _value;
		ICLabel _label;
		char _chvalue[ICCLASS_CHVALUE_SIZE];
		char _chlabel[ICCLASS_CHLABEL_SIZE];
};

#endif
