# Combined Projects: Class Schedule Generator and Place Visit Planner

This repository contains two projects:
1. **Class Schedule Generator**: Creates weekly schedules for classes and assigns teachers based on availability and constraints.
2. **Place Visit Planner**: Plans optimal visits to places based on opening hours, ranks, and visitation constraints.

## Project 1: Class Schedule Generator

### Overview
The Class Schedule Generator creates a weekly timetable for courses while ensuring:
- Teachers are assigned based on their availability.
- No schedule conflicts between courses and teacher commitments.
- Courses are distributed evenly across the week.

### Features
1. **Teacher Management**:
   - Handles teacher availability, free days, and courses they can teach.
   - Assigns teachers with minimal workdays and resolves conflicts.

2. **Course Scheduling**:
   - Schedules courses based on provided time slots and teacher availability.
   - Ensures all courses are allocated without conflicts.

3. **Output**:
   - Produces a structured weekly schedule showing courses, assigned teachers, and timings.

### How to Run
1. **Compile**:
   ```bash
   g++ "class schedule.cpp" -o ScheduleGenerator
