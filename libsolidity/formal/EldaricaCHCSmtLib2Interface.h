/*
	This file is part of solidity.

	solidity is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	solidity is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with solidity.  If not, see <http://www.gnu.org/licenses/>.
*/
// SPDX-License-Identifier: GPL-3.0

#pragma once

#include <libsmtutil/CHCSmtLib2Interface.h>

namespace solidity::frontend::smt
{

class EldaricaCHCSmtLib2Interface: public smtutil::CHCSmtLib2Interface
{
public:
	EldaricaCHCSmtLib2Interface(
		frontend::ReadCallback::Callback _smtCallback,
		std::optional<unsigned int> _queryTimeout,
		bool computeInvariants
	);

private:
	void setupSmtCallback() override;

	bool m_computeInvariants;
};

}
