/**
 * @file autosar_sts_s10/task2_instance1.c
 *
 * @section desc File description
 *
 * @section copyright Copyright
 *
 * Trampoline Test Suite
 *
 * Trampoline Test Suite is copyright (c) IRCCyN 2005-2007
 * Trampoline Test Suite is protected by the French intellectual property law.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; version 2
 * of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * @section infos File informations
 *
 * $Date$
 * $Rev$
 * $Author$
 * $URL$
 */

/*Instance 1 of task t2*/

#include "embUnit.h"
#include "Os.h"

DeclareEvent(Event1);

/*test case:test the reaction of the system called with 
 an activation of a task*/
static void test_t2_instance1(void)
{
	StatusType result_inst_1, result_inst_2, result_inst_3, result_inst_4;
	
	SCHEDULING_CHECK_INIT(12);
	result_inst_1 = WaitEvent(Event1);
	SCHEDULING_CHECK_AND_EQUAL_INT(16,E_OK, result_inst_1);
	
	SCHEDULING_CHECK_INIT(17);
	result_inst_2 = ClearEvent(Event1);
	SCHEDULING_CHECK_AND_EQUAL_INT(17,E_OK, result_inst_2);
	
	SCHEDULING_CHECK_INIT(18);
	result_inst_3 = WaitEvent(Event1);
	SCHEDULING_CHECK_AND_EQUAL_INT(21,E_OK, result_inst_3);
	
	SCHEDULING_CHECK_INIT(22);
	result_inst_4 = TerminateTask();
	SCHEDULING_CHECK_AND_EQUAL_INT(22,E_OK, result_inst_4);
		
}

/*create the test suite with all the test cases*/
TestRef AutosarSTSTest_seq10_t2_instance1(void)
{
	EMB_UNIT_TESTFIXTURES(fixtures) {
		new_TestFixture("test_t2_instance1",test_t2_instance1)
	};
	EMB_UNIT_TESTCALLER(AutosarSTSTest,"AutosarSTSTest_sequence10",NULL,NULL,fixtures);
	
	return (TestRef)&AutosarSTSTest;
}

/* End of file autosar_sts_s10/task2_instance1.c */
