Mini Project :
■ Student Record Management System
- Add, update, delete, search student records.
- Use switch case, structures, functions, file handling.



📌 Problem Statement: Student Gradebook Management System

You are required to design and implement a Gradebook Management System in C.
This system should help a teacher manage student records, including their marks in multiple subjects, and automatically compute results such as total marks, average, and grade.

⸻

✅ Requirements
	1.	Student Information
	•	Each student record should include:
	•	Roll number (unique)
	•	Name
	•	Marks in 5 subjects
	•	Total marks (calculated)
	•	Average marks (calculated)
	•	Grade (calculated automatically based on average)
	2.	Functionalities
The system should provide the following options in a menu-driven format:
	•	Add Student: Insert a new student record. Roll numbers must be unique.
	•	List Students: Display all student records with details.
	•	Search Student: Search for a student by roll number and display their details.
	•	Update Marks: Modify marks of an existing student.
	•	Delete Student: Remove a student record by roll number.
	•	Save Records to File: Write all student records to a file (gradebook.txt).
	•	Load Records from File: Read all student records from the file.
	•	Exit: End the program after saving the data.
	3.	Grading Criteria
	•	Average ≥ 90 → Grade A
	•	Average ≥ 75 → Grade B
	•	Average ≥ 60 → Grade C
	•	Average ≥ 40 → Grade D
	•	Average < 40 → Grade F
	4.	Constraints
	•	Maximum of 100 students can be stored.
	•	Names cannot have spaces (simplification for input).
	•	Data must persist between runs using a text file (gradebook.txt).