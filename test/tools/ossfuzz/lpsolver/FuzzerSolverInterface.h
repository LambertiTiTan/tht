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
/**
 * Implements the Fuzzer-Solver interface.
 */

#pragma once

#include <libsolutil/LP.h>
#include <libsolutil/LinearExpression.h>

#include <string>

namespace solidity::test::fuzzer::lpsolver
{

using solution = std::pair<
    solidity::util::LPResult,
	std::map<std::string, solidity::util::rational>
>;

class FuzzerSolverInterface
{
public:
	FuzzerSolverInterface(bool _supportModels);

	/// @returns constant rational.
	solidity::util::LinearExpression constant(solidity::util::rational _rationalConstant);

	/// @returns linear expression that equals zero.
	solidity::util::LinearExpression zero()
	{
		return constant(0);
	}

	/// @returns product of a rational factor and variable.
	solidity::util::LinearExpression variable(
		solidity::util::rational _factor,
		std::string const& _variable
	);

	/// Adds less-than-equal-zero constraint to solver.
	void addLEConstraint(solidity::util::LinearExpression _lhs);

	/// Adds equal-to-zero constraint to solver.
	void addEQConstraint(solidity::util::LinearExpression _lhs);

	/// Adds less-than-equal constraint from vector of factors.
	void addLEConstraint(std::vector<int> _factors);

	/// Adds equal-to constraint from vector of factors.
	void addEQConstraint(std::vector<int> _factors);

	/// Adds @param _constraint to LP solver.
	void addConstraint(std::pair<bool, std::vector<int>> _constraint);

	/// Adds @param _constraints to LP solver.
	void addConstraints(std::vector<std::pair<bool, std::vector<int>>> _constraints);

	/// @returns linear expression created from @param _factors.
	solidity::util::LinearExpression linearExpression(std::vector<int> _factors);

	/// Queries LP solver and @returns solution.
	solution check();

	/// Queries LP solver and @returns sat result as string.
	std::string checkResult();

private:
	/// Adds variable if necessary to LP solver state and @returns index of variable.
	size_t variableIndex(std::string const& _name);

	/// @returns LP result as string.
	std::string lpResult(solidity::util::LPResult _result);

	solidity::util::LPSolver m_solver;
	solidity::util::SolvingState m_solvingState;
};
}
