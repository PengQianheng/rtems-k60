-- SPDX-License-Identifier: BSD-2-Clause

--
--  TMTEST / SPECIFICATION
--
--  DESCRIPTION:
--
--  This package is the specification for Test 4 of the RTEMS
--  Timing Test Suite.
--
--  DEPENDENCIES: 
--
--  
--
--  COPYRIGHT (c) 1989-2011.
--  On-Line Applications Research Corporation (OAR).
--
--  Redistribution and use in source and binary forms, with or without
--  modification, are permitted provided that the following conditions
--  are met:
--  1. Redistributions of source code must retain the above copyright
--     notice, this list of conditions and the following disclaimer.
--  2. Redistributions in binary form must reproduce the above copyright
--     notice, this list of conditions and the following disclaimer in the
--     documentation and/or other materials provided with the distribution.
--
--  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
--  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
--  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
--  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
--  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
--  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
--  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
--  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
--  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
--  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
--  POSSIBILITY OF SUCH DAMAGE.
--

with TIME_TEST_SUPPORT;
with RTEMS;
with RTEMS.TASKS;

package TMTEST is

--
--  This array contains the IDs of all RTEMS tasks created by this test.
--

   TASK_ID : array ( RTEMS.UNSIGNED32 
      range 1 .. TIME_TEST_SUPPORT.OPERATION_COUNT ) of RTEMS.ID;

--
--  This variable contains the id of the highest priority task
--  in the system.
-- 

   HIGHEST_ID : RTEMS.ID;

--
--  The following is the ID of the semaphore used for timing operations.
--

   SEMAPHORE_ID : RTEMS.ID;

--
--  The following is used to perform the same operation 
--  on a group of tasks.
--

   TASK_COUNT : RTEMS.UNSIGNED32;

--
--  The following variable is set to the execution time returned
--  by the timer.
--

   END_TIME  : RTEMS.UNSIGNED32;

--
--  INIT
--
--  DESCRIPTION:
--
--  This RTEMS task initializes the application.
--

   procedure INIT (
      ARGUMENT : in     RTEMS.TASKS.ARGUMENT
   );
   pragma Convention (C, INIT);

--
--  TEST_INIT
--
--  DESCRIPTION:
--
--  This subprogram performs test initialization.
--

   procedure TEST_INIT;

--
--  HIGHEST_TASK
--
--  DESCRIPTION:
--
--  This RTEMS task is created by one of the LOW_TASKS.  The 
--  first time it executes, it performs a blocking SEMAPHORE_OBTAIN
--  which transfers control of the processor to HIGH_TASK.
--  The first time HIGHEST_TASK is restarted, it stops the
--  timer and reports the execution time for a TASK_RESTART
--  for a blocked task which preempts the caller.  The second 
--  time HIGHEST_TASK is restarted, it stops the timer and reports 
--  the execution time for a TASK_RESTART for a ready task which 
--  has its original priority restored and preempts the caller.  
--

   procedure HIGHEST_TASK (
      ARGUMENT : in     RTEMS.TASKS.ARGUMENT
   );
   pragma Convention (C, HIGHEST_TASK);

--
--  HIGH_TASK
--
--  DESCRIPTION:
--
--  This RTEMS task is created by one of the LOW_TASKS.   This
--  task restarts HIGHEST_TASK twice.  HIGHEST_TASK is blocked the
--  first time and preempts this task when restarted.  HIGHEST_TASK
--  is ready the second time but has lowered its priority.  When 
--  restarted for the second time, HIGHEST_TASK will have its
--  original priority restored and preempt this task.
--  Once control of the processor is returned to this task after
--  HIGHEST_TASK deletes itself, the following execution times
--  are measured and reported.
--
--    + readying SEMAPHORE_RELEASE 
--    + TASK_CREATE
--    + TASK_START
--    + TASK_RESTART of a suspended task
--    + TASK_DELETE of a suspended task
--    + TASK_RESTART of a ready task
--    + TASK_RESTART of a blocked task which does not cause a preempt
--    + TASK_DELETE of a blocked task
--

   procedure HIGH_TASK (
      ARGUMENT : in     RTEMS.TASKS.ARGUMENT
   );
   pragma Convention (C, HIGH_TASK);

--
--  LOW_TASKS
--
--  DESCRIPTION:
--
--  The last of these RTEMS tasks to execute creates HIGH_TASK
--  and HIGHEST_TASK.  All of these tasks perform a blocking 
--  SEMAPHORE_OBTAIN.
--

   procedure LOW_TASKS (
      ARGUMENT : in     RTEMS.TASKS.ARGUMENT
   );
   pragma Convention (C, LOW_TASKS);

--
--  RESTART_TASK
--
--  DESCRIPTION:
--
--  This RTEMS task
--

   procedure RESTART_TASK (
      ARGUMENT : in     RTEMS.TASKS.ARGUMENT
   );
   pragma Convention (C, RESTART_TASK);

end TMTEST;
